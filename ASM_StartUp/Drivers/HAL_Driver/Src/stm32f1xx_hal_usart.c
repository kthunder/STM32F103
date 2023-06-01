#include "stm32f1xx.h"
#include "stm32f1xx_hal_usart.h"

void USART_Init(USART_TypeDef* USARTx)
{
	USARTx->BRR = 0x271;	// 设置波特率

	USARTx->CR1 |= 1 << 13; // 使能USART
	USARTx->CR1 |= 1 << 12; // 一个起始位，8个数据位，n个停止位
	USARTx->CR1 |= 1 << 3;	// TX使能
	USARTx->CR1 |= 1 << 2;	// RX使能
}

uint32_t USART_Transmit(USART_TypeDef* USARTx, uint8_t* pData, uint16_t nSize)
{
	if ((USART1->SR) & (1 << 7))
	{
		// USART1->DR = RCC->CFGR;
		// USART1->DR = RCC->CFGR >> 8;
		USART1->DR = 0x11;
		// USART1->DR = RCC->CFGR >> 24;
	}
	return 0;
}