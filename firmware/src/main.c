#include <FreeRTOS.h>
#include <message_buffer.h>
#include <queue.h>
#include <task.h>

#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/cm3/cortex.h>

#include <stdlib.h>

#include "gcode.h"
#include "serial.h"
#include "actuate.h"
#include "bsp.h"

const stepper_s stepper_x = {
    // TODO
    .step_pin = GPIO13,
    .step_port = GPIOC,
    .dir_pin = GPIO12,
    .dir_port = GPIOC,
};

const stepper_s stepper_y = {
    // TODO
    .step_pin = GPIO15,
    .step_port = GPIOC,
    .dir_pin = GPIO14,
    .dir_port = GPIOC,
};

const pin_s servo = {
    .pin = GPIO0,
    .port = GPIOB,
};

const pin_s solenoid = {
    .pin = GPIO1,
    .port = GPIOB,
};

const pin_s limit_x = {
    .pin = GPIO4,
    .port = GPIOA,
};

const pin_s limit_y = {
    .pin = GPIO5,
    .port = GPIOA,
};

// Queue for UART characters to be processed
xQueueHandle uart1_queue;
xQueueHandle uart2_queue;
MessageBufferHandle_t raw_gcode_buffer;
xQueueHandle command_queue;

void usart1_isr(void) {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    char c = usart_recv(USART1);

    xQueueSendFromISR(uart1_queue, &c, &xHigherPriorityTaskWoken);
}

void task_uart(void *args __attribute__((unused))) {
    uint8_t uart_buffer[64];
    uint8_t uart_buffer_length = 0;
    char c;

    for (;;) {
        // Block until UART received
        xQueueReceive(uart1_queue, &c, portMAX_DELAY);

        if (c != '\n') {
            uart_buffer[uart_buffer_length] = c;
            uart_buffer_length++;
        } else {
            // c == '\n'
            uart_buffer[uart_buffer_length] = '\0';
            uart_buffer_length++;
            xMessageBufferSend(raw_gcode_buffer, &uart_buffer,
                               uart_buffer_length, 0);
        }
    }
}

void task_shell(void *args __attribute__((unused))) {
    char buf[RECV_BUF_SIZE];
    int len;

    for (;;) {
        console_puts("Enter a string: ");
        len = console_gets(buf, 128);
        if (len) {
            console_puts("\nYou entered : '");
            console_puts(buf);
            console_puts("'\n");
        } else {
            console_puts("\n");
        }
    }
}

void task_gcode(void *args __attribute__((unused))) {
    char gcode[64];
    int rc = 0;

    for (;;) {
        size_t len = xMessageBufferReceive(raw_gcode_buffer, &gcode, 64, 0);
        (void)len;

        // decode
        gcode_command_s cmd;
        rc = gcode_parse(gcode, len, &cmd);

        if (rc == GCODE_PARSE_UNKNOWN) {
            // handle error
        } else if (rc == GCODE_PARSE_ERROR) {
            // handle error
        } else {
            // TODO handle queue full
            xQueueSend(command_queue, (void *)&cmd, 0);
        }
    }
}

void task_ui(void *args __attribute__((unused))) {
    for (;;) {}
}

void task_motion(void *args __attribute__((unused))) {
    gcode_command_s cmd;

    for (;;) {
        xQueueReceive(command_queue, &cmd, portMAX_DELAY);

        switch (cmd.type) {
            case G01: {
                move_linear(cmd.g01.x, cmd.g01.y);
                move_z_axis(cmd.g01.z);
            } break;
            case M400: {
                actuate_solenoid(false);
            } break;
            case M401: {
                actuate_solenoid(true);
            } break;
        }

        // send "ok\n"
    }
}

void task_blink(void *args) {
    (void)args;

    for (;;) {
        gpio_toggle(GPIOC, GPIO13);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

static void usart_setup(int uart) {
    gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ,
                  GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO_USART2_TX);

    gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ,
                  GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO_USART1_TX);

    usart_set_baudrate(uart, 9600);
    usart_set_databits(uart, 8);
    usart_set_stopbits(uart, USART_STOPBITS_1);
    usart_set_mode(uart, USART_MODE_TX_RX);
    usart_set_parity(uart, USART_PARITY_NONE);
    usart_set_flow_control(uart, USART_FLOWCONTROL_NONE);

    switch (uart) {
        case USART1: {
            nvic_enable_irq(NVIC_USART1_IRQ);
        } break;
        case USART2: {
            nvic_enable_irq(NVIC_USART2_IRQ);
        } break;
        default: {
            // Do nothing
        } break;
    }

    usart_enable_rx_interrupt(uart);

    usart_enable(uart);
}

static void gpio_setup(void) {
    gpio_set_mode(limit_x.port, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_INPUT_FLOAT, limit_x.pin);
    gpio_set_mode(limit_y.port, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_INPUT_FLOAT, limit_y.pin);
}

int main(void) {
    rcc_clock_setup_pll(&rcc_hse_configs[RCC_CLOCK_HSE8_72MHZ]);
    rcc_periph_clock_enable(RCC_USART1);
    rcc_periph_clock_enable(RCC_USART2);
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_GPIOB);

    gpio_setup();
    usart_setup(USART1);
    usart_setup(USART2);

    /*
     * Synchronization
     */
    uart1_queue = xQueueCreate(1, sizeof(char));
    uart2_queue = xQueueCreate(1, sizeof(char));
    raw_gcode_buffer = xMessageBufferCreate(64);
    command_queue = xQueueCreate(1, sizeof(gcode_command_s));

    xTaskCreate(task_gcode, "gcode", 100, NULL, configMAX_PRIORITIES - 1, NULL);
    xTaskCreate(task_uart, "uart", 100, NULL, configMAX_PRIORITIES - 1, NULL);
    // xTaskCreate(task_shell, "shell", 100, NULL, configMAX_PRIORITIES - 1, NULL);
    // xTaskCreate(task_ui, "ui", 100, NULL, configMAX_PRIORITIES - 1, NULL);
    xTaskCreate(task_motion, "motion", 100, NULL, configMAX_PRIORITIES - 1, NULL);

    vTaskStartScheduler();

    do {} while (1);
    return 0;
}
