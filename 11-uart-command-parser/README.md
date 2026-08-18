# 11 - UART Command Parser

This project builds on the UART interrupt and ring-buffer implementation from the previous project.

The STM8 receives ASCII commands asynchronously through UART1. Received bytes are stored in a ring buffer by the UART interrupt service routine, while the main loop processes the buffered data and detects valid commands.

## Supported Commands

```text
ledon
ledoff
```

When a valid command is received:

* `ledon` turns the external LED on.
* `ledoff` turns the external LED off.
* The internal LED continues blinking periodically.
* A response is sent back over UART.

Example:

```text
ledon
-> LED ON!

ledoff
-> LED OFF!
```

## Concepts

This project is intended as a learning exercise for:

* UART interrupt-driven reception
* Ring buffers
* Non-blocking command processing
* Parsing commands from a byte stream
* Handling commands that may wrap around the ring-buffer boundary
* Separating ISR responsibilities from application logic
* Event-based application handling
* Periodic tasks driven by a timer interrupt
* Detecting and counting UART overrun errors

## Architecture

The UART ISR is responsible only for receiving bytes and placing them into the ring buffer.

The main loop performs the higher-level processing:

```text
UART RX
   │
   ▼
UART Interrupt
   │
   ▼
Ring Buffer
   │
   ▼
Command_Task()
   │
   ├── "ledon"  ──► TURN_LED_ON
   │
   └── "ledoff" ─► TURN_LED_OFF
                         │
                         ▼
                  External_LED_Task()
```

TIM4 generates a periodic interrupt and maintains the system tick used by the LED blinking task.

## Important Design Idea

The interrupt handler does not attempt to parse commands.

It only moves incoming bytes into the ring buffer.

This keeps the ISR short and moves application-level processing into the normal execution context.

## Hardware

Target MCU:

```text
STM8
```

Used peripherals:

```text
UART1
TIM4
GPIO
```

LEDs:

```text
PB5 -> Internal LED
PA3 -> External LED
```

UART:

```text
PD5 -> TX
PD6 -> RX
```

## Notes

The ring buffer is intentionally small because this is a learning project. The implementation also keeps track of UART overrun errors:

```c
volatile uint_16 uart_overrun_count = 0;
```

The project is not intended to be a complete command-line interface. Its purpose is to understand how a small embedded system can process an asynchronous byte stream without parsing data inside an interrupt handler.
