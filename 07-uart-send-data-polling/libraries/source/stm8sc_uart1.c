#include "stm8sc_uart1.h"

void UART1_Init(void)
{
    /*
     * fMASTER = 16 MHz
     * baud    = 9600
     *
     * UARTDIV = 16000000 / 9600
     *         = 1666.666...
     *
     * STM8 UART:
     *
     * BRR1 = 0x68
     * BRR2 = 0x03
     */

    UART1->BRR1 = 0x68;
    UART1->BRR2 = 0x03;

    // 8 data bits, no parity
    UART1->CR1 = 0x00;

    // TX + RX enabled
    UART1->CR2 = UART1_CR2_TEN | UART1_CR2_REN;

    // 1 stop bit
    UART1->CR3 = 0x00;
}


void UART1_SendData(Byte data)
{
    while ((UART1->SR & TXE_MASK) == 0)
    {
    }

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


Byte UART1_ReceiveData(void)
{
    while ((UART1->SR & RXNE_MASK) == 0)
    {
    }

    return UART1->DR;
}


void UART1_Prompt(void)
{
    UART1_SendString("\r\n");
    UART1_SendString("=====================\r\n");
    UART1_SendString(" STM8 UART1 MONITOR PROMPT\r\n");
    UART1_SendString("Clock : 16 MHz\r\n");
    UART1_SendString("UART  : 9600 8N1\r\n");
    UART1_SendString("=====================\r\n");
}