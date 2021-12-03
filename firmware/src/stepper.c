#include "stepper.h"
#include "util.h"

// TODO tune me!
#define STEPPER_DELAY (36000)

void stepper_init(stepper_s stepper) {
    gpio_set_mode(stepper.step.port, GPIO_MODE_OUTPUT_10_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, stepper.step.pin);
    gpio_set_mode(stepper.step.port, GPIO_MODE_OUTPUT_10_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, stepper.step.pin);
}

void stepper_step(stepper_s stepper, uint8_t dir) {
    if (dir == CLOCKWISE) {
        gpio_set(stepper.dir.port, stepper.dir.pin);
    } else {
        gpio_clear(stepper.dir.port, stepper.dir.pin);
    }
    
    // TIM_ARR(TIM6) = 500;
    // TIM_EGR(TIM6) = TIM_EGR_UG;
    // TIM_CR1(TIM6) |= TIM_CR1_CEN;
    // timer_enable_counter(TIM6);
    // while (TIM_CR1(TIM6) & TIM_CR1_CEN);

    gpio_set(stepper.step.port, stepper.step.pin);
    delay(STEPPER_DELAY);

    // TIM_ARR(TIM6) = 500;
    // TIM_EGR(TIM6) = TIM_EGR_UG;
    // TIM_CR1(TIM6) |= TIM_CR1_CEN;
    // timer_enable_counter(TIM6);
    // while (TIM_CR1(TIM6) & TIM_CR1_CEN);

    gpio_clear(stepper.step.port, stepper.step.pin);
    delay(STEPPER_DELAY);
}
