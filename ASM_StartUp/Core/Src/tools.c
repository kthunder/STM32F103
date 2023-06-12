#include <stdint.h>
#include <stdio.h>
#include "stm32f1xx.h"
#include "stm32f1xx_hal_usart.h"
#include "tools.h"

static uint32_t systicks = 0;

__attribute__((weak)) int __io_getchar()
{
    // return USART_Receive(USART1, (uint8_t *)&ch, 1);
    return 0;
}

__attribute__((weak)) int __io_putchar(int ch)
{
    return USART_Transmit(USART1, (uint8_t *)&ch, 1);
}

__attribute__((weak)) int _read(int file, char *ptr, int len)
{
    (void)file;
    int DataIdx;

    for (DataIdx = 0; DataIdx < len; DataIdx++)
    {
        *ptr++ = __io_getchar();
    }

    return len;
}

__attribute__((weak)) int _write(int file, char *ptr, int len)
{
    (void)file;
    int DataIdx;

    for (DataIdx = 0; DataIdx < len; DataIdx++)
    {
        __io_putchar(*ptr++);
    }
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

void HardFault_Handler()
{
    printf("%s\n",__func__);
}