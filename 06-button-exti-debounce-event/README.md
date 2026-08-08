# 6. Button EXTI Debounce Event

A button handling project that combines STM8 external interrupts (EXTI) with software debouncing and event generation.

A push button connected to PD3 triggers an external interrupt on state changes. The interrupt notifies the application that the button state may have changed, while a TIM4-based system tick is used to debounce the input before generating button events.

The design separates interrupt detection from button processing, providing a simple event-driven approach to button handling.

**Features:**

* External interrupt (EXTI) button detection
* Interrupt-driven button state notification
* Software debouncing using TIM4 system tick
* Button press event generation
* Active-low push button input
* Event-driven application design
* Bare-metal register-level STM8 programming

**Registers used:**

* `GPIOA` (`ODR`, `DDR`, `CR1`, `CR2`)
* `GPIOB` (`ODR`, `DDR`, `CR1`, `CR2`)
* `GPIOD` (`IDR`, `DDR`, `CR1`, `CR2`)
* `EXTI` (`CR1`)
* `TIM4` (`CR1`, `IER`, `SR1`, `PSCR`, `ARR`, `CNTR`)
