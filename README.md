# STM8S Projects
A collection of STM8S bare-metal projects developed using the SDCC compiler and programmed with an ST-Link debugger/programmer.
## Table of Contents
- [Hardware & Toolchain](#hardware--toolchain)
- [Projects](#projects)
  - [1. Bare Metal LED Blink - Software Delay](./01-led-blink-software-delay)
  - [2. TIM4 Hardware Timer Delay Driver (Polling, Specifically Busy Wait)](./02-tim4-polling-delay)
  - [3. TIM4 Hardware Timer Delay Driver (Interrupt-Driven)](./03-tim4-interrupt-delay)
  - [4. TIM4 Interrupt + GPIO Button Polling](./04-tim4-interrupt-button-polling)
- [Supported MCU](#supported-mcu)
- [Build & Flash](#build--flash)
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

### [4. TIM4 Interrupt + GPIO Button Polling](./04-tim4-interrupt-button-polling)

A project combining TIM4 interrupt handling with GPIO polling.

An external LED connected to PA3 is toggled every 500ms inside the TIM4 interrupt handler. A push button connected to PD3 is read using GPIO polling and controls the onboard LED connected to PB5.

**Features**

- TIM4 interrupt handling
- GPIO input polling
- Internal pull-up configuration
- Active-low push button input
- Multiple GPIO configurations in one project

---

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