#ifndef STM8SC_UART1_H
#define STM8SC_UART1_H

#include "stm8sc_gpio.h"


#define UART1_Address 0x5230U

typedef struct
{
    __IOU8 SR;
    __IOU8 DR;
    __IOU8 BRR1;
    __IOU8 BRR2;
    __IOU8 CR1;
    __IOU8 CR2;
    __IOU8 CR3;
    __IOU8 CR4;
    __IOU8 CR5;
    __IOU8 GTR;
    __IOU8 PSCR;
} UART1_T;

#define TXE_MASK      (1U << 7) // transmit register status
#define RXNE_MASK     (1U << 5) // receive register status
#define UART1_CR2_TEN (1U << 3) // enable transmitter
#define UART1_CR2_REN (1U << 2) // enable receiver

#define UART1 ((UART1_T *) UART1_Address)

// API
void UART1_Init(void);
void UART1_SendData(Byte data);
void UART1_SendString(const Byte *data);
void UART1_Prompt(void);
Byte UART1_ReceiveData(void);

#endif // !STM8SC_UART_H