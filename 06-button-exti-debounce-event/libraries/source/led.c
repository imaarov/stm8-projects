#include "led.h"
#include "button.h"

static uint_16 led_last_toggle_time = 0;

void LED_Internal_B5_Task(void)
{
    if (Button_GetEvent() == BUTTON_PRESSED_EVENT)
    {
        GPIOB_T->ODR ^= PB5_MASK;
    }
}

void LED_External_P3_Task(void)
{
    if (system_tick_ms - led_last_toggle_time >= LED_TOGGLE_PERIOD_MS)
    {
        led_last_toggle_time = system_tick_ms;
        GPIOA->ODR ^= P3_MASK;
    }
    
}