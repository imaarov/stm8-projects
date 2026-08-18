#include "stm8sc_gpio.h"
#include "stm8sc_clk.h"
#include "stm8sc_uart1.h"
#include "stm8sc_tim4.h"

#define LED_BLINK_PERIOD       300U
#define UART1_BUFF_SIZE        8U
#define COMMAND_PROMPT_LED_ON  "LEDON"
#define COMMAND_PROMPT_LED_OFF "LEDOFF"

#define true                   1
#define false                  0

#define DEBUG                  1

typedef enum
{
    TURN_LED_ON,
    TURN_LED_OFF,
    DEFAULT,
} LED_EVENT;

LED_EVENT led_event = DEFAULT;

unsigned char led_on_prompt[]  = "ledon";
unsigned char led_off_prompt[] = "ledoff";

volatile uint_16 system_tick_ms              = 0;
volatile uint_16 led_last_blink_ms           = 0;
volatile Byte buff_ring[UART1_BUFF_SIZE + 1] = {0};
volatile uint_8 head                         = 0;
volatile uint_8 tail                         = 0;
volatile uint_16 uart_overrun_count          = 0;

void UART1_SendData(Byte data);
void UART1_SendString(const Byte *data);
void LED_Blink_Task(void);
void Command_Task(void);
void External_LED_Task(void);
void Advance_Tail(uint_8 n);
bool Ring_Find(uint_8 start, const char *prompt, uint_8 len);
static inline uint_8 Get_Unread_Buff_Size(void);

void main(void)
{
    // CLOCK = 16 MHz
    CLK->CKDIVR &= ~(CPUDIV_MASK | HSIDIV_MASK);
    CLK->CKDIVR |= DIV_1;

    // TIM4 config
    TIM4->CR1 &= ~TIM4_CR1_CEN;
    TIM4->PSCR = Prescaler_128;
    TIM4->ARR  = 124;
    TIM4->CNTR = 0;
    TIM4->SR1 &= ~TIM4_SR_UIF;
    TIM4->IER |= TIM4_IER_UIE; // enable interrupt
    TIM4->CR1 |= TIM4_CR1_CEN;

    // GPIO config

    // PD5 = TX
    GPIOD->ODR |= (1U << 5);
    GPIOD->DDR |= (1U << 5);
    GPIOD->CR1 |= (1U << 5);
    GPIOD->CR2 &= ~(1U << 5); // low speed

    // PD6 = RX
    GPIOD->DDR &= ~(1U << 6);
    GPIOD->CR1 &= ~(1U << 6);
    GPIOD->CR2 &= ~(1U << 6);

    // PB5 = Internal LED
    GPIOB->ODR |= (1U << 5);
    GPIOB->CR1 |= (1U << 5);
    GPIOB->CR2 &= ~(1U << 5);
    GPIOB->DDR |= (1U << 5);

    // PA3 = External LED
    GPIOA->ODR &= P3_CLEAR_MASK; // preload the Port B, Pin 5 ODR = 1 (OUTPUT LOW)
    GPIOA->CR1 |= P3_MASK;       // configure PB5 as PUSH PULL
    GPIOA->CR2 &= P3_CLEAR_MASK; // configure PB5 as Slow Ouput
    GPIOA->DDR |= P3_MASK;       // ... DDR = 1 (mode OUTPUT)

    // UART config
    UART1->BRR2 = 0x03;
    UART1->BRR1 = 0x68;

    UART1->CR1 &= ~UART1_CR1_M; // 8-bit
    UART1->CR3 = 0x00;          // 1 stop bit
    UART1->CR2 = UART1_CR2_TEN | UART1_CR2_REN;
    UART1->CR2 |= UART1_CR2_RIEN; // RXNE interrupt enable

    __asm__("rim");

    while (1)
    {
        LED_Blink_Task();
        Command_Task();
        External_LED_Task();
    }
}

void UART1_SendData(Byte data)
{
    while ((UART1->SR & UART1_SR_TXE) == 0);
    UART1->DR = data;
}

void UART1_SendString(const Byte *data)
{
    while (*data)
    {
        UART1_SendData(*data);
        data++;
    }
}

void LED_Blink_Task(void)
{
    if ((system_tick_ms - led_last_blink_ms) >= LED_BLINK_PERIOD)
    {
        led_last_blink_ms = system_tick_ms;
        GPIOB->ODR ^= (1U << 5);
    }
}

void UART1_ISR_Handler(void) __interrupt(UART1_IRQ_RECIEVE)
{
    uint_8 sr = UART1->SR;
    Byte data = UART1->DR;

    if (sr & UART1_SR_OR)
    {
        uart_overrun_count++;
        return;
    }

    uint_8 next = head;
    if (next == UART1_BUFF_SIZE - 1)
    {
        next = 0;
    }
    else
    {
        next++;
    }

    if (next != tail)
    {
        buff_ring[head] = data;
        head            = next;
    }
}

void TIM4_ISR_Handler(void) __interrupt(TIM4_IRQ)
{
    TIM4->SR1 &= ~TIM4_SR_UIF;
    system_tick_ms++;
}

void Command_Task(void)
{
    if (head == tail)
    {
        return;
    }
    
    uint_8 buff_size = Get_Unread_Buff_Size();

    if (buff_ring[tail] != led_on_prompt[0] &&
        buff_ring[tail] != led_off_prompt[0])
    {
        Advance_Tail(1);
        return;
    }

    uint_8 on_len = sizeof(led_on_prompt) - 1;
    uint_8 off_len = sizeof(led_off_prompt) - 1;

    if (buff_size >= on_len && Ring_Find(tail, led_on_prompt, on_len))
    {
        UART1_SendString("LED ON!\r\n");
        led_event = TURN_LED_ON;
        Advance_Tail(on_len);
    }
    else if (buff_size >= off_len && Ring_Find(tail, led_off_prompt, off_len))
    {
        UART1_SendString("LED OFF!\r\n");
        led_event = TURN_LED_OFF;
        Advance_Tail(off_len);
    }
    else if (buff_size >= off_len) 
    {
        UART1_SendString("Command not found\r\n");
        Advance_Tail(1);
    }else
    {
        return;
    }
}

bool Ring_Find(uint_8 start, const char *prompt, uint_8 len)
{
    for (uint_8 i = 0; i < len; i++)
    {
        if (buff_ring[start] != prompt[i])
        {
            return false;
        }
        
        if (start == UART1_BUFF_SIZE - 1)
        {
            start = 0;
        }else
        {
            start++;
        }
    }
    
    return true;
}

void Advance_Tail(uint_8 n)
{
    while (n--)
    {
        if (tail == UART1_BUFF_SIZE - 1)
        {
            tail = 0;
        }else
        {
            tail++;
        }
    }
}

void External_LED_Task(void)
{
    if (led_event != DEFAULT)
    {
        switch (led_event)
        {
            case TURN_LED_ON:
                GPIOA->ODR |= (1U << 3);
                break;
            case TURN_LED_OFF:
                GPIOA->ODR &= ~(1U << 3);
                break;

            default:
                break;
        }
        led_event = DEFAULT;
    }
}

static inline uint_8 Get_Unread_Buff_Size(void)
{
    return tail < head ? head - tail : UART1_BUFF_SIZE - tail + head;
}