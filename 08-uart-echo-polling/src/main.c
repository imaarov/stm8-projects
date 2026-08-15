#include "stm8sc_gpio.h"
#include "stm8sc_clk.h"
#include "stm8sc_uart1.h"

void UART1_SendData(Byte data);
void UART1_SendString(const Byte *data);
Byte UART1_ReceiveData(void);

void main(void)
{
    // CLOCK = 16 MHz
    CLK->CKDIVR &= ~(CPUDIV_MASK | HSIDIV_MASK);
    CLK->CKDIVR |= DIV_1;

    // GPIO config

    // PD5 = TX
    GPIOD->ODR |= (1U << 5);
    GPIOD->DDR |= (1U << 5);
    GPIOD->CR1 |= (1U << 5);
    GPIOD->CR2 &= ~(1U << 5);   // low speed

    // PD6 = RX
    GPIOD->DDR &= ~(1U << 6);
    GPIOD->CR1 &= ~(1U << 6);
    GPIOD->CR2 &= ~(1U << 6);

    // UART config

    UART1->BRR2 = 0x03;
    UART1->BRR1 = 0x68;

    UART1->CR1 &= ~UART1_CR1_M;     // 8-bit
    UART1->CR3 = 0x00;             // 1 stop bit
    UART1->CR2 = UART1_CR2_TEN | UART1_CR2_REN;

    while (1)
    {
        Byte c = UART1_ReceiveData(); // wait for data

        UART1_SendData(c); // send the data (echo)

        UART1_SendString("\r\nfinally\r\n"); // send some message after it
    }
}

Byte UART1_ReceiveData(void)
{
    // wait until RXNE = 1 (data received)
    while ((UART1->SR & UART1_SR_RXNE) == 0);

    return UART1->DR;   // reading DR clears RXNE
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