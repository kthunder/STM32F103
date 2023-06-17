#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx.h"

/**
 *函数功能：设置引脚为高电平
 *参数说明：GPIOx:该参数为 GPIO_TypeDef类型的指针，指向 GPIO端口的地址
 *        GPIO_Pin:选择要设置的 GPIO端口引脚，可输入宏 GPIO_Pin_0-15，
 *                 表示 GPIOx端口的 0-15号引脚。
 */
void GPIO_SetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    /*设置 GPIOx端口 BSRR寄存器的第 GPIO_Pin位，使其输出高电平*/
    /*因为 BSRR寄存器写 0不影响，
    宏 GPIO_Pin只是对应位为 1，其它位均为 0，所以可以直接赋值*/
    GPIOx->BSRR = GPIO_Pin;
}

/**
 *函数功能：设置引脚为低电平
 *参数说明：GPIOx:该参数为 GPIO_TypeDef类型的指针，指向 GPIO端口的地址
 *        GPIO_Pin:选择要设置的 GPIO端口引脚，可输入宏 GPIO_Pin_0-15，
 *                 表示 GPIOx端口的 0-15号引脚。
 */
void GPIO_ResetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    /*设置 GPIOx端口 BSRR寄存器的第 GPIO_Pin位，使其输出高电平*/
    /*因为 BRR寄存器写 0不影响，
    宏 GPIO_Pin只是对应位为 1，其它位均为 0，所以可以直接赋值*/
    GPIOx->BRR = GPIO_Pin;
}

void GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    GPIOx->ODR ^= GPIO_Pin;
}

/**
 *函数功能：初始化引脚模式
 *参数说明：GPIOx，该参数为 GPIO_TypeDef类型的指针，指向 GPIO端口的地址
 *         GPIO_InitTypeDef:GPIO_InitTypeDef结构体指针，指向初始化变量
 */
void GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_InitConfig)
{
    uint32_t currentmode = 0x00;
    uint32_t currentpin = 0x00;
    uint32_t pinpos = 0x00;
    uint32_t pos = 0x00;
    uint32_t tmpreg = 0x00;
    uint32_t pinmask = 0x00;

    /*---------------- GPIO 模式配置 -------------------*/
    // 把输入参数 GPIO_Mode的低四位暂存在 currentmode
    currentmode = ((uint32_t)GPIO_InitConfig->GPIO_Mode) & ((uint32_t)0x0F);

    // bit4是 1表示输出，bit4是 0则是输入
    // 判断 bit4是 1还是 0，即首选判断是输入还是输出模式
    if ((((uint32_t)GPIO_InitConfig->GPIO_Mode) & ((uint32_t)0x10)) != 0x00)
    {
        // 输出模式则要设置输出速度
        currentmode |= (uint32_t)GPIO_InitConfig->GPIO_Speed;
    }
    /*-----GPIO CRL 寄存器配置 CRL寄存器控制着低 8位 IO- ----*/
    // 配置端口低 8位，即 Pin0~Pin7
    if (((uint32_t)GPIO_InitConfig->GPIO_Pin & ((uint32_t)0x00FF)) != 0x00)
    {
        // 先备份 CRL寄存器的值
        tmpreg = GPIOx->CRL;

        // 循环，从 Pin0开始配对，找出具体的 Pin
        for (pinpos = 0x00; pinpos < 0x08; pinpos++)
        {
            // pos的值为 1左移 pinpos位
            pos = ((uint32_t)0x01) << pinpos;

            // 令 pos与输入参数 GPIO_PIN作位与运算
            currentpin = (GPIO_InitConfig->GPIO_Pin) & pos;

            // 若 currentpin=pos,则找到使用的引脚
            if (currentpin == pos)
            {
                // pinpos的值左移两位(乘以 4),因为寄存器中 4个位配置一个引脚
                pos = pinpos << 2;
                // 把控制这个引脚的 4个寄存器位清零，其它寄存器位不变
                pinmask = ((uint32_t)0x0F) << pos;
                tmpreg &= ~pinmask;

                // 向寄存器写入将要配置的引脚的模式
                tmpreg |= (currentmode << pos);

                // 判断是否为下拉输入模式
                if (GPIO_InitConfig->GPIO_Mode == GPIO_Mode_IPD)
                {
                    // 下拉输入模式,引脚默认置 0,对 BRR寄存器写 1对引脚置 0
                    GPIOx->BRR = (((uint32_t)0x01) << pinpos);
                }
                else
                {
                    // 判断是否为上拉输入模式
                    if (GPIO_InitConfig->GPIO_Mode == GPIO_Mode_IPU)
                    {
                        // 上拉输入模式,引脚默认值为 1,对 BSRR寄存器写 1对引脚置 1
                        GPIOx->BSRR = (((uint32_t)0x01) << pinpos);
                    }
                }
            }
        }
        // 把前面处理后的暂存值写入到 CRL寄存器之中
        GPIOx->CRL = tmpreg;
    }
    /*--------GPIO CRH 寄存器配置 CRH寄存器控制着高 8位 IO- -----*/
    // 配置端口高 8位，即 Pin8~Pin15
    if (GPIO_InitConfig->GPIO_Pin > 0x00FF)
    {
        // // 先备份 CRH寄存器的值
        tmpreg = GPIOx->CRH;

        // 循环，从 Pin8开始配对，找出具体的 Pin
        for (pinpos = 0x00; pinpos < 0x08; pinpos++)
        {
            pos = (((uint32_t)0x01) << (pinpos + 0x08));

            // pos与输入参数 GPIO_PIN作位与运算
            currentpin = ((GPIO_InitConfig->GPIO_Pin) & pos);

            // 若 currentpin=pos,则找到使用的引脚
            if (currentpin == pos)
            {
                // pinpos的值左移两位(乘以 4),因为寄存器中 4个位配置一个引脚
                pos = pinpos << 2;

                // 把控制这个引脚的 4个寄存器位清零，其它寄存器位不变
                pinmask = ((uint32_t)0x0F) << pos;
                tmpreg &= ~pinmask;

                // 向寄存器写入将要配置的引脚的模式
                tmpreg |= (currentmode << pos);

                // 判断是否为下拉输入模式
                if (GPIO_InitConfig->GPIO_Mode == GPIO_Mode_IPD)
                {
                    // 下拉输入模式,引脚默认置 0,对 BRR寄存器写 1可对引脚置 0
                    GPIOx->BRR = (((uint32_t)0x01) << (pinpos + 0x08));
                }
                // 判断是否为上拉输入模式
                if (GPIO_InitConfig->GPIO_Mode == GPIO_Mode_IPU)
                {
                    // 上拉输入模式,引脚默认值为 1,对 BSRR寄存器写 1可对引脚置 1
                    GPIOx->BSRR = (((uint32_t)0x01) << (pinpos + 0x08));
                }
            }
        }
        // 把前面处理后的暂存值写入到 CRH寄存器之中
        GPIOx->CRH = tmpreg;
    }
}