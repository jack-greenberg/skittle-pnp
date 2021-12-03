#pragma once
#include <stdint.h>
#include <stdlib.h>

inline void delay(uint32_t t) {
    for (uint32_t i = 0; i < t; i++) {
        __asm("nop");
    }
}
