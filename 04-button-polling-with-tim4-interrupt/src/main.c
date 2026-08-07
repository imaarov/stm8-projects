#include "stm8sc_gpio.h" // my custom stm8 header, not the SPL
#include "stm8sc_tim4.h"
#include "stm8sc_clk.h"

void GPIOA3_Init(void);
void GPIOD3_Init(void);
void GPIOB5_Init(void);

void main(void)
{
    CLK_Init_16MHz();

    GPIOB5_Init(); // embedded STM8 LED
    GPIOA3_Init(); // external LED that connected through the A3 pin
    GPIOD3_Init(); // INPUT pin that connected to the button

    // hardware based Delay with TIM4
    TIM4_Init();
    TIM4_ENABLE_INTERRUPT();
    TIM4_Start();
    __asm__("rim");

    while (1) {
        if ((GPIOD->IDR & (1U << 3)) == 0)
        {
            GPIOB_T->ODR ^= PB5_MASK;
        }
        // uncomment if you want to ignore the bouncing effects
        //else
        //{
        //    GPIOB_T->ODR &= PB5_CLEAR_MASK;
        //}
    }
}

void GPIOB5_Init(void)
{
    // initializing proper GPIO for LED
    GPIOB_T->ODR &= PB5_CLEAR_MASK;       // preload the Port B, Pin 5 ODR = 1 (OUTPUT LOW)
    GPIOB_T->CR1 |= PB5_MASK;       // configure PB5 as PUSH PULL
    GPIOB_T->CR2 &= PB5_CLEAR_MASK; // configure PB5 as Slow Ouput
    GPIOB_T->DDR |= PB5_MASK;       // ... DDR = 1 (mode OUTPUT)
}

void GPIOA3_Init(void)
{
    GPIOA->ODR |= P3_MASK;       // preload the Port A, Pin 3 ODR = 1 (OUTPUT HIGH)
    GPIOA->CR1 |= P3_MASK;       // configure PA3 as PUSH PULL
    GPIOA->CR2 &= P3_CLEAR_MASK; // configure PA3 as Slow Ouput
    GPIOA->DDR |= P3_MASK;       // ... DDR = 1 (mode OUTPUT)
}

void GPIOD3_Init(void)
{
    GPIOD->CR1 |= P3_MASK;       // configure as PULL UP (key pressed = 0 otherwise = 1)
    GPIOD->CR2 &= P3_CLEAR_MASK; // no interrupt
    GPIOD->DDR &= P3_CLEAR_MASK; // mod INPUT
}