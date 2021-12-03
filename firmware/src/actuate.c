#include "actuate.h"
#include "bsp.h"
#include "serial.h"
#include "servo.h"

#include <FreeRTOS.h>
#include <task.h>

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/usart.h>
#include <math.h>
#include <stdlib.h>

#define CLOCKWISE (0)
#define COUNTERCLOCKWISE (1)
#define STEP_DELAY (500)

static volatile int32_t x_pos;
static volatile int32_t y_pos;

static volatile bool STOP_X = false;
static volatile bool STOP_Y = false;

extern stepper_s stepper_x;
extern stepper_s stepper_y;
extern pin_s servo;
extern pin_s solenoid;
extern pin_s limit_x;
extern pin_s limit_y;

void exti4_isr(void) {
    // Limit x
    STOP_X = true;
    x_pos = 0;
    exti_reset_request(EXTI4);
}

void exti9_5_isr(void) {
    // Limit y
    STOP_Y = true;
    y_pos = 0;
    exti_reset_request(EXTI5);
}

static void stepper_step(uint8_t dir, stepper_s* stepper) {
    if (dir == CLOCKWISE) {
        gpio_set(stepper->dir_port, stepper->dir_pin);
    } else {
        gpio_clear(stepper->dir_port, stepper->dir_pin);
    }
    
    TIM_ARR(TIM6) = 500;
    TIM_EGR(TIM6) = TIM_EGR_UG;
    TIM_CR1(TIM6) |= TIM_CR1_CEN;
    timer_enable_counter(TIM6);
    while (TIM_CR1(TIM6) & TIM_CR1_CEN);

    gpio_set(stepper->step_port, stepper->step_pin);

    TIM_ARR(TIM6) = 500;
    TIM_EGR(TIM6) = TIM_EGR_UG;
    TIM_CR1(TIM6) |= TIM_CR1_CEN;
    timer_enable_counter(TIM6);
    while (TIM_CR1(TIM6) & TIM_CR1_CEN);

    gpio_clear(stepper->step_port, stepper->step_pin);
}

void move_linear(int32_t x, int32_t y) {
    // For horizontal, move 

    int32_t delta_x = x;// - x_pos;
    int32_t delta_y = y;// - y_pos;

    float slope = delta_y / delta_x;
    float inv_slope = delta_x / delta_y;
    
    uint8_t x_dir = (x > 0) ? COUNTERCLOCKWISE : CLOCKWISE;
    uint8_t y_dir = (y > 0) ? CLOCKWISE : COUNTERCLOCKWISE;

    if (delta_y == 0) {
        // Just move X
        for (int32_t i = 0; i < abs(delta_x); i++) {
            if (gpio_get(limit_x.port, limit_x.pin) || (x > 0)) {
                stepper_step(x_dir, &stepper_x);
            }

            uart_puts(USART1, "\b");
        }
    } else if (delta_x == 0) {
        // Just move Y
        for (int32_t i = 0; i < abs(delta_y); i++) {
            if (gpio_get(limit_y.port, limit_y.pin) || (y > 0)) {
                stepper_step(y_dir, &stepper_y);
            }
            uart_puts(USART1, "\b\b");
        }
    } else if (slope >= 1) {
        // Y is bigger
        for (int32_t i = 0; i < abs(delta_y); i++) {
            if (gpio_get(limit_y.port, limit_y.pin) || (y > 0)) {
                stepper_step(y_dir, &stepper_y);
            }

            if (i % (int)slope == 0) {
                if (gpio_get(limit_x.port, limit_x.pin) || (y > 0)) {
                    stepper_step(x_dir, &stepper_x);
                }
            }
            uart_puts(USART1, "\b\b");
        }
    } else {
        // X is bigger
        for (int32_t i = 0; i < abs(delta_x); i++) {
            if (gpio_get(limit_x.port, limit_x.pin) || (x > 0)) {
                stepper_step(x_dir, &stepper_x);
            }

            if (i % (int)inv_slope == 0) {
                if (gpio_get(limit_y.port, limit_y.pin) || (y > 0)) {
                    stepper_step(y_dir, &stepper_y);
                }
            }

            uart_puts(USART1, "\b\b");
        }
    }
}

void move_home(bool x, bool y, bool z) {
    if (z) {
        move_z_axis(950);
    }

    bool stop_x = false;
    bool stop_y = false;

    while (true) {
        if (gpio_get(limit_x.port, limit_x.pin)) {
            stepper_step(CLOCKWISE, &stepper_x);
        } else {
            stop_x = true;
        }

        if (gpio_get(limit_y.port, limit_y.pin)) {
            stepper_step(COUNTERCLOCKWISE, &stepper_y);
        } else {
            stop_y = true;
        }

        if (stop_x && stop_y) {
            break;
        }

        uart_puts(USART1, "\b\b");
    }
}

void move_z_axis(int32_t z) {
    // timer_set_oc_value(TIM3, TIM_OC3, z);
    servo_set_position(SERVO_CH1, z);
    // timer_enable_oc_output(TIM2, TIM_OC3);
}

void actuate_solenoid(bool closed) {
    if (closed) {
        gpio_set(solenoid.port, solenoid.pin);
    } else {
        gpio_clear(solenoid.port, solenoid.pin);
    }
}
