#include "stm8sc.h" // my custom stm8 header, not the SPL

#define LOOP_COUNT 50000U

void DelayLoop(void);

void main(void)
{
    // initializing GPIO
    GPIOB_T->ODR |= PB5_MASK;       // preload the Port B, Pin 5 ODR = 1 (OUTPUT HIGH)
    GPIOB_T->CR1 |= PB5_MASK;       // configure PB5 as PUSH PULL
    GPIOB_T->CR2 &= PB5_CLEAR_MASK; // configure PB5 as Slow Ouput
    GPIOB_T->DDR |= PB5_MASK;       // ... DDR = 1 (mode OUTPUT)

    // main loop

    while (1) {
        GPIOB_T->ODR ^= PB5_MASK;
        DelayLoop();
    }
}

void DelayLoop(void)
{
    for (volatile uint_16 i = 0; i < LOOP_COUNT; i++) {
        // nop
    }
}