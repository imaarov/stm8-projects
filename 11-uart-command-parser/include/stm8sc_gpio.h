#ifndef STM8SC_GPIO_H
#define STM8SC_GPIO_H

#define uint_8  unsigned char
#define bool    uint_8
#define uint_16 unsigned short
#define uint_32 unsigned long

#define __IOU8  volatile uint_8

#define Byte    uint_8

// define bit masks
#define PB5_MASK       (1U << 5)
#define P3_MASK        (1U << 3)
#define P3_CLEAR_MASK  (~P3_MASK)
#define PB5_CLEAR_MASK (~PB5_MASK)

// Port/Pin Base Address Definition
#define GPIOB_Address 0x5005U
#define GPIOA_Address 0x5000U
#define GPIOD_Address 0x500FU

// Struct Based on GPIO Adress
typedef struct {
    volatile uint_8 ODR; // Output Data      Register
    volatile uint_8 IDR; // Input  Data      Register
    volatile uint_8 DDR; // Data   Direction Register
    volatile uint_8 CR1; // Control Register 1
    volatile uint_8 CR2; // Control Register 2
} GPIO_T;

// Cast the GPIO B to GPIO_T struct
#define GPIOB ((GPIO_T *)GPIOB_Address)
#define GPIOA ((GPIO_T *)GPIOA_Address)
#define GPIOD ((GPIO_T *)GPIOD_Address)

#endif // !STM8SC_GPIO_H