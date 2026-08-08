#ifndef STM8SC_EXTI_H
#define STM8SC_EXTI_H

#include "stm8sc_gpio.h"

#define EXTI_Address 0x50A0U
#define EXTI_CR1_PD_BOTH_EDGE  (0x03U << 6) // set bit[7:6]=11 - falling and rising edge

extern volatile uint_8 button_interrupt;

typedef struct
{
    volatile uint_8 CR1;
    volatile uint_8 CR2;
} EXTI_T;

#define EXTI ((EXTI_T *) EXTI_Address)

// API
void SET_PD_BOTH_EDGE_SENSITIVITY(void);
void EXTI_PD_ISR_Handler(void) __interrupt(6);

#endif // !STM8SC_EXTI_H