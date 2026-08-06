#include "stm8sc_gpio.h" // my custom stm8 header, not the SPL
#include "stm8sc_tim4.h"
#include "stm8sc_clk.h"

void GPIO_Init(void);
void DelayLoop(void);

void main(void)
{
    GPIO_Init();
    CLK_Init_16MHz();

    // hardware based Delay with TIM4 (polling, busy wait)
    TIM4_Init();
    while (1) {
        TIM4_DelayMs(500);
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