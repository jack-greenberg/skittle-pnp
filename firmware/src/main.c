#include <FreeRTOS.h>
#include <message_buffer.h>
#include <queue.h>
#include <task.h>

#include <libopencm3/stm32/f1/nvic.h>
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
#include "stepper.h"
#include "servo.h"

// Queue for UART characters to be processed
xQueueHandle uart2_queue;
MessageBufferHandle_t raw_gcode_buffer;
xQueueHandle command_queue;

void usart2_isr(void) {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    char c = usart_recv(USART2);

    xQueueSendFromISR(uart2_queue, &c, &xHigherPriorityTaskWoken);
}

void task_uart(void *args __attribute__((unused))) {
    uint8_t uart_buffer[64];
    uint8_t uart_buffer_length = 0;
    char c;

    for (;;) {
        // Block until UART received
        xQueueReceive(uart2_queue, &c, portMAX_DELAY);
        uart_putc(USART2, c);

        if (c != '\r') {
            uart_buffer[uart_buffer_length] = c;
            uart_buffer_length++;
        } else {
            uart_putc(USART2, '\n');
            // c == '\n'
            uart_buffer[uart_buffer_length] = '\0';
            uart_buffer_length++;
            xMessageBufferSend(raw_gcode_buffer, &uart_buffer,
                               uart_buffer_length, 0);

            uart_buffer_length = 0;
        }
    }
}

void task_gcode(void *args __attribute__((unused))) {
    int rc = 0;

    for (;;) {
        char gcode[64] = {0};

        size_t len = xMessageBufferReceive(raw_gcode_buffer, &gcode, 64, portMAX_DELAY);

        xMessageBufferReset(raw_gcode_buffer);

        // decode
        gcode_command_s cmd = {0};
        rc = gcode_parse(gcode, len, &cmd);

        if (rc == GCODE_PARSE_UNKNOWN) {
            uart_puts(USART2, "Parse unknown\n");
        } else if (rc == GCODE_PARSE_ERROR) {
            uart_puts(USART2, "Parse error\n");
        } else {
            xQueueSend(command_queue, (void *)&cmd, portMAX_DELAY);
        }
    }
}

void task_ui(void *args __attribute__((unused))) {
    for (;;) {}
}

void task_motion(void *args __attribute__((unused))) {
    gcode_command_s cmd = {0};

    for (;;) {
        xQueueReceive(command_queue, &cmd, portMAX_DELAY);

        switch (cmd.type) {
            case G01: {
                move_z_axis(cmd.g01.z);
                move_linear(cmd.g01.x, cmd.g01.y);
            } break;
            case G28: {
                move_home(cmd.g28.x, cmd.g28.y, cmd.g28.z);
            } break;
            case G400: {
                enable_motors(true);
            } break;
            case G401: {
                enable_motors(false);
            } break;
            case M400: {
                actuate_solenoid(false);
            } break;
            case M401: {
                actuate_solenoid(true);
            } break;
            case M410: {
                open_feeder(true);
            } break;
            case M411: {
                open_feeder(false);
            } break;
        }

        uart_puts(USART2, "ok\r\n");
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

    usart_set_baudrate(uart, 9600);
    usart_set_databits(uart, 8);
    usart_set_stopbits(uart, USART_STOPBITS_1);
    usart_set_mode(uart, USART_MODE_TX_RX);
    // usart_set_parity(uart, USART_PARITY_NONE);
    // usart_set_flow_control(uart, USART_FLOWCONTROL_NONE);

    switch (uart) {
        case USART1: {
            // nvic_enable_irq(NVIC_USART1_IRQ);
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

static void limit_setup(void) {
    nvic_enable_irq(NVIC_EXTI9_5_IRQ);
    nvic_enable_irq(NVIC_EXTI15_10_IRQ);

    gpio_set_mode(limit_x_min.port, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, limit_x_min.pin);
    exti_set_trigger(LIMIT_X_MIN_IRQ, EXTI_TRIGGER_FALLING);
    exti_select_source(LIMIT_X_MIN_IRQ, limit_x_min.port);
    exti_enable_request(LIMIT_X_MIN_IRQ);

    gpio_set_mode(limit_y_min.port, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, limit_y_min.pin);
    exti_select_source(LIMIT_Y_MIN_IRQ, limit_y_min.port);
    exti_set_trigger(LIMIT_Y_MIN_IRQ, EXTI_TRIGGER_FALLING);
    exti_enable_request(LIMIT_Y_MIN_IRQ);

    gpio_set_mode(limit_x_max.port, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, limit_x_max.pin);
    exti_select_source(LIMIT_X_MAX_IRQ, limit_x_max.port);
    exti_set_trigger(LIMIT_X_MAX_IRQ, EXTI_TRIGGER_FALLING);
    exti_enable_request(LIMIT_X_MAX_IRQ);

    gpio_set_mode(limit_y_max.port, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, limit_y_max.pin);
    exti_select_source(LIMIT_Y_MAX_IRQ, limit_y_max.port);
    exti_set_trigger(LIMIT_Y_MAX_IRQ, EXTI_TRIGGER_FALLING);
    exti_enable_request(LIMIT_Y_MAX_IRQ);
}

int main(void) {
    rcc_clock_setup_pll(&rcc_hse_configs[RCC_CLOCK_HSE8_72MHZ]);
    rcc_periph_clock_enable(RCC_USART2);
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_AFIO);

    limit_setup();
    usart_setup(USART2);

    /*
     * Steppers
     */
    stepper_init(stepper_x);
    stepper_init(stepper_y);

    /*
     * Servos
     */
    servo_init(servo_z, Z_MIN);
    servo_set_position(servo_z, 950);
    servo_init(servo_feeder, 950);
    servo_set_position(servo_feeder, 950);

    /*
     * Valve
     */
    gpio_set_mode(solenoid.port, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, solenoid.pin);

    /*
     * Synchronization
     */
    uart2_queue = xQueueCreate(1, sizeof(char));
    raw_gcode_buffer = xMessageBufferCreate(64);
    command_queue = xQueueCreate(1, sizeof(gcode_command_s));

    xTaskCreate(task_gcode, "gcode", 100, NULL, configMAX_PRIORITIES - 2, NULL);
    xTaskCreate(task_uart, "uart", 100, NULL, configMAX_PRIORITIES - 2, NULL);
    xTaskCreate(task_motion, "motion", 100, NULL, configMAX_PRIORITIES - 1, NULL);

    vTaskStartScheduler();

    do {} while (1);
    return 0;
}
