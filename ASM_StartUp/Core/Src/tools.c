#include <stdint.h>
#include "stm32f1xx.h"
#include "stm32f1xx_hal_usart.h"
#include "tools.h"

static uint32_t systicks = 0;

// int __io_putchar(int ch)
// {
//     return USART_Transmit(USART1, (uint8_t *)&ch, 1);
// }

int _write(int file, char *ptr, int len)
{
    USART_Transmit(USART1, (uint8_t *)ptr, len);
    return len;
}

void delay_ms(uint32_t ms)
{
    uint32_t current = systicks;
    while (systicks - current < ms)
        ;
}

void SysTick_Handler()
{
    systicks++;
}