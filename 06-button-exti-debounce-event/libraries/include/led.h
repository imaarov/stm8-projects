#ifndef LED_H
#define LED_H

#include "stm8sc_gpio.h"

#define LED_TOGGLE_PERIOD_MS 500U
static uint_16 led_last_toggle_time;

void LED_Internal_B5_Task(void);
void LED_External_P3_Task(void);

#endif // !LED_H