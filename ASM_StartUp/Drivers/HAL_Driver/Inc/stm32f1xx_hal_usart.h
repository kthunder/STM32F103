#ifndef __STM32F1xx_HAL_USART_H
#define __STM32F1xx_HAL_USART_H

#include "stm32f1xx.h"

void USART_Init(USART_TypeDef* USARTx);

uint32_t USART_Transmit(USART_TypeDef* USARTx, uint8_t *pData, uint16_t nSize);

#endif