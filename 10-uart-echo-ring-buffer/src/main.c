#include "stm8sc_gpio.h"
#include "stm8sc_clk.h"
#include "stm8sc_uart1.h"
#include "stm8sc_tim4.h"

#define LED_BLINK_PERIOD 300U
#define UART1_BUFF_SIZE  8U

volatile uint_16 system_tick_ms              = 0;
volatile uint_16 led_last_blink_ms           = 0;
volatile Byte buff_ring[UART1_BUFF_SIZE + 1] = {0};
volatile uint_8 head                         = 0;
volatile uint_8 tail                         = 0;
volatile uint_16 uart_overrun_count          = 0;

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

    __asm__("rim");

    while (1)
    {
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
    while (*data)
    {
        UART1_SendData(*data);
        data++;
    }
}

void LED_Blink_Task(void)
{
    if ((system_tick_ms - led_last_blink_ms) >= LED_BLINK_PERIOD)
    {
        led_last_blink_ms = system_tick_ms;
        GPIOB->ODR ^= (1U << 5);
    }
}

void UART1_Recieve_Task(void)
{
    if (head != tail)
    {
        UART1_SendData(buff_ring[tail]);
        if (tail == UART1_BUFF_SIZE - 1)
        {
            tail = 0;
        }
        else
        {
            tail++;
        }
    }
}

void UART1_ISR_Handler(void) __interrupt(UART1_IRQ_RECIEVE)
{
    uint_8 sr = UART1->SR;
    Byte data = UART1->DR;

    if (sr & UART1_SR_OR)
    {
        uart_overrun_count++;
        return;
    }

    uint_8 next = head;
    if (next == UART1_BUFF_SIZE - 1)
    {
        next = 0;
    }
    else
    {
        next++;
    }

    if (next != tail)
    {
        buff_ring[head] = data;
        head            = next;
    }
}

void TIM4_ISR_Handler(void) __interrupt(TIM4_IRQ)
{
    TIM4->SR1 &= ~TIM4_SR_UIF;
    system_tick_ms++;
}
