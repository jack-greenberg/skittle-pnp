/*
 * Board support package -- defines the pins used
 */
#pragma once
#include <stdint.h>

typedef struct {
    uint32_t port;
    uint16_t pin;
} pin_s;
