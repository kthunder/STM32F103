#ifndef __STM32F10x_H
#define __STM32F10x_H

#define __IO volatile

typedef unsigned int u32;
typedef unsigned short u16;

/*片上外设基地址  */
#define PERIPH_BASE (0x40000000U)

/*APB2总线基地址 */
#define APB2PERIPH_BASE (PERIPH_BASE + 0x10000U)

/*AHB总线基地址 */
#define AHBPERIPH_BASE (PERIPH_BASE + 0x20000U)

/*RCC外设基地址*/
#define RCC_BASE (AHBPERIPH_BASE + 0x1000U)

/*RCC的 AHB1时钟使能寄存器地址,强制转换成指针*/
#define RCC_APB2ENR *(unsigned int*)(RCC_BASE + 0x18)

#endif