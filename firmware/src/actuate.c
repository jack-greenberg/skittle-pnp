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
#include <libopencm3/stm32/f1/nvic.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/usart.h>
#include <math.h>
#include <stdlib.h>

enum Pos {
    MIN,
    MAX,
    NONE,
} x_extreme, y_extreme = NONE;

static volatile int32_t x_pos;
static volatile int32_t y_pos;

static volatile bool STOP_X = false;
static volatile bool STOP_Y = false;

void exti9_5_isr(void) {
    STOP_X = true;

    if (!gpio_get(limit_x_min.port, limit_x_min.pin)) {
        x_extreme = MIN;
    }

    if (!gpio_get(limit_x_max.port, limit_x_max.pin)) {
        x_extreme = MAX;
    }
    exti_reset_request(LIMIT_X_MIN_IRQ);
    exti_reset_request(LIMIT_X_MAX_IRQ);

}

void exti15_10_isr(void) {
    STOP_Y = true;

    if (!gpio_get(limit_y_min.port, limit_y_min.pin)) {
        y_extreme = MIN;
    }

    if (!gpio_get(limit_y_max.port, limit_y_max.pin)) {
        y_extreme = MAX;
    }

    exti_reset_request(LIMIT_Y_MIN_IRQ);
    exti_reset_request(LIMIT_Y_MAX_IRQ);
}

void move_linear(int32_t x, int32_t y) {
    // For horizontal, move 

    // TODO: absolute positioning
    int32_t delta_x = x;// - x_pos;
    int32_t delta_y = y;// - y_pos;

    int slope = (int)(abs(delta_y / delta_x));
    int inv_slope = (int)(abs(delta_x / delta_y));
    
    uint8_t x_dir = (x > 0) ? COUNTERCLOCKWISE : CLOCKWISE;
    uint8_t y_dir = (y > 0) ? COUNTERCLOCKWISE : CLOCKWISE;

    STOP_X = false;
    STOP_Y = false;

    if (!gpio_get(limit_x_min.port, limit_x_min.pin) && x <= 0) {
        STOP_X = true;
    }

    if (!gpio_get(limit_x_max.port, limit_x_max.pin) && x >= 0) {
        STOP_X = true;
    }

    if (!gpio_get(limit_y_min.port, limit_y_min.pin) && y <= 0) {
        STOP_Y = true;
    }

    if (!gpio_get(limit_y_max.port, limit_y_max.pin) && y >= 0) {
        STOP_Y = true;
    }

    stepper_set_dir(stepper_x, x_dir);
    stepper_set_dir(stepper_y, y_dir);

    if (delta_y == 0) {
        // Just move X
        for (int32_t i = 0; i < abs(delta_x); i++) {
            if (!STOP_X) {
                stepper_step(stepper_x);
            }
        }
    } else if (delta_x == 0) {
        // Just move Y
        for (int32_t i = 0; i < abs(delta_y); i++) {
            if (!STOP_Y) {
                stepper_step(stepper_y);
            }
        }
    } else if (slope >= 1) {
        // Y is bigger
        for (int32_t i = 0; i < abs(delta_y); i++) {

            if (i % (int)slope == 0) {
                if (!STOP_X && !STOP_Y) {
                    stepper_step_both();
                };
            } else {
                if (!STOP_Y) {
                    stepper_step(stepper_y);
                }
            }

            if (STOP_X && STOP_Y) {
                break;
            }
        }
    } else {
        // X is bigger
        for (int32_t i = 0; i < abs(delta_x); i++) {
            if (i % (int)inv_slope == 0) {
                if (!STOP_Y && !STOP_X) {
                    stepper_step_both();
                }
            } else {
                if (!STOP_X) {
                    stepper_step(stepper_x);
                }
            }

            if (STOP_X && STOP_Y) {
                break;
            }
        }
    }

    STOP_X = false;
    STOP_Y = false;
}

void move_home(bool x, bool y, bool z) {
    if (z) {
        move_z_axis(950);
    }

    bool stop_x = false;
    bool stop_y = false;

    stepper_set_dir(stepper_x, CLOCKWISE);
    stepper_set_dir(stepper_y, CLOCKWISE);

    while (true) {
        if (!gpio_get(limit_x_min.port, limit_x_min.pin)) {
            stop_x = true;
        }

        if (!gpio_get(limit_y_min.port, limit_y_min.pin)) {
            stop_y = true;
        }

        if (stop_x && stop_y) {
            break;
        } else if (stop_x) {
            stepper_step(stepper_y);
        } else if (stop_y) {
            stepper_step(stepper_x);
        } else {
            stepper_step_both();
        }

        delay(2700);

        if (stop_x && stop_y) {
            break;
        }
    }

    delay(1000);

    stepper_set_dir(stepper_x, COUNTERCLOCKWISE);
    stepper_set_dir(stepper_y, COUNTERCLOCKWISE);

    for (uint8_t i = 0; i < 20; i++) {
        stepper_step_both();
    }
}

void move_z_axis(int32_t z) {
    // Enforce bounds
    if (z < Z_MIN) {
        z = Z_MIN;
    }

    if (z > Z_MAX) {
        z = Z_MAX;
    }

    servo_set_position(servo_z, z);
}

void actuate_solenoid(bool closed) {
    if (closed) {
        gpio_set(solenoid.port, solenoid.pin);
    } else {
        gpio_clear(solenoid.port, solenoid.pin);
    }
}

void enable_motors(bool enabled) {
    if (enabled) {
        gpio_set(stepper_x.n_enable.port, stepper_x.n_enable.pin);
        gpio_set(stepper_y.n_enable.port, stepper_y.n_enable.pin);
    } else {
        gpio_clear(stepper_x.n_enable.port, stepper_x.n_enable.pin);
        gpio_clear(stepper_y.n_enable.port, stepper_y.n_enable.pin);
    }
}

void open_feeder(bool open) {
    if (open) {
        servo_set_position(servo_feeder, 0);
    } else {
        servo_set_position(servo_feeder, 95);
    }
}
