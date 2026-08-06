# 1. Bare Metal LED Blink - Software Delay
Toggles an LED on PB5 using a busy-wait software delay loop.
Purpose: verify toolchain, flashing, and GPIO register configuration on the STM8S103F3.

**Registers used:** `GPIOB` (ODR, DDR, CR1, CR2)