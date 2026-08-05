# STM8S Projects

A collection of STM8S bare-metal projects developed using the SDCC compiler and programmed with an ST-Link debugger/programmer.

## Hardware & Toolchain

- MCU Family: STM8S
- Programmer: ST-Link
- Compiler: SDCC
- Development Style: Bare Metal (No SPL, No HAL)
- IDE: Visual Studio Code with EIDE extension
- Environment: GNU/Linux

## Projects

### 1. Bare Metal LED Blink - Software Delay

A simple LED blinking project written in C to verify toolchain setup, flashing, GPIO configuration, and basic STM8S development workflow.

**Features**
- Direct register manipulation
- GPIO output configuration
- Software-based delay loop
- Minimal STM8S bare-metal example

---

### 2. TIM4 Hardware Timer Delay Driver

A bare-metal TIM4 driver implementing millisecond delays using the STM8S hardware timer peripheral.

The project demonstrates direct interaction with STM8S timer registers without relying on SPL or HAL libraries.

**Features**
- Custom TIM4 register mapping using C structures
- Direct peripheral register access
- Hardware timer-based millisecond delay
- Timer prescaler and auto-reload configuration
- Manual flag handling and overflow detection
- Resource management (timer start/stop control)

## Supported MCU

Current development target:

- STM8S103F3

Future projects may support additional STM8S devices.

## Build & Flash

Compile the project using SDCC and flash the generated binary to the target MCU using an ST-Link programmer.

The project is developed using the EIDE extension in Visual Studio Code on a GNU/Linux environment.

## License

This repository is provided for learning, experimentation, and embedded systems development.
