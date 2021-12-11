#include "stepper.h"
#include "util.h"

// TODO tune me!
#define STEPPER_DELAY (7000)

void stepper_init(stepper_s stepper) {
    gpio_set_mode(stepper.step.port, GPIO_MODE_OUTPUT_10_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, stepper.step.pin);

    gpio_set_mode(stepper.dir.port, GPIO_MODE_OUTPUT_10_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, stepper.dir.pin);

    gpio_set_mode(stepper.n_enable.port, GPIO_MODE_OUTPUT_10_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, stepper.n_enable.pin);
}

void stepper_set_dir(stepper_s stepper, uint8_t dir) {
    if (dir == CLOCKWISE) {
        gpio_set(stepper.dir.port, stepper.dir.pin);
    } else {
        gpio_clear(stepper.dir.port, stepper.dir.pin);
    }
}

void stepper_step(stepper_s stepper) {
    if (stepper.step.port == GPIOA) {
        delay(3800); // Y
    } else {
        delay(3600); // X
    }

    gpio_set(stepper.step.port, stepper.step.pin);

    delay(STEPPER_DELAY);

    gpio_clear(stepper.step.port, stepper.step.pin);
}

void stepper_step_both(void) {
    delay(3600);
    gpio_set(stepper_x.step.port, stepper_x.step.pin);

    delay(200);
    gpio_set(stepper_y.step.port, stepper_y.step.pin);

    delay(STEPPER_DELAY);

    gpio_clear(stepper_x.step.port, stepper_x.step.pin);
    gpio_clear(stepper_y.step.port, stepper_y.step.pin);
}
