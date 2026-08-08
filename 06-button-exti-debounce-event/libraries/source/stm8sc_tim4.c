#include "stm8sc_tim4.h"

volatile uint_16 system_tick_ms = 0;

void TIM4_Init(void)
{
    TIM4->CR1 &= ~TIM4_CR1_CEN;
    TIM4->PSCR = Prescaler_128;
    TIM4->ARR  = 124;
    TIM4->CNTR = 0;
    TIM4->SR1 &= ~TIM4_SR_UIF;
}

void TIM4_ENABLE_INTERRUPT(void)
{
    TIM4->IER |= TIM4_IER_UIE;
}

void TIM4_Start(void)
{
    TIM4->CR1 |= TIM4_CR1_CEN;
}

void TIM4_DelayMs(uint_16 ms)
{
    TIM4->CR1 &= ~TIM4_CR1_CEN;

    TIM4->CNTR = 0;
    TIM4->SR1 &= ~TIM4_SR_UIF;

    TIM4->CR1 |= TIM4_CR1_CEN;

    while (ms) {
        // use while for better readbility instead of if
        while ((TIM4->SR1 & TIM4_SR_UIF) == 0) {
        }

        TIM4->SR1 &= ~TIM4_SR_UIF;
        --ms;
    }

    TIM4->CR1 &= ~TIM4_CR1_CEN;
}

void TIM4_ISR_Handler(void) __interrupt(23)
{
    TIM4->SR1 &= ~TIM4_SR_UIF;
    system_tick_ms++;
}
