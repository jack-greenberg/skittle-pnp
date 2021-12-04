#include "actuate.h"
#include "bsp.h"
#include "serial.h"
#include "servo.h"
#include "stepper.h"
#include "util.h"

#include <FreeRTOS.h>
#include <task.h>

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/usart.h>
#include <math.h>
#include <stdlib.h>

enum Pos {
    MIN,
    MAX,
} x_extreme, y_extreme;

static volatile int32_t x_pos;
static volatile int32_t y_pos;

static volatile bool STOP_X = false;
static volatile bool STOP_Y = false;

void exti9_5_isr(void) {
    STOP_X = true;
}

// void exti15_10_isr(void) {
//     STOP_Y = true;
// }

// void exti4_isr(void) {
//     // Limit x
//     STOP_X = true;
//     x_pos = 0;
//     exti_reset_request(EXTI4);
// }
// 
// void exti9_5_isr(void) {
//     // Limit y
//     STOP_Y = true;
//     y_pos = 0;
//     exti_reset_request(EXTI5);
// }

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
            if (gpio_get(limit_x_min.port, limit_x_min.pin) || (x > 0)) {
                stepper_step(stepper_x, x_dir);
            }
        }
    } else if (delta_x == 0) {
        // Just move Y
        for (int32_t i = 0; i < abs(delta_y); i++) {
            if (gpio_get(limit_y_min.port, limit_y_min.pin) || (y > 0)) {
                stepper_step(stepper_y, y_dir);
            }
        }
    } else if (slope >= 1) {
        // Y is bigger
        for (int32_t i = 0; i < abs(delta_y); i++) {
            if (gpio_get(limit_y_min.port, limit_y_min.pin) || (y > 0)) {
                stepper_step(stepper_y, y_dir);
            }

            if (i % (int)slope == 0) {
                if (gpio_get(limit_x_min.port, limit_x_min.pin) || (y > 0)) {
                    stepper_step(stepper_x, x_dir);
                }
            }
        }
    } else {
        // X is bigger
        for (int32_t i = 0; i < abs(delta_x); i++) {
            if (gpio_get(limit_x_min.port, limit_x_min.pin) || (x > 0)) {
                stepper_step(stepper_x, x_dir);
            }

            if (i % (int)inv_slope == 0) {
                if (gpio_get(limit_y_min.port, limit_y_min.pin) || (y > 0)) {
                    stepper_step(stepper_y, y_dir);
                }
            }
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
        if (gpio_get(limit_x_min.port, limit_x_min.pin)) {
            stepper_step(stepper_x, CLOCKWISE);
        } else {
            stop_x = true;
        }

        if (gpio_get(limit_y_min.port, limit_y_min.pin)) {
            stepper_step(stepper_y, COUNTERCLOCKWISE);
        } else {
            stop_y = true;
        }

        if (stop_x && stop_y) {
            break;
        }
    }
}

void move_z_axis(int32_t z) {
    // Enforce bounds
    if (z < SERVO_MIN) {
        z = SERVO_MIN;
    }

    if (z > SERVO_MAX) {
        z = SERVO_MAX;
    }

    servo_set_position(SERVO_TIM_OC, z);
}

void actuate_solenoid(bool closed) {
    if (closed) {
        gpio_set(solenoid.port, solenoid.pin);
    } else {
        gpio_clear(solenoid.port, solenoid.pin);
    }
}
