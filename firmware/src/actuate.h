#pragma once

#include <stdbool.h>
#include <stdint.h>

/*
 * Moves in a 2-dimensional linear motion. X and Y are in steps
 */
void move_linear(int32_t x, int32_t y);

/*
 * Moves to 0,0 as fast as possible until limit switches are hit
 */
void move_home(bool x, bool y, bool z);

/*
 * Moves the Z axis servo motor
 */
void move_z_axis(int32_t z);

/*
 * Controls actuation of the solenoid. If closed is `true`, the solenoid closes,
 * if it is `false` the solenoid is opened.
 */
void actuate_solenoid(bool closed);
