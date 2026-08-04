# STM8S Projects

A collection of STM8S bare-metal projects developed using the SDCC compiler and programmed with an ST-Link debugger/programmer.

## Hardware & Toolchain

- MCU Family: STM8S
- Programmer: ST-Link
- Compiler: SDCC
- Development Style: Bare Metal (No RTOS, No HAL)

## Projects

### 1. Bare Metal LED Blink
A simple LED blinking project written in C to verify toolchain setup, flashing, GPIO configuration, and basic STM8S development workflow.

**Features**
- Direct register manipulation
- GPIO output configuration
- Software delay loop
- Minimal STM8S bare-metal example

## Supported MCU

Current development target:

- STM8S103F3

Future projects may support additional STM8S devices.

## Build & Flash

Compile the project using SDCC and flash the generated binary to the target MCU using an ST-Link programmer.

## License

This repository is provided for learning, experimentation, and embedded systems development.