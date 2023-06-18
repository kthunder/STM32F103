#include "tools.h"
#include "stm32f103x6.h"
#include "stm32f1xx.h"
#include "stm32f1xx_hal_usart.h"
#include <stdint.h>
#include <stdio.h>

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

uint32_t HAL_GetTick() { return systicks; }

void Active_Soft_EXIT(IRQn_Type nIRQ)
{
    // __ASM volatile("SVC 0x01");
    NVIC_EnableIRQ(nIRQ);
    SET_BIT(SCB->CCR, SCB_CCR_USERSETMPEND_Msk);
    WRITE_REG(NVIC->STIR, nIRQ);
}

// STM IRQHandler def

void SysTick_Handler() { systicks++; }

void HardFault_Handler()
{
    printf("%s\n", __func__);
    while (1)
    {
        ;
    }
}