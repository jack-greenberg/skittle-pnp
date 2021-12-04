#pragma once

#include "bsp.h"

#define CLOCKWISE (0)
#define COUNTERCLOCKWISE (1)

typedef struct {
    pin_s step;
    pin_s dir;
    pin_s n_enable;
} stepper_s;

extern stepper_s stepper_x;
extern stepper_s stepper_y;

void stepper_init(stepper_s stepper);

void stepper_step(stepper_s stepper, uint8_t dir);
