#include "stm8sc_exti.h"

volatile uint_8 button_interrupt = 0;

void SET_PD_BOTH_EDGE_SENSITIVITY(void)
{
    EXTI->CR1 &= ~(0x03U << 6);
    EXTI->CR1 |= EXTI_CR1_PD_BOTH_EDGE;
}

void EXTI_PD_ISR_Handler(void) __interrupt(6)
{
    button_interrupt = 1;
}