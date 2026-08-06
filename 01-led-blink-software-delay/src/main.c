#include "stm8sc_gpio.h" // my custom stm8 header, not the SPL

#define LOOP_COUNT 70000U

void GPIO_Init(void);
void DelayLoop(void);

void main(void)
{
    GPIO_Init();
    // software based Delay
    while (1) {
        GPIOB_T->ODR ^= PB5_MASK;
        DelayLoop();
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
