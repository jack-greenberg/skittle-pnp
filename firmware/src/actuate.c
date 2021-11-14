#include "actuate.h"
#include "bsp.h"

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
#include <math.h>
#include <stdlib.h>

#define max(X, Y) (((X) > (Y)) ? (X) : (Y))

#define CLOCKWISE (0)
#define COUNTERCLOCKWISE (1)

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

void exti0_isr(void) {
    // Limits
}

static void stepper_step(uint8_t dir, stepper_s* stepper) {
    if (dir == CLOCKWISE) {
        gpio_set(stepper->dir_port, stepper->dir_pin);
    } else {
        gpio_clear(stepper->dir_port, stepper->dir_pin);
    }

    gpio_set(stepper->step_port, stepper->step_pin);

    // wait 500us

    gpio_clear(stepper->step_port, stepper->step_pin);
    
    // wait 500us
}

void move_linear(int32_t x, int32_t y) {
    // For horizontal, move 
    
    int32_t delta_x = x - x_pos;
    int32_t delta_y = y - y_pos;

    float slope = delta_y / delta_x;
    
    uint8_t x_dir = (x > 0) ? CLOCKWISE : COUNTERCLOCKWISE;
    uint8_t y_dir = (y > 0) ? CLOCKWISE : COUNTERCLOCKWISE;

    if (slope > 1) {
        // dy is bigger
        for (uint32_t i = 0; i < delta_y; i++) {
            if (!STOP_Y) {
                stepper_step(y_dir, &stepper_y);
            }

            if ((i % (int)round(slope) == 0) && (i < abs(delta_x)) && (!STOP_X)) {
                stepper_step(x_dir, &stepper_x);
            }
        }
    } else {
        // dx is bigger
        float slope_inv = delta_x / delta_y;

        for (uint32_t i = 0; i < delta_x; i++) {
            if (!STOP_Y) {
                stepper_step(y_dir, &stepper_y);
            }

            if ((i % (int)round(slope_inv) == 0) && (i < abs(delta_y)) && (!STOP_X)) {
                stepper_step(x_dir, &stepper_x);
            }
        }
    }
}

void move_z_axis(int32_t z) {

}

void actuate_solenoid(bool closed) {
    if (closed) {
        gpio_set(solenoid.port, solenoid.pin);
    } else {
        gpio_clear(solenoid.port, solenoid.pin);
    }
}
