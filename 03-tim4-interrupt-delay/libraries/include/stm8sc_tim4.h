#ifndef STM8SC_TIM4_H
#define STM8SC_TIM4_H

#include "stm8sc_gpio.h"

#define TIM4_Address 0x5340

typedef struct
{
    volatile uint_8 CR1;
#if defined(STM8S103) || defined(STM8S003) || defined(STM8S001)
    volatile uint_8 RESERVED1; // reserved register (on some devices)
    volatile uint_8 RESERVED2; // reserved register (on some devices)
#endif
    volatile uint_8 IER;
    volatile uint_8 SR1;
    volatile uint_8 EGR;
    volatile uint_8 CNTR;
    volatile uint_8 PSCR;
    volatile uint_8 ARR;
} TIM4_T;

enum Prescaler {
    Prescaler_1   = 0,
    Prescaler_2   = 1,
    Prescaler_4   = 2,
    Prescaler_8   = 3,
    Prescaler_16  = 4,
    Prescaler_32  = 5,
    Prescaler_64  = 6,
    Prescaler_128 = 7
};

#define TIM4_CR1_CEN (1U << 0)
#define TIM4_SR_UIF  (1U << 0)
#define TIM4_IER_UIE (1U << 0)

#define TIM4         ((TIM4_T *)TIM4_Address)

// API
void TIM4_Init(void);
void TIM4_DelayMs(uint_16 ms);
void TIM4_ENABLE_INTERRUPT(void);
void TIM4_Start(void);
void TIM4_IRS_Handler(void) __interrupt(23);

#endif // !STM8SC_TIM4_H