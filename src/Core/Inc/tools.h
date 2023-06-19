#ifndef __TOOLS_H
#define __TOOLS_H

#include <stdint.h>
#include <stdio.h>

#define GET_BIT(value,bit) ((value)&(1<<(bit)))     //读取指定位
#define CPL_BIT(value,bit) ((value)^=(1<<(bit)))    //取反指定位

// #define SET_BIT(value,bit) ((value)|= (1<<(bit)))   //把某个位置1
// #define CLEAR_BIT(value,bit) ((value)&=~(1<<(bit))) //把某个位置0



void delay_ms(uint32_t ms);

uint32_t HAL_GetTick();

#define assert_param(expr) \
    ((expr) ? (void)0U : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
static inline void assert_failed(uint8_t *file, uint32_t line)
{
    printf("Wrong parameters value: file %s on line %lu\n", file, line);

    while (1)
    {
    }
}

#endif