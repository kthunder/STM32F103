#include "stm32f103x6.h"
#include "stm32f1xx_hal_usart.h"


void USART_Init(USART_TypeDef* USARTx)
{
    USARTx->BRR = 0x271; // 设置波特率

    USARTx->CR1 |= 1<<13; // 使能USART
    USARTx->CR1 |= 1<<12; // 一个起始位，8个数据位，n个停止位
    USARTx->CR1 |= 1<<3; // TX使能
    USARTx->CR1 |= 1<<2; // RX使能
}