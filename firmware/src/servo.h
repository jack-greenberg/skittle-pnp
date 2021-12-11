#pragma once
#include <libopencm3/stm32/timer.h>
#include <stdint.h>

typedef struct {
    uint32_t timer;
    uint32_t output_channel;
    uint32_t gpio_output_number;
    uint32_t gpio_port;
} servo_s;

/**
 * Prescale 72000000 Hz system clock by 72 = 1000000 Hz.
 */
#define PWM_PRESCALE	(72)

/**
 * We need a 50 Hz period (1000 / 20ms = 50), thus devide 100000 by 50 = 20000 (us).
 */
#define PWM_PERIOD		(20000)

/**
 * Initialize and start the PWM used for the servos, drive servos to middle position.
 */
void servo_init(servo_s servo, int32_t start_position);

/**
 * Drive the servo connected to the given channel to the given position in us.
 *
 * @param[in]	pos_us	The position in us to which to drive the servo to.
 */
void servo_set_position(servo_s servo, uint32_t pos_us);
