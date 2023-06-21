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

uint32_t SVC_Handler_Fn(uint32_t *pwdSF)
{
    uint32_t svc_number;
    uint32_t svc_r0;
    uint32_t svc_r1;
    uint32_t svc_r2;
    uint32_t svc_r3;
    uint32_t nRet;

    svc_number = ((char *)pwdSF[6])[-2];
    svc_r0 = ((unsigned long)pwdSF[0]);
    svc_r1 = ((unsigned long)pwdSF[1]);
    svc_r2 = ((unsigned long)pwdSF[2]);
    svc_r3 = ((unsigned long)pwdSF[3]);

    log_info("SVC number : %d\n", svc_number);
    log_info("SVC parameter 0 : %d\n", svc_r0);
    log_info("SVC parameter 1 : %d\n", svc_r1);
    log_info("SVC parameter 2 : %d\n", svc_r2);
    log_info("SVC parameter 3 : %d\n", svc_r3);

    pwdSF[0] = nRet;
    return 0;
}

void SVC_Handler()
{
    __ASM volatile(
        "\n\t\
    TST     LR,#4           \n\t\
    ITE     EQ              \n\t\
    MRSEQ   R0, MSP         \n\t\
    MRSNE   R0, PSP         \n\t\
    B       SVC_Handler_Fn");
}
