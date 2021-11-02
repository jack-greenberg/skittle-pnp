#pragma once
#include <stdint.h>

typedef enum {
  FORWARD,
  REVERSE,
} direction_e;

typedef enum {
  FULL,
  HALF,
  QUARTER,
  EIGHTH,
  SIXTEENTH,
} step_size_e;

typedef struct {
  uint16_t step_pin;
  uint16_t dir_pin;

  uint16_t pulse_width; // pulse width in microseconds
} motor_s;

void motor_init(motor_s* motor_cfg);

void motor_rotate(motor_s* motor_cfg, direction_e dir, step_size_e step_size, uint32_t num_steps);
