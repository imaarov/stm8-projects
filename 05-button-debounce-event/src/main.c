#include "stm8sc_gpio.h" // my custom stm8 header, not the SPL
#include "stm8sc_tim4.h"
#include "stm8sc_clk.h"
#include "button.h"
#include "led.h"


void main(void)
{
    // set fMaster clock to 16MHz
    CLK_Init_16MHz();

    // set Pin B5(embedded LED on board) A3(external LED) D3(INPUT)
    GPIOB5_Init();
    GPIOA3_Init();
    GPIOD3_Init();

    // setup TIM4, enable INTERRUPT as well
    TIM4_Init();
    TIM4_ENABLE_INTERRUPT();
    TIM4_Start();

    __asm__("rim");

    while (1) {
        // listen for button in PD3
        Button_Update();
        // toggle every 500ms, interrupt, external LED on PA3
        LED_External_P3_Task();
        // toggle only when external button pressed
        LED_Internal_B5_Task();
    }
}
