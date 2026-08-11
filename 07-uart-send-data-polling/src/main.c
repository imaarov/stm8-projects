#include "stm8sc_gpio.h" // my custom stm8 header, not the SPL
#include "stm8sc_clk.h"
#include "stm8sc_tim4.h"
#include "stm8sc_uart1.h"

#define UART1_DATA_SEND_MS 300

static uint_16 uart1_last_data_time = 0;

void UART1_DATA_TASK(void);

void main(void)
{
    // init fMaster clock to 16MHz
    CLK_Init_16MHz();

    // init PD5 and PD6 on for acting as RXD and TXD
    GPIOD5_Init();
    GPIOD6_Init();

    // init tim4
    TIM4_Init();
    TIM4_ENABLE_INTERRUPT();
    TIM4_Start();
    __asm__("rim");

    // init uart1
    UART1_Init();
    UART1_Prompt();

    while (1) {
        UART1_DATA_TASK();
    }
}

void UART1_DATA_TASK(void)
{
    // send data 1ms through UART1
    if (system_tick_ms - uart1_last_data_time >= UART1_DATA_SEND_MS)
    {
        uart1_last_data_time = system_tick_ms;
        UART1_SendString("UART1: TICK\r\n");
    }
}
