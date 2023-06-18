#include <stdio.h>

// STM IRQHandler def

void HardFault_Handler()
{
    printf("%s\n", __func__);
    while (1)
    {
        ;
    }
}