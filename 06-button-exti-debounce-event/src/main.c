#include "stm8sc_gpio.h" // my custom stm8 header, not the SPL
#include "stm8sc_tim4.h"
#include "stm8sc_clk.h"
#include "stm8sc_exti.h"
#include "button.h"
#include "led.h"


void main(void)
{
    // set fMaster clock to 16MHz
    CLK_Init_16MHz();

    // set Pin B5(embedded LED on board) A3(external LED) D3(INPUT) (with interrupt)
    GPIOB5_Init();
    GPIOA3_Init();
    GPIOD3_Init();

    // set interrupt type for PD to be falling edge(because of pull up)
    SET_PD_BOTH_EDGE_SENSITIVITY();


    // setup TIM4, enable INTERRUPT as well
    TIM4_Init();
    TIM4_ENABLE_INTERRUPT();
    TIM4_Start();
    __asm__("rim");

    while (1) {
        Button_Task();
        LED_External_P3_Task();
        LED_Internal_B5_Task();
    }
}
