# 8. UART1 Echo (Polling)

A project extending UART communication on STM8S to support bidirectional data transfer using polling.

UART1 is configured for asynchronous serial communication at 9600 baud. Unlike the previous project which only transmitted data, this project introduces UART reception and builds a simple interactive behavior.

The application waits for incoming data from a serial terminal. When a byte is received, it is immediately echoed back to the sender, followed by a short message. The system then returns to waiting for the next byte.

This demonstrates how to use the RXNE flag for receiving data and how to combine it with TXE-based transmission to create a basic request-response style interface.

Features:

- UART1 initialization using direct register access
- 9600 baud asynchronous serial communication
- UART receive polling using the RXNE flag
- UART transmit polling using the TXE flag
- Full duplex communication (RX + TX)
- Echo functionality (receive -> send back)
- Simple interactive serial behavior
- Bare-metal register-level STM8 programming

Registers used:

- CLK (CKDIVR)
- GPIOD (ODR, DDR, CR1, CR2)
- UART1 (SR, DR, BRR1, BRR2, CR1, CR2, CR3)

Hardware Connections:

STM8S103F3 UART1 default pins:

PD5 -> UART1_TX  
PD6 -> UART1_RX  

Example USB-to-UART connection:

STM8 PD5 (TX) ----> USB-UART RX  
STM8 PD6 (RX) <---- USB-UART TX  
STM8 GND ---------- USB-UART GND  

How it works:

1. The MCU waits for incoming UART data (blocking polling)
2. When a byte is received:
   - It is read from the UART data register
   - It is immediately sent back (echo)
   - A short message is transmitted
3. The system returns to waiting for the next byte

Example interaction:

PC sends: A  
MCU responds: A  
finally  

PC sends: B  
MCU responds: B  
finally  

GNU/Linux test:

picocom -b 9600 /dev/ttyUSB0