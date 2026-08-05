#include "stm8sc.h" // my custom stm8 header, not the SPL
#include "stm8sc_tim4.h"
#include "stm8sc_clk.h"

#define LOOP_COUNT 70000U

void DelayLoop(void);

void main(void)
{
    // initializing GPIO
    GPIOB_T->ODR |= PB5_MASK;       // preload the Port B, Pin 5 ODR = 1 (OUTPUT HIGH)
    GPIOB_T->CR1 |= PB5_MASK;       // configure PB5 as PUSH PULL
    GPIOB_T->CR2 &= PB5_CLEAR_MASK; // configure PB5 as Slow Ouput
    GPIOB_T->DDR |= PB5_MASK;       // ... DDR = 1 (mode OUTPUT)

    // initializing fMaster Clock for CPU to be the default 16MHz
    // its seems like after reset, clkdiv is set to 4 and the fMaster is 4MHz
    CLK->CKDIVR &= ~(CPUDIV_MASK | HSIDIV_MASK);
    CLK->CKDIVR |= DIV_1;

    // software based Delay
    // while (1) {
    //    GPIOB_T->ODR ^= PB5_MASK;
    //    DelayLoop();
    //}

    // hardware based Delay with TIM4
    TIM4_Init();
    while (1) {
        TIM4_DelayMs(500);
        GPIOB_T->ODR ^= PB5_MASK;
    }
}

// software delay
void DelayLoop(void)
{
    for (volatile uint_32 i = 0; i < LOOP_COUNT; i++);
}