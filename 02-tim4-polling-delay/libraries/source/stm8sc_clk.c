#include "stm8sc_clk.h"

void CLK_Init_16MHz(void)
{
    // initializing fMaster Clock for CPU to be the default 16MHz
    // its seems like after reset, clkdiv is set to 4 and the fMaster is 4MHz
    CLK->CKDIVR &= ~(CPUDIV_MASK | HSIDIV_MASK);
    CLK->CKDIVR |= DIV_1;
}