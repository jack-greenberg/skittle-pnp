#include "bsp.h"
#include "stepper.h"

// TODO jack: update the TIM config
pin_s servo = {
    .pin = GPIO8,
    .port = GPIOA,
};

pin_s solenoid = {
    .pin = GPIO1,
    .port = GPIOA,
};

pin_s limit_x_min = {
    .pin = GPIO8,
    .port = GPIOB,
};

pin_s limit_x_max = {
    .pin = GPIO9,
    .port = GPIOB,
};

pin_s limit_y_min = {
    .pin = GPIO12,
    .port = GPIOB,
};

pin_s limit_y_max = {
    .pin = GPIO13,
    .port = GPIOB,
};

stepper_s stepper_x = {
    .step = {
        .pin = GPIO4,
        .port = GPIOB,
    },
    .dir = {
        .pin = GPIO5,
        .port = GPIOB,
    },
    .n_enable = {
        .pin = GPIO11,
        .port = GPIOA,
    }
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
