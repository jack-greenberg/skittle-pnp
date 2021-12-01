#include <FreeRTOS.h>
#include <message_buffer.h>
#include <queue.h>
#include <task.h>

#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/cortex.h>

#include <stdlib.h>
#include <string.h>

#include "gcode.h"
#include "serial.h"
#include "actuate.h"
#include "bsp.h"

const stepper_s stepper_x = {
    // TODO
    .step_pin = GPIO13,
    .step_port = GPIOB,
    .dir_pin = GPIO12,
    .dir_port = GPIOB,
};

const stepper_s stepper_y = {
    // TODO
    .step_pin = GPIO15,
    .step_port = GPIOB,
    .dir_pin = GPIO14,
    .dir_port = GPIOB,
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
        uart_putc(USART1, c);

        if (c != '\r') {
            uart_buffer[uart_buffer_length] = c;
            uart_buffer_length++;
        } else {
            uart_putc(USART1, '\n');
            // c == '\n'
            uart_buffer[uart_buffer_length] = '\0';
            uart_buffer_length++;
            uart_puts(USART1, "Sent to GCode processor\n");
            xMessageBufferSend(raw_gcode_buffer, &uart_buffer,
                               uart_buffer_length, 0);

            uart_buffer_length = 0;
        }
    }
}

void task_gcode(void *args __attribute__((unused))) {
    int rc = 0;

    for (;;) {
        char gcode[64];

        size_t len = xMessageBufferReceive(raw_gcode_buffer, &gcode, 64, portMAX_DELAY);

        xMessageBufferReset(raw_gcode_buffer);

        uart_puts(USART1, "Received in GCode processor\n");
        uart_puts(USART1, gcode);
        uart_putc(USART1, '\n');

        (void)len;

        // decode
        gcode_command_s cmd;
        rc = gcode_parse(gcode, len, &cmd);

        if (rc == GCODE_PARSE_UNKNOWN) {
            uart_puts(USART1, "Parse unknown\n");
            // handle error
        } else if (rc == GCODE_PARSE_ERROR) {
            uart_puts(USART1, "Parse error\n");
            // handle error
        } else {
            uart_puts(USART1, "Parse successful\n");
            // TODO handle queue full
            xQueueSend(command_queue, (void *)&cmd, portMAX_DELAY);
        }

        memset(gcode, 0, 64);
    }
}

void task_ui(void *args __attribute__((unused))) {
    for (;;) {}
}

void task_motion(void *args __attribute__((unused))) {
    gcode_command_s cmd;

    for (;;) {
        xQueueReceive(command_queue, &cmd, portMAX_DELAY);

        uart_puts(USART1, "Got command\n");

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

        uart_puts(USART1, "ok\n");
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
    gpio_set_mode(stepper_x.step_port, GPIO_MODE_OUTPUT_10_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, stepper_x.step_pin);
    gpio_set_mode(stepper_y.step_port, GPIO_MODE_OUTPUT_10_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, stepper_y.step_pin);
    gpio_set_mode(stepper_x.dir_port, GPIO_MODE_OUTPUT_10_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, stepper_x.dir_pin);
    gpio_set_mode(stepper_y.dir_port, GPIO_MODE_OUTPUT_10_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, stepper_y.dir_pin);

    gpio_clear(stepper_x.step_port, stepper_x.step_pin);
    gpio_clear(stepper_y.step_port, stepper_y.step_pin);
    gpio_clear(stepper_x.dir_port, stepper_x.dir_pin);
    gpio_clear(stepper_y.dir_port, stepper_y.dir_pin);

    gpio_set_mode(limit_x.port, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, limit_x.pin);
    gpio_set_mode(limit_y.port, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, limit_y.pin);

    nvic_enable_irq(NVIC_EXTI4_IRQ);
    exti_select_source(EXTI4, limit_x.port);
	exti_set_trigger(EXTI4, EXTI_TRIGGER_FALLING);
	exti_enable_request(EXTI4);

    nvic_enable_irq(NVIC_EXTI9_5_IRQ);
    exti_select_source(EXTI5, limit_y.port);
	exti_set_trigger(EXTI5, EXTI_TRIGGER_FALLING);
	exti_enable_request(EXTI5);
}

static void tim_setup(void) {
    /* set up a microsecond free running timer for delay */
	rcc_periph_clock_enable(RCC_TIM6);
	/* microsecond counter */
	timer_set_prescaler(TIM6, rcc_apb1_frequency / 1000000 - 1);
	timer_set_period(TIM6, 0xffff);
	timer_one_shot_mode(TIM6);
}

int main(void) {
    rcc_clock_setup_pll(&rcc_hse_configs[RCC_CLOCK_HSE8_72MHZ]);
    rcc_periph_clock_enable(RCC_USART1);
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_GPIOB);

    gpio_setup();
    usart_setup(USART1);
    tim_setup();

    /*
     * Synchronization
     */
    uart1_queue = xQueueCreate(1, sizeof(char));
    uart2_queue = xQueueCreate(1, sizeof(char));
    raw_gcode_buffer = xMessageBufferCreate(64);
    command_queue = xQueueCreate(1, sizeof(gcode_command_s));

    xTaskCreate(task_gcode, "gcode", 100, NULL, configMAX_PRIORITIES - 2, NULL);
    xTaskCreate(task_uart, "uart", 100, NULL, configMAX_PRIORITIES - 2, NULL);
    // xTaskCreate(task_shell, "shell", 100, NULL, configMAX_PRIORITIES - 3, NULL);
    // xTaskCreate(task_ui, "ui", 100, NULL, configMAX_PRIORITIES - 1, NULL);
    xTaskCreate(task_motion, "motion", 100, NULL, configMAX_PRIORITIES - 1, NULL);

    vTaskStartScheduler();

    do {} while (1);
    return 0;
}
