#ifndef __STM32F1xx_HAL_FLASH_H
#define __STM32F1xx_HAL_FLASH_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f1xx.h"

    uint32_t FLASH_Write(uint32_t addr, void *ptr, uint32_t len);
    uint32_t FLASH_Read(uint32_t addr, void *ptr, uint32_t len);
    uint32_t FLASH_Blank_Check(uint32_t addr, uint32_t len);
    uint32_t FLASH_Erase(uint32_t addr);

#ifdef __cplusplus
}
#endif

#endif