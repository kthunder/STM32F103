#include "tools.h"
#include "stm32f1xx.h"
#include <stdint.h>
#include <stdio.h>
#include "log.h"

// STM IRQHandler def

void HardFault_Handler()
{
    printf("%s\n", __func__);
    while (1)
    {
        ;
    }
}

uint32_t SVC_Handler_Fn(uint32_t * pwdSF)
{
    uint32_t SVC_number;
    uint32_t SVC_r0;
    uint32_t SVC_r1;
    uint32_t SVC_r2;
    uint32_t SVC_r3;
    uint32_t nRet;

    SVC_number = ((char *) pwdSF[6])[-2];
}


void SVC_Handler()
{
    __ASM volatile(         \
    "                       \
    IMPORT SVC_Handler_Fn   \
    TST     LR,#4           \
    ITE     EQ              \
    MRSEQ   R0, MSP         \
    MRSEQ   R0, MSP         \
    B       svc_handler     \
    ");
}

