# 7. UART1 Send Data Polling

A project introducing STM8 UART communication using direct register-level programming.

UART1 is configured for asynchronous serial communication at 9600 baud using the STM8S103F3 built-in UART peripheral. A TIM4-based millisecond system tick is used to periodically transmit data through the UART interface without blocking the application.

The project demonstrates how to configure UART1, transmit bytes and strings using polling, and build a simple serial monitor output without relying on SPL or HAL libraries.

At startup, the application prints a UART monitor banner. After initialization, a message is transmitted every 300ms through UART1.

**Features:**

* UART1 initialization using direct register access
* 9600 baud asynchronous serial communication
* UART transmit polling using the TXE flag
* String transmission support
* TIM4 interrupt-driven millisecond system tick
* Periodic UART message transmission
* Simple UART monitor banner output
* Bare-metal register-level STM8 programming

**Registers used:**

* `CLK` (`CKDIVR`)
* `GPIOD` (`ODR`, `DDR`, `CR1`, `CR2`)
* `TIM4` (`CR1`, `IER`, `SR1`, `PSCR`, `ARR`, `CNTR`)
* `UART1` (`SR`, `DR`, `BRR1`, `BRR2`, `CR1`, `CR2`, `CR3`)

## Hardware Connections

STM8S103F3 UART1 default pins:

```text
PD5 -> UART1_TX
PD6 -> UART1_RX
```

Example USB-to-UART connection:

```text
STM8 PD5 (TX) ----> USB-UART RX
STM8 PD6 (RX) <---- USB-UART TX
STM8 GND ---------- USB-UART GND
```

## Example Output

```text
=====================
 STM8 UART1 MONITOR PROMPT
Clock : 16 MHz
UART  : 9600 8N1
=====================

UART1: TICK
UART1: TICK
UART1: TICK
...
```
