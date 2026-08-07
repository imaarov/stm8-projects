# 4. GPIO Button Polling + TIM4 Interrupt

Controls two LEDs using two different event handling approaches:

- An external LED connected to PA3 is toggled every 500ms inside a TIM4 update/overflow interrupt.
- The onboard LED connected to PB5 is controlled by a push button connected to PD3 using GPIO polling.
- PD3 is configured as an input with internal pull-up, so the button press is detected as an active-low signal (`0`).

The main loop remains non-blocking for the timer operation, while the button state is continuously checked through polling.

**Features:**
- TIM4 hardware timer interrupt (`TIM4_ISR_Handler`)
- SDCC interrupt handler (`__interrupt(23)`)
- GPIO input polling
- Internal pull-up configuration
- Active-low push button
- Bare-metal register-level STM8 programming

**Registers used:**
- `GPIOA` (`ODR`, `DDR`, `CR1`, `CR2`)
- `GPIOB` (`ODR`, `DDR`, `CR1`, `CR2`)
- `GPIOD` (`IDR`, `DDR`, `CR1`, `CR2`)
- `TIM4` (`CR1`, `IER`, `SR1`, `PSCR`, `ARR`, `CNTR`)