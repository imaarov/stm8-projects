#include "stm8sc_gpio.h"
#include "stm8sc_clk.h"
#include "stm8sc_uart1.h"
#include "stm8sc_tim4.h"

#define LED_BLINK_PERIOD 300U

typedef enum {
    DATA_RECIEVED = 0,
    DATA_NOT_RECEIVED,
} UART_EVENT;

volatile UART_EVENT uart_event     = DATA_NOT_RECEIVED;
volatile uint_16 system_tick_ms    = 0;
volatile uint_16 led_last_blink_ms = 0;
volatile Byte uart1_buff           = 0;

void UART1_SendData(Byte data);
void UART1_SendString(const Byte *data);
void UART1_Recieve_Task(void);
void LED_Blink_Task(void);

void main(void)
{
    // CLOCK = 16 MHz
    CLK->CKDIVR &= ~(CPUDIV_MASK | HSIDIV_MASK);
    CLK->CKDIVR |= DIV_1;

    // TIM4 config
    TIM4->CR1 &= ~TIM4_CR1_CEN;
    TIM4->PSCR = Prescaler_128;
    TIM4->ARR  = 124;
    TIM4->CNTR = 0;
    TIM4->SR1 &= ~TIM4_SR_UIF;
    TIM4->IER |= TIM4_IER_UIE; // enable interrupt
    TIM4->CR1 |= TIM4_CR1_CEN;
    __asm__("rim");

    // GPIO config

    // PD5 = TX
    GPIOD->ODR |= (1U << 5);
    GPIOD->DDR |= (1U << 5);
    GPIOD->CR1 |= (1U << 5);
    GPIOD->CR2 &= ~(1U << 5); // low speed

    // PD6 = RX
    GPIOD->DDR &= ~(1U << 6);
    GPIOD->CR1 &= ~(1U << 6);
    GPIOD->CR2 &= ~(1U << 6);

    // PB5 = LED
    GPIOB->ODR |= (1U << 5);
    GPIOB->CR1 |= (1U << 5);
    GPIOB->CR2 &= ~(1U << 5);
    GPIOB->DDR |= (1U << 5);

    // UART config
    UART1->BRR2 = 0x03;
    UART1->BRR1 = 0x68;

    UART1->CR1 &= ~UART1_CR1_M; // 8-bit
    UART1->CR3 = 0x00;          // 1 stop bit
    UART1->CR2 = UART1_CR2_TEN | UART1_CR2_REN;
    UART1->CR2 |= UART1_CR2_RIEN; // RXNE interrupt enable

    while (1) {
        UART1_Recieve_Task();
        LED_Blink_Task();
    }
}

void UART1_SendData(Byte data)
{
    while ((UART1->SR & UART1_SR_TXE) == 0);
    UART1->DR = data;
}

void UART1_SendString(const Byte *data)
{
    while (*data) {
        UART1_SendData(*data);
        data++;
    }
}

void UART1_Recieve_Task(void)
{
    if (uart_event == DATA_RECIEVED) {
        uart_event = DATA_NOT_RECEIVED;
        UART1_SendString("\r\ni got it ");
        UART1_SendData(uart1_buff);
        UART1_SendString("\r\n");
    }
}

void LED_Blink_Task(void)
{
    if ((system_tick_ms - led_last_blink_ms) >= LED_BLINK_PERIOD) {
        led_last_blink_ms = system_tick_ms;
        GPIOB->ODR ^= (1U << 5);
    }
}

void UART1_ISR_Handler(void) __interrupt(UART1_IRQ_RECIEVE)
{
    uart1_buff = UART1->DR;
    uart_event = DATA_RECIEVED;
}

void TIM4_ISR_Handler(void) __interrupt(TIM4_IRQ)
{
    TIM4->SR1 &= ~TIM4_SR_UIF;
    system_tick_ms++;
}
