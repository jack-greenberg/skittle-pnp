#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>

#include "pwm.h"
#include "servo.h"
#include "bsp.h"

void servo_init(servo_s servo, int32_t start_position)
{
     pwm_init_timer(&RCC_APB1ENR, RCC_APB1ENR_TIM3EN, servo.timer, PWM_PRESCALE, PWM_PERIOD);

     pwm_init_output_channel(servo.timer, servo.output_channel, &RCC_APB2ENR, RCC_APB2ENR_IOPAEN, servo.gpio_port, servo.gpio_output_number);

     pwm_set_pulse_width(servo.timer, servo.output_channel, start_position);

     pwm_start_timer(servo.timer);
}

void servo_set_position(servo_s servo, uint32_t pos_us)
{
     pwm_set_pulse_width(servo.timer, servo.output_channel, pos_us);
}
