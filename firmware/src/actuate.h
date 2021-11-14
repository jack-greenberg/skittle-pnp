#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    int16_t step_pin;
    int32_t step_port;
    int16_t dir_pin;
    int32_t dir_port;
    int16_t enable_pin;
    int32_t enable_port;
} stepper_s;

/*
 * Moves in a 2-dimensional linear motion. X and Y are in steps
 */
void move_linear(int32_t x, int32_t y);

/*
 * Moves the Z axis servo motor
 */
void move_z_axis(int32_t z);

/*
 * Controls actuation of the solenoid. If closed is `true`, the solenoid closes,
 * if it is `false` the solenoid is opened.
 */
void actuate_solenoid(bool closed);
