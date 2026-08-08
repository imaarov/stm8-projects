#include "button.h"

static uint_16 button_state_change_time = 0;

void Button_Update(void)
{
    BUTTON_KEY_STATE current_state = (GPIOD->IDR & (1U << 3)) == 0 ? PRESSED : RELEASED;
    if (current_state != state) // we have new state
    {
        button_state_change_time = system_tick_ms;
        state = current_state;
    }

    if ((system_tick_ms - button_state_change_time >= BUTTON_TOGGLE_DEBOUNCE))
    {
        if (current_state == state) // state remain the same thing as before as debounce period
        {
            real_state = state;
            if(previous_real_state == RELEASED && real_state == PRESSED) // change state from release to pressed
            {
                button_event = BUTTON_PRESSED_EVENT;
            }
            previous_real_state = real_state;
        }
    }
}

Button_Event Button_GetEvent(void)
{
    Button_Event event = button_event;
    button_event = NO_EVENT;
    return event;
}