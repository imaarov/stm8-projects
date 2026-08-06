#include "stm8sc_gpio.h" // my custom stm8 header, not the SPL
#include "stm8sc_tim4.h"
#include "stm8sc_clk.h"

#define LOOP_COUNT 70000U

static uint_16 ms_counter = 0;

void GPIO_Init(void);
void DelayLoop(void);

void main(void)
{
    GPIO_Init();
    CLK_Init_16MHz();

    // software based Delay
    // while (1) {
    //    GPIOB_T->ODR ^= PB5_MASK;
    //    DelayLoop();
    //}

    // hardware based Delay with TIM4
    TIM4_Init();
    TIM4_ENABLE_INTERRUPT();
    TIM4_Start();
    __asm__("rim");
    while (1) {
    }
}
void TIM4_IRS_Handler(void) __interrupt(23)
{
    TIM4->SR1 &= ~TIM4_SR_UIF;

    ms_counter++;
    if (ms_counter >= 500) {
        ms_counter = 0;
        GPIOB_T->ODR ^= PB5_MASK;
    }
}

void GPIO_Init(void)
{
    // initializing proper GPIO for LED
    GPIOB_T->ODR |= PB5_MASK;       // preload the Port B, Pin 5 ODR = 1 (OUTPUT HIGH)
    GPIOB_T->CR1 |= PB5_MASK;       // configure PB5 as PUSH PULL
    GPIOB_T->CR2 &= PB5_CLEAR_MASK; // configure PB5 as Slow Ouput
    GPIOB_T->DDR |= PB5_MASK;       // ... DDR = 1 (mode OUTPUT)
}

// software delay
void DelayLoop(void)
{
    for (volatile uint_32 i = 0; i < LOOP_COUNT; i++);
}
