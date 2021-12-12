#include "bsp.h"
#include "stepper.h"
#include "servo.h"
#include <libopencm3/stm32/timer.h>

// TODO jack: update the TIM config
servo_s servo_z = {
    .timer = TIM1,
    .output_channel = TIM_OC1,
    .gpio_output_number = GPIO_TIM1_CH1,
    .gpio_port = GPIOA,
};

// TODO
servo_s servo_feeder = {
    .timer = TIM3,
    .output_channel = TIM_OC1,
    .gpio_output_number = GPIO_TIM3_CH1,
    .gpio_port = GPIOB,
};

pin_s solenoid = {
    .pin = GPIO1,
    .port = GPIOA,
};

pin_s limit_x_min = {
    .pin = GPIO9,
    .port = GPIOB,
};

pin_s limit_x_max = {
    .pin = GPIO8,
    .port = GPIOB,
};

pin_s limit_y_min = {
    .pin = GPIO13,
    .port = GPIOB,
};

pin_s limit_y_max = {
    .pin = GPIO12,
    .port = GPIOB,
};

stepper_s stepper_x = {
    .step = {
        .pin = GPIO1,
        .port = GPIOB,
    },
    .dir = {
        .pin = GPIO0,
        .port = GPIOB,
    },
    .n_enable = {
        .pin = GPIO11,
        .port = GPIOA,
    },
};

stepper_s stepper_y = {
    .step = {
        .pin = GPIO7,
        .port = GPIOA,
    },
    .dir = {
        .pin = GPIO6,
        .port = GPIOA,
    },
    .n_enable = {
        .pin = GPIO11,
        .port = GPIOB,
    }
};
