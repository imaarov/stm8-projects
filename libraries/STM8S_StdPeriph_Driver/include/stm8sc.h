#ifndef STM8SC_H
#define STM8SC_H

#define uint_8  unsigned char
#define uint_16 unsigned short
#define uint_32 unsigned long

// define bit masks
#define PB5_MASK       (1U << 5)
#define PB5_CLEAR_MASK (~PB5_MASK)

// Port/Pin Base Address Definition
#define GPIOB_Address 0x5005U

// Struct Based on GPIO Adress
typedef struct {
    volatile uint_8 ODR; // Output Data      Register
    volatile uint_8 IDR; // Input  Data      Register
    volatile uint_8 DDR; // Data   Direction Register
    volatile uint_8 CR1; // Control Register 1
    volatile uint_8 CR2; // Control Register 2
} GPIO_T;

// Cast the GPIO B to GPIO_T struct
#define GPIOB_T ((GPIO_T *)GPIOB_Address)

#endif // !STM8SC_H