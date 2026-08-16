# 9. UART1 Echo (Interrupt)

A project extending UART communication on STM8S by replacing polling-based reception with interrupts.

UART1 is configured for 9600 baud. When a byte is received, the UART ISR reads it from the data register and signals the main loop using an event flag.

## Features

* UART1 initialization using direct register access
* 9600 baud asynchronous serial communication
* UART reception using interrupts
* Event-based communication between ISR and main loop
* UART transmission using TXE polling
* TIM4 interrupt for a millisecond system tick
* Bare-metal register-level STM8 programming

## Registers used

* CLK (CKDIVR)
* TIM4 (CR1, PSCR, ARR, CNTR, SR1, IER)
* GPIOD (ODR, DDR, CR1, CR2)
* GPIOB (ODR, DDR, CR1, CR2)
* UART1 (SR, DR, BRR1, BRR2, CR1, CR2, CR3)

## Hardware Connections

```text
STM8 PD5 (TX) ----> USB-UART RX
STM8 PD6 (RX) <---- USB-UART TX
STM8 GND ---------- USB-UART GND
```

## How it works

1. UART generates an interrupt when a byte is received.
2. The ISR reads the byte and sets `uart_event`.
3. The main loop detects the event and echoes the byte.
4. TIM4 maintains the system tick and periodically blinks the LED.

## Known limitation

This implementation has a **race condition / data-loss problem**.

The ISR and main loop share a single `uart1_buff`. If another byte arrives before the main loop finishes processing the previous one, the ISR can overwrite the buffer. There is no mechanism to queue multiple received bytes.

Project **10** addresses this by introducing a ring buffer.
