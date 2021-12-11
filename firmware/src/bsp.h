/*
 * Board support package -- defines the pins used
 */
#pragma once

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
#include <stdint.h>
#include "servo.h"

#define LIMIT_X_MIN_IRQ (EXTI7)
#define LIMIT_X_MAX_IRQ (EXTI9)
#define LIMIT_Y_MIN_IRQ (EXTI12)
#define LIMIT_Y_MAX_IRQ (EXTI13)

typedef struct {
    uint32_t port;
    uint16_t pin;
} pin_s;

#define SERVO_Z_TIM_OC (TIM_OC1)
#define SERVO_Z_TIM_GPIO_CH (GPIO_TIM1_CH1)
#define SERVO_Z_TIM (TIM1)
#define SERVO_Z_GPIO_PORT (GPIOA)

extern pin_s solenoid;
extern pin_s limit_x_min;
extern pin_s limit_y_min;
extern pin_s limit_x_max;
extern pin_s limit_y_max;
extern servo_s servo_z;
extern servo_s servo_feeder;
