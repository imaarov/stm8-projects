#include "stm8sc_gpio.h"

void GPIOB5_Init(void)
{
    // initializing proper GPIO for LED
    GPIOB->ODR &= PB5_CLEAR_MASK;       // preload the Port B, Pin 5 ODR = 1 (OUTPUT LOW)
    GPIOB->CR1 |= PB5_MASK;       // configure PB5 as PUSH PULL
    GPIOB->CR2 &= PB5_CLEAR_MASK; // configure PB5 as Slow Ouput
    GPIOB->DDR |= PB5_MASK;       // ... DDR = 1 (mode OUTPUT)
}

void GPIOA3_Init(void)
{

    GPIOA->ODR |= P3_MASK;       // preload the Port B, Pin 5 ODR = 1 (OUTPUT HIGH)
    GPIOA->CR1 |= P3_MASK;       // configure PB5 as PUSH PULL
    GPIOA->CR2 &= P3_CLEAR_MASK; // configure PB5 as Slow Ouput
    GPIOA->DDR |= P3_MASK;       // ... DDR = 1 (mode OUTPUT)
}

void GPIOD3_Init(void)
{
    GPIOD->CR1 |= P3_MASK;       // configure as PULL UP
    GPIOD->CR2 &= P3_CLEAR_MASK; // no interrupt
    GPIOD->DDR &= P3_CLEAR_MASK; // mod INPUT
}