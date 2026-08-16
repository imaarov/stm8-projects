# STM8S Projects
A collection of STM8S bare-metal projects developed using the SDCC compiler and programmed with an ST-Link debugger/programmer.
## Table of Contents
- [Hardware & Toolchain](#hardware--toolchain)
- [Projects](#projects)
  - [1. Bare Metal LED Blink - Software Delay](./01-led-blink-software-delay)
  - [2. TIM4 Hardware Timer Delay Driver (Polling, Specifically Busy Wait)](./02-tim4-polling-delay)
  - [3. TIM4 Hardware Timer Delay Driver (Interrupt-Driven)](./03-tim4-interrupt-delay)
  - [4. TIM4 Interrupt + GPIO Button Polling](./04-button-polling-with-tim4-interrupt)
  - [5. Button Debounce + Event Detection](./05-button-debounce-event)
  - [6. Button EXTI Debounce + Event Detection](./06-button-exti-debounce-event)
  - [7. UART1 Send Data Polling](./07-uart-send-data-polling)
  - [8. UART1 Echo (Polling)](./08-uart-echo-polling)
  - [9. UART1 Echo (Interrupt)](./09-uart-echo-interrupt)
  - [10. UART1 Echo with Ring Buffer](./10-uart-echo-ring-buffer)

- [Supported MCU](#supported-mcu)
- [Build & Flash](#build--flash)
- [UART Commands on GNU/Linux](#uart-gnulinux-commands)
- [License](#license)

## Hardware & Toolchain

- MCU Family: STM8S
- Programmer: ST-Link
- Compiler: SDCC
- Development Style: Bare Metal (No SPL, No HAL)
- IDE: Visual Studio Code with EIDE extension
- Environment: GNU/Linux

## Projects

### [1. Bare Metal LED Blink - Software Delay](./01-led-blink-software-delay)

A simple LED blinking project written in C to verify toolchain setup, flashing, GPIO configuration, and basic STM8S development workflow.

**Features**

- Direct register manipulation
- GPIO output configuration
- Software-based delay loop
- Minimal STM8S bare-metal example

---

### [2. TIM4 Hardware Timer Delay Driver](./02-tim4-polling-delay)

A bare-metal TIM4 driver implementing millisecond delays using the STM8S hardware timer peripheral.

The project demonstrates direct interaction with STM8S timer registers without relying on SPL or HAL libraries.

**Features**

- Custom TIM4 register mapping using C structures
- Direct peripheral register access
- Hardware timer-based millisecond delay
- Timer prescaler and auto-reload configuration
- Manual flag handling and overflow detection
- Resource management (timer start/stop control)

---

### [3. TIM4 Hardware Timer Delay Driver (Interrupt-Driven)](./03-tim4-interrupt-delay)

A bare-metal TIM4 driver reworked to use hardware interrupts instead of busy-wait polling, freeing up the main loop while keeping precise millisecond timing.

The project demonstrates SDCC's `__interrupt(N)` mechanism and STM8's auto-generated interrupt vector table, without relying on SPL or HAL libraries.

**Features**

- SDCC `__interrupt(N)` ISR registration (no manual vector table required)
- TIM4 configured to tick every 1ms via prescaler/auto-reload
- Software millisecond counter maintained inside the ISR
- Non-blocking main loop
- Global interrupt enable/disable via `rim`/`sim`

---

### [4. TIM4 Interrupt + GPIO Button Polling](./04-button-polling-with-tim4-interrupt)

A project combining TIM4 interrupt handling with GPIO polling.

An external LED connected to PA3 is toggled every 500ms inside the TIM4 interrupt handler. A push button connected to PD3 is read using GPIO polling and controls the onboard LED connected to PB5.

**Features**

- TIM4 interrupt handling
- GPIO input polling
- Internal pull-up configuration
- Active-low push button input
- Multiple GPIO configurations in one project

---

### [5. Button Debounce + Event Detection](./05-button-debounce-event)

A project implementing software debouncing and event-based button handling on top of GPIO polling and the TIM4 millisecond system tick.

The push button connected to PD3 is continuously sampled and debounced before generating a button press event. The onboard LED connected to PB5 responds to the generated event, while the external LED connected to PA3 continues to toggle every 500ms using the TIM4 interrupt.

**Features**

- GPIO button polling
- Software button debouncing
- Button press event detection
- TIM4 millisecond system tick
- Active-low push button with internal pull-up
- Separation of button state and button events

---


### [6. Button EXTI Debounce + Event Detection](./06-button-exti-debounce-event)

A project combining STM8 external interrupts (EXTI), software debouncing, and event-driven button handling.

The push button connected to PD3 generates an external interrupt whenever its state changes. The interrupt notifies the application that a potential button event has occurred, while a TIM4-based millisecond system tick is used to debounce the input before generating button press events.

The onboard LED connected to PB5 responds to button press events, while the external LED connected to PA3 continues to toggle every 500ms using the TIM4 interrupt.

**Features**

- STM8 EXTI (external interrupt) button detection
- Interrupt-driven button state notification
- Software button debouncing
- Button press event detection
- TIM4 millisecond system tick
- Active-low push button with internal pull-up
- Separation of interrupt handling, button processing, and event generation
- Bare-metal register-level STM8 programming

---


### [7. UART1 Send Data Polling](./07-uart-send-data-polling)

A project introducing UART communication on STM8S using direct register-level programming.

UART1 is configured for asynchronous serial communication at 9600 baud. A TIM4-based millisecond system tick is used to periodically transmit messages through UART1 while keeping the main loop responsive.

The project demonstrates UART peripheral initialization, GPIO configuration for TX/RX operation, transmit polling using the TXE flag, and string transmission without relying on SPL or HAL libraries.

**Features**

* UART1 initialization using direct register access
* 9600 baud asynchronous communication
* UART transmit polling (TXE flag)
* String transmission support
* TIM4 interrupt-driven millisecond system tick
* Periodic UART message transmission
* UART monitor banner output
* Bare-metal STM8 programming

---


### [8. UART1 Echo (Polling)](./08-uart-echo-polling)

A project extending UART communication to support bidirectional data transfer using polling.

UART1 is configured for asynchronous communication at 9600 baud. The application waits for incoming data, echoes the received byte back to the sender, and transmits a short message.

This project demonstrates UART reception using the RXNE flag and introduces interactive serial communication on STM8.

**Features**

* UART receive polling (RXNE flag)
* UART transmit polling (TXE flag)
* Full duplex UART communication
* Echo functionality (receive → send back)
* Simple interactive serial interface
* Bare-metal STM8 programming

---

### [9. UART1 Echo (Interrupt)](./09-uart-echo-interrupt)

A project extending UART communication to use interrupt-driven reception instead of polling.

UART1 is configured for asynchronous communication at 9600 baud. Received bytes are handled by the UART interrupt and passed to the main loop using a simple event flag.

The project also demonstrates a race condition caused by sharing a single receive buffer between the ISR and main loop, which motivates the ring buffer implementation in project 10.

**Features**

* UART receive interrupt (RXNE)
* Event-based communication between ISR and main loop
* UART transmit polling (TXE flag)
* TIM4 interrupt-driven millisecond system tick
* Demonstration of shared-data race condition
* Bare-metal STM8 programming

---

### [10. UART1 Echo with Ring Buffer](./10-uart-echo-ring-buffer)

A continuation of the UART interrupt project that introduces a fixed-size ring buffer for handling multiple received bytes asynchronously.

The UART interrupt stores received data in the buffer while the main loop processes it independently, avoiding the single-byte buffer limitation of project 9.

**Features**

* UART receive interrupt (RXNE)
* Fixed-size ring buffer
* Head/tail buffer management
* UART overrun detection
* UART transmit polling (TXE flag)
* TIM4 interrupt-driven millisecond system tick
* Bare-metal STM8 programming



## Supported MCU

Current development target:

- STM8S103F3

Future projects may support additional STM8S devices.

## Build & Flash

Compile the project using SDCC and flash the generated binary to the target MCU using an ST-Link programmer.

The project is developed using the EIDE extension in Visual Studio Code on a GNU/Linux environment.

You can use the `build.sh` bash script as well. It automates building and flashing.

Build:

```bash
./build.sh
```

Flash:

```bash
./build.sh --flash
```

## UART GNU/Linux Commands

- install picocom

```bash
sudo apt update && sudo apt install picocom
```

- find the USB UART Bridge

```bash
ls -l /dev/serial/by-id/
```

- listen to the USB UART bridge

```bash
picocom -b 9600 /dev/ttyUSB0
```