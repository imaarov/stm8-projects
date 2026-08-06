#ifndef STM8SC_CLK_H
#define STM8SC_CLK_H

#include "stm8sc_gpio.h"

#define CLK_Address 0x50C0U

#define CPUDIV_MASK 0x07U
#define HSIDIV_MASK 0x18U

typedef struct
{
    volatile uint_8 ICKR;
    volatile uint_8 ECKR;
    uint_8 reserved1;
    volatile uint_8 CMSR;
    volatile uint_8 SWR;
    volatile uint_8 SWCR;
    volatile uint_8 CKDIVR;
    volatile uint_8 PCKENR1;
    volatile uint_8 CSSR;
    volatile uint_8 CCOR;
    volatile uint_8 PCKENR2;
    uint_8 reserved2;
    volatile uint_8 HSITRIMR;
    volatile uint_8 SWIMCCR;
} CLK_T;

enum CPUDIV {
    DIV_1   = 0,
    DIV_2,
    DIV_4 ,
    DIV_8 ,
    DIV_16,
    DIV_32,
    DIV_64,
    DIV_128,
};

#define CLK ((CLK_T *)CLK_Address)

// CLK API
void CLK_Init_16MHz(void);

#endif // !STM8SC_CLK_H