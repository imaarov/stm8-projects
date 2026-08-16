# 10. UART1 Echo with Ring Buffer

A continuation of project 09 that replaces the single-byte UART buffer with a fixed-size ring buffer.

Received bytes are stored by the UART interrupt and processed asynchronously by the main loop.

## Features

* UART1 initialization using direct register access
* 9600 baud asynchronous serial communication
* Interrupt-driven UART reception
* Fixed-size ring buffer
* UART overrun detection
* TXE polling for transmission
* TIM4 interrupt for system tick
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
2. The ISR reads the byte and writes it to the ring buffer.
3. `head` tracks the write position and `tail` tracks the read position.
4. The main loop processes buffered bytes independently of the ISR.
5. If the buffer is full, the incoming byte is discarded.
6. UART hardware overrun errors are counted in `uart_overrun_count`.

The ring buffer removes the single-byte shared-buffer limitation from project 09 and allows multiple received bytes to be queued.
