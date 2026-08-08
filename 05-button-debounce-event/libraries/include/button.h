#ifndef BUTTON_H
#define BUTTON_H

#include "stm8sc_gpio.h"
#include "stm8sc_tim4.h"

#define BUTTON_TOGGLE_DEBOUNCE 80U

static uint_16 button_state_change_time;

typedef enum 
{
    PRESSED = 0, // pressed in real time, not a state, just an state
    RELEASED, // default
} BUTTON_KEY_STATE;

typedef enum
{
    NO_EVENT,
    BUTTON_PRESSED_EVENT
} Button_Event;

static BUTTON_KEY_STATE state = RELEASED;
static BUTTON_KEY_STATE real_state = RELEASED;
static BUTTON_KEY_STATE previous_real_state = RELEASED;
static Button_Event button_event = NO_EVENT;

void Button_Update(void);
Button_Event Button_GetEvent(void);

#endif // !BUTTON_H