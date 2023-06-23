#include "tools.h"
#include "stm32f1xx.h"
#include "stm32f1xx_hal_def.h"
#include <stdint.h>
#include <stdio.h>
#include "log.h"

// STM IRQHandler def

void HardFault_Handler()
{
    log_info(__func__);
    while (1)
    {
        ;
    }
}

void SVC_Handler_Fn(uint32_t *pwdSF)
{
    // pwdSF += 1; 
    uint32_t svc_number = ((char *)pwdSF[6])[-2];
    uint32_t svc_r0 = pwdSF[0];
    uint32_t svc_r1 = pwdSF[1];
    uint32_t svc_r2 = pwdSF[2];
    uint32_t svc_r3 = pwdSF[3];

    // __ASM __volatile("add	r7, #4");
}

void SVC_Handler()
{
    // GNU GCC 使用r7作为sp的temp使用，并push了r7导致栈帧下移了一帧
    // 之后的栈帧计算都会受到影响导致错误
    // 所以这里使用sp增加4还原栈顶位置
    __ASM __volatile("pop     {r7}");

    __ASM __volatile("TST     LR,#4           \n\
                      ITE     EQ              \n\
                      MRSEQ   R0, MSP         \n\
                      MRSNE   R0, PSP         \n\
                      B       SVC_Handler_Fn");
    // 直接使用B跳转，不被担心返回，因为返回在SVC_Handler_Fn中处理
    // 因为不在此函数返回,所以不必担心这里的还原r7指令pop r7,代码不会执行到这里
}
