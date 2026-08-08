# 5. Button Debounce + Event Detection

Implements a debounced push-button input with event-based handling.

* The push button connected to PD3 is continuously sampled using GPIO polling.
* Button state changes are debounced using the TIM4 millisecond system tick.
* A `BUTTON_PRESSED_EVENT` is generated only when a valid press is detected.
* The onboard LED connected to PB5 responds to the button press event.
* The external LED connected to PA3 continues to toggle every 500ms using the TIM4 interrupt.

The button logic separates the **raw GPIO state**, **debounced state**, and **button event**, preventing a single physical press from being interpreted multiple times due to switch bouncing.

**Features:**

* GPIO button polling
* Software button debouncing
* Event-based button handling
* TIM4 millisecond system tick
* Active-low push button with internal pull-up
* Separation of button state and button events
* Bare-metal register-level STM8 programming

**Registers used:**

* `GPIOA` (`ODR`, `DDR`, `CR1`, `CR2`)
* `GPIOB` (`ODR`, `DDR`, `CR1`, `CR2`)
* `GPIOD` (`IDR`, `DDR`, `CR1`, `CR2`)
* `TIM4` (`CR1`, `IER`, `SR1`, `PSCR`, `ARR`, `CNTR`)
