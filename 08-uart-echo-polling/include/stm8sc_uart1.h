#ifndef STM8SC_UART1_H
#define STM8SC_UART1_H

#include "stm8sc_gpio.h"


#define UART1_Address 0x5230U

typedef struct
{
    __IOU8 SR;
    __IOU8 DR;    /* use for both transmittion and receition*/
    __IOU8 BRR1;  /* 
                    ** should write the BRR2 before BRR1**
                    Tx\Rx baud rate = fMaster / UART_DIV (BRR)
                    UART_DIV[11:4] 
                    writing BRR1 will make the baud update
                    */
    __IOU8 BRR2; /* Tx\Rx baud rate, UART_DIV*/
    __IOU8 CR1;
    __IOU8 CR2;
    __IOU8 CR3;
    __IOU8 CR4;
    __IOU8 CR5;
    __IOU8 GTR;
    __IOU8 PSCR;
} UART1_T;

/*
    UART1 SR 
    7   6   5    4    3    2   1   0
    TXE TC RXNE IDLE OR   NF   FE  PE
*/
#define UART1_SR_PE   (1U << 0) // Parity error
#define UART1_SR_FE   (1U << 1) // Framing error
#define UART1_SR_NF   (1U << 2) // Noise
#define UART1_SR_OR   (1U << 3) // Overrun: new data arived, but the old data was never read
#define UART1_SR_IDLE (1U << 4) // RX line is in IDLE mode
#define UART1_SR_RXNE (1U << 5) // Receive Data Register Not Empty, when its 1 thats mean UART fetch a byte and data is in DR ready to read **Read DR clear this FLAG**
#define UART1_SR_TC   (1U << 6) // Transmittion completed
#define UART1_SR_TXE  (1U << 7) // Transmit Data Register Empty, if its 1 thats mean register is empty and you can put the next data in the DR register

/*
    UART1 CR1
    7    6    5    4    3     2      1    0
    R8   T8   -    M    WAKE  PCEN   PS   PIEN
*/
#define UART1_CR1_PIEN (1U << 0) // parity interrupt enable (0 = no parity, 1 = parity enable)
#define UART1_CR1_PS   (1U << 1) // parity selection        (0 = even parity, 1 = odd parity)
#define UART1_CR1_PCEN (1U << 2) // parity control enable
#define UART1_CR1_WAKE (1U << 3) // wake up method
#define UART1_CR1_M    (1u << 4) // word length             (0 = 8bit, 1 = 9bit)

/*
    UART1 CR2
    7     6     5      4      3    2    1    0
    TIEN  TCIEN RIEN   ILIEN  TEN  REN  RWU  SBK
*/
#define UART1_CR2_SBK   (1U << 0) // send break
#define UART1_CR2_RWU   (1U << 1) // receiver wake up
#define UART1_CR2_REN   (1U << 2) // receiver enable
#define UART1_CR2_TEN   (1U << 3) // transmitter enable
#define UART1_CR2_ILIEN (1U << 4) // idle line interrupt
#define UART1_CR2_RIEN  (1U << 5) // RXNE interrupt enable
#define UART1_CR2_TCIEN (1U << 6) // Transmittion complete interrupt
#define UART1_CR2_TIEN  (1U << 7) // TXE interrupt enable

/*
    UART1 CR3
    7       6    5     4     3     2      1    0
    LINEN STOP1 STOP0 CKEN  CPOL  CPHA   LBCL  -
*/
#define UART1_CR3_LINEN (1U << 7) // LIN mode enable

#define UART1_CR3_STOP1 (1U << 6) // STOP bit 1
#define UART1_CR3_STOP0 (1U << 5) // STOP bit 0
/*
    STOP1 STOP0
    0     0     -> 1 stop bit
    0     1     -> 0.5 stop bit
    1     0     -> 2 stop bits
    1     1     -> 1.5 stop bits
*/
#define UART1_CR3_CKEN  (1U << 4) // clock enable (synchronous mode)
#define UART1_CR3_CPOL  (1U << 3) // clock polarity
#define UART1_CR3_CPHA  (1U << 2) // clock phase
#define UART1_CR3_LBCL  (1U << 1) // last bit clock pulse
#define UART1_CR3_NONE  (0U << 0) // reserved bit


#define UART1_CR2_TEN (1U << 3) // enable transmitter
#define UART1_CR2_REN (1U << 2) // enable receiver

#define UART1 ((UART1_T *) UART1_Address)

#endif // !STM8SC_UART_H