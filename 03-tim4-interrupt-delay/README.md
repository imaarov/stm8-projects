# 3. TIM4 Hardware Timer Delay Driver (Interrupt-Driven)
Toggles an LED on PB5 every 500ms using TIM4 configured to tick every 1ms, with the toggle handled entirely inside a `TIM4_UPD_OVF` interrupt handler (SDCC `__interrupt(23)`). The main loop is non-blocking.

**Registers used:** `GPIOB`, `TIM4` (CR1, IER, SR1, PSCR, ARR, CNTR)