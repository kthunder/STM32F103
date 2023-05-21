#ifndef __STM32F10x_H
#define __STM32F10x_H

#define __IO volatile

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

typedef struct
{
  __IO u32 SR;
  __IO u32 CR1;
  __IO u32 CR2;
  __IO u32 SMPR1;
  __IO u32 SMPR2;
  __IO u32 JOFR1;
  __IO u32 JOFR2;
  __IO u32 JOFR3;
  __IO u32 JOFR4;
  __IO u32 HTR;
  __IO u32 LTR;
  __IO u32 SQR1;
  __IO u32 SQR2;
  __IO u32 SQR3;
  __IO u32 JSQR;
  __IO u32 JDR1;
  __IO u32 JDR2;
  __IO u32 JDR3;
  __IO u32 JDR4;
  __IO u32 DR;
} ADC_TypeDef;

typedef struct
{
  __IO u32 SR;               /*!< ADC status register,    used for ADC multimode (bits common to several ADC instances). Address offset: ADC1 base address         */
  __IO u32 CR1;              /*!< ADC control register 1, used for ADC multimode (bits common to several ADC instances). Address offset: ADC1 base address + 0x04  */
  __IO u32 CR2;              /*!< ADC control register 2, used for ADC multimode (bits common to several ADC instances). Address offset: ADC1 base address + 0x08  */
  u32  RESERVED[16];
  __IO u32 DR;               /*!< ADC data register,      used for ADC multimode (bits common to several ADC instances). Address offset: ADC1 base address + 0x4C  */
} ADC_Common_TypeDef;

/** 
  * @brief Backup Registers  
  */

typedef struct
{
  u32  RESERVED0;
  __IO u32 DR1;
  __IO u32 DR2;
  __IO u32 DR3;
  __IO u32 DR4;
  __IO u32 DR5;
  __IO u32 DR6;
  __IO u32 DR7;
  __IO u32 DR8;
  __IO u32 DR9;
  __IO u32 DR10;
  __IO u32 RTCCR;
  __IO u32 CR;
  __IO u32 CSR;
} BKP_TypeDef;
  
/** 
  * @brief Controller Area Network TxMailBox 
  */

typedef struct
{
  __IO u32 TIR;
  __IO u32 TDTR;
  __IO u32 TDLR;
  __IO u32 TDHR;
} CAN_TxMailBox_TypeDef;

/** 
  * @brief Controller Area Network FIFOMailBox 
  */
  
typedef struct
{
  __IO u32 RIR;
  __IO u32 RDTR;
  __IO u32 RDLR;
  __IO u32 RDHR;
} CAN_FIFOMailBox_TypeDef;

/** 
  * @brief Controller Area Network FilterRegister 
  */
  
typedef struct
{
  __IO u32 FR1;
  __IO u32 FR2;
} CAN_FilterRegister_TypeDef;

/** 
  * @brief Controller Area Network 
  */
  
typedef struct
{
  __IO u32 MCR;
  __IO u32 MSR;
  __IO u32 TSR;
  __IO u32 RF0R;
  __IO u32 RF1R;
  __IO u32 IER;
  __IO u32 ESR;
  __IO u32 BTR;
  u32  RESERVED0[88];
  CAN_TxMailBox_TypeDef sTxMailBox[3];
  CAN_FIFOMailBox_TypeDef sFIFOMailBox[2];
  u32  RESERVED1[12];
  __IO u32 FMR;
  __IO u32 FM1R;
  u32  RESERVED2;
  __IO u32 FS1R;
  u32  RESERVED3;
  __IO u32 FFA1R;
  u32  RESERVED4;
  __IO u32 FA1R;
  u32  RESERVED5[8];
  CAN_FilterRegister_TypeDef sFilterRegister[14];
} CAN_TypeDef;

/** 
  * @brief CRC calculation unit 
  */

typedef struct
{
  __IO u32 DR;           /*!< CRC Data register,                           Address offset: 0x00 */
  __IO u8  IDR;          /*!< CRC Independent data register,               Address offset: 0x04 */
  u8       RESERVED0;    /*!< Reserved,                                    Address offset: 0x05 */
  u16      RESERVED1;    /*!< Reserved,                                    Address offset: 0x06 */  
  __IO u32 CR;           /*!< CRC Control register,                        Address offset: 0x08 */ 
} CRC_TypeDef;


/** 
  * @brief Debug MCU
  */

typedef struct
{
  __IO u32 IDCODE;
  __IO u32 CR;
}DBGMCU_TypeDef;

/** 
  * @brief DMA Controller
  */

typedef struct
{
  __IO u32 CCR;
  __IO u32 CNDTR;
  __IO u32 CPAR;
  __IO u32 CMAR;
} DMA_Channel_TypeDef;

typedef struct
{
  __IO u32 ISR;
  __IO u32 IFCR;
} DMA_TypeDef;



/** 
  * @brief External Interrupt/Event Controller
  */

typedef struct
{
  __IO u32 IMR;
  __IO u32 EMR;
  __IO u32 RTSR;
  __IO u32 FTSR;
  __IO u32 SWIER;
  __IO u32 PR;
} EXTI_TypeDef;

/** 
  * @brief FLASH Registers
  */

typedef struct
{
  __IO u32 ACR;
  __IO u32 KEYR;
  __IO u32 OPTKEYR;
  __IO u32 SR;
  __IO u32 CR;
  __IO u32 AR;
  __IO u32 RESERVED;
  __IO u32 OBR;
  __IO u32 WRPR;
} FLASH_TypeDef;

/** 
  * @brief Option Bytes Registers
  */
  
typedef struct
{
  __IO u16 RDP;
  __IO u16 USER;
  __IO u16 Data0;
  __IO u16 Data1;
  __IO u16 WRP0;
  __IO u16 WRP1;
  __IO u16 WRP2;
  __IO u16 WRP3;
} OB_TypeDef;

/** 
  * @brief General Purpose I/O
  */

typedef struct
{
  __IO u32 CRL;
  __IO u32 CRH;
  __IO u32 IDR;
  __IO u32 ODR;
  __IO u32 BSRR;
  __IO u32 BRR;
  __IO u32 LCKR;
} GPIO_TypeDef;

/** 
  * @brief Alternate Function I/O
  */

typedef struct
{
  __IO u32 EVCR;
  __IO u32 MAPR;
  __IO u32 EXTICR[4];
  u32 RESERVED0;
  __IO u32 MAPR2;  
} AFIO_TypeDef;
/** 
  * @brief Inter Integrated Circuit Interface
  */

typedef struct
{
  __IO u32 CR1;
  __IO u32 CR2;
  __IO u32 OAR1;
  __IO u32 OAR2;
  __IO u32 DR;
  __IO u32 SR1;
  __IO u32 SR2;
  __IO u32 CCR;
  __IO u32 TRISE;
} I2C_TypeDef;

/** 
  * @brief Independent WATCHDOG
  */

typedef struct
{
  __IO u32 KR;           /*!< Key register,                                Address offset: 0x00 */
  __IO u32 PR;           /*!< Prescaler register,                          Address offset: 0x04 */
  __IO u32 RLR;          /*!< Reload register,                             Address offset: 0x08 */
  __IO u32 SR;           /*!< Status register,                             Address offset: 0x0C */
} IWDG_TypeDef;

/** 
  * @brief Power Control
  */

typedef struct
{
  __IO u32 CR;
  __IO u32 CSR;
} PWR_TypeDef;

/** 
  * @brief Reset and Clock Control
  */

typedef struct
{
  __IO u32 CR;
  __IO u32 CFGR;
  __IO u32 CIR;
  __IO u32 APB2RSTR;
  __IO u32 APB1RSTR;
  __IO u32 AHBENR;
  __IO u32 APB2ENR;
  __IO u32 APB1ENR;
  __IO u32 BDCR;
  __IO u32 CSR;


} RCC_TypeDef;

/** 
  * @brief Real-Time Clock
  */

typedef struct
{
  __IO u32 CRH;
  __IO u32 CRL;
  __IO u32 PRLH;
  __IO u32 PRLL;
  __IO u32 DIVH;
  __IO u32 DIVL;
  __IO u32 CNTH;
  __IO u32 CNTL;
  __IO u32 ALRH;
  __IO u32 ALRL;
} RTC_TypeDef;

/** 
  * @brief Serial Peripheral Interface
  */

typedef struct
{
  __IO u32 CR1;
  __IO u32 CR2;
  __IO u32 SR;
  __IO u32 DR;
  __IO u32 CRCPR;
  __IO u32 RXCRCR;
  __IO u32 TXCRCR;
  __IO u32 I2SCFGR;
} SPI_TypeDef;

/**
  * @brief TIM Timers
  */
typedef struct
{
  __IO u32 CR1;             /*!< TIM control register 1,                      Address offset: 0x00 */
  __IO u32 CR2;             /*!< TIM control register 2,                      Address offset: 0x04 */
  __IO u32 SMCR;            /*!< TIM slave Mode Control register,             Address offset: 0x08 */
  __IO u32 DIER;            /*!< TIM DMA/interrupt enable register,           Address offset: 0x0C */
  __IO u32 SR;              /*!< TIM status register,                         Address offset: 0x10 */
  __IO u32 EGR;             /*!< TIM event generation register,               Address offset: 0x14 */
  __IO u32 CCMR1;           /*!< TIM  capture/compare mode register 1,        Address offset: 0x18 */
  __IO u32 CCMR2;           /*!< TIM  capture/compare mode register 2,        Address offset: 0x1C */
  __IO u32 CCER;            /*!< TIM capture/compare enable register,         Address offset: 0x20 */
  __IO u32 CNT;             /*!< TIM counter register,                        Address offset: 0x24 */
  __IO u32 PSC;             /*!< TIM prescaler register,                      Address offset: 0x28 */
  __IO u32 ARR;             /*!< TIM auto-reload register,                    Address offset: 0x2C */
  __IO u32 RCR;             /*!< TIM  repetition counter register,            Address offset: 0x30 */
  __IO u32 CCR1;            /*!< TIM capture/compare register 1,              Address offset: 0x34 */
  __IO u32 CCR2;            /*!< TIM capture/compare register 2,              Address offset: 0x38 */
  __IO u32 CCR3;            /*!< TIM capture/compare register 3,              Address offset: 0x3C */
  __IO u32 CCR4;            /*!< TIM capture/compare register 4,              Address offset: 0x40 */
  __IO u32 BDTR;            /*!< TIM break and dead-time register,            Address offset: 0x44 */
  __IO u32 DCR;             /*!< TIM DMA control register,                    Address offset: 0x48 */
  __IO u32 DMAR;            /*!< TIM DMA address for full transfer register,  Address offset: 0x4C */
  __IO u32 OR;              /*!< TIM option register,                         Address offset: 0x50 */
}TIM_TypeDef;


/** 
  * @brief Universal Synchronous Asynchronous Receiver Transmitter
  */
 
typedef struct
{
  __IO u32 SR;         /*!< USART Status register,                   Address offset: 0x00 */
  __IO u32 DR;         /*!< USART Data register,                     Address offset: 0x04 */
  __IO u32 BRR;        /*!< USART Baud rate register,                Address offset: 0x08 */
  __IO u32 CR1;        /*!< USART Control register 1,                Address offset: 0x0C */
  __IO u32 CR2;        /*!< USART Control register 2,                Address offset: 0x10 */
  __IO u32 CR3;        /*!< USART Control register 3,                Address offset: 0x14 */
  __IO u32 GTPR;       /*!< USART Guard time and prescaler register, Address offset: 0x18 */
} USART_TypeDef;

/** 
  * @brief Universal Serial Bus Full Speed Device
  */
  
typedef struct
{
  __IO u16 EP0R;                 /*!< USB Endpoint 0 register,                   Address offset: 0x00 */ 
  __IO u16 RESERVED0;            /*!< Reserved */     
  __IO u16 EP1R;                 /*!< USB Endpoint 1 register,                   Address offset: 0x04 */
  __IO u16 RESERVED1;            /*!< Reserved */       
  __IO u16 EP2R;                 /*!< USB Endpoint 2 register,                   Address offset: 0x08 */
  __IO u16 RESERVED2;            /*!< Reserved */       
  __IO u16 EP3R;                 /*!< USB Endpoint 3 register,                   Address offset: 0x0C */ 
  __IO u16 RESERVED3;            /*!< Reserved */       
  __IO u16 EP4R;                 /*!< USB Endpoint 4 register,                   Address offset: 0x10 */
  __IO u16 RESERVED4;            /*!< Reserved */       
  __IO u16 EP5R;                 /*!< USB Endpoint 5 register,                   Address offset: 0x14 */
  __IO u16 RESERVED5;            /*!< Reserved */       
  __IO u16 EP6R;                 /*!< USB Endpoint 6 register,                   Address offset: 0x18 */
  __IO u16 RESERVED6;            /*!< Reserved */       
  __IO u16 EP7R;                 /*!< USB Endpoint 7 register,                   Address offset: 0x1C */
  __IO u16 RESERVED7[17];        /*!< Reserved */     
  __IO u16 CNTR;                 /*!< Control register,                          Address offset: 0x40 */
  __IO u16 RESERVED8;            /*!< Reserved */       
  __IO u16 ISTR;                 /*!< Interrupt status register,                 Address offset: 0x44 */
  __IO u16 RESERVED9;            /*!< Reserved */       
  __IO u16 FNR;                  /*!< Frame number register,                     Address offset: 0x48 */
  __IO u16 RESERVEDA;            /*!< Reserved */       
  __IO u16 DADDR;                /*!< Device address register,                   Address offset: 0x4C */
  __IO u16 RESERVEDB;            /*!< Reserved */       
  __IO u16 BTABLE;               /*!< Buffer Table address register,             Address offset: 0x50 */
  __IO u16 RESERVEDC;            /*!< Reserved */       
} USB_TypeDef;


/** 
  * @brief Window WATCHDOG
  */

typedef struct
{
  __IO u32 CR;   /*!< WWDG Control register,       Address offset: 0x00 */
  __IO u32 CFR;  /*!< WWDG Configuration register, Address offset: 0x04 */
  __IO u32 SR;   /*!< WWDG Status register,        Address offset: 0x08 */
} WWDG_TypeDef;

/**
  * @}
  */
  
/** @addtogroup Peripheral_memory_map
  * @{
  */


#define FLASH_BASE            0x08000000UL /*!< FLASH base address in the alias region */
#define FLASH_BANK1_END       0x08007FFFUL /*!< FLASH END address of bank1 */
#define SRAM_BASE             0x20000000UL /*!< SRAM base address in the alias region */
#define PERIPH_BASE           0x40000000UL /*!< Peripheral base address in the alias region */

#define SRAM_BB_BASE          0x22000000UL /*!< SRAM base address in the bit-band region */
#define PERIPH_BB_BASE        0x42000000UL /*!< Peripheral base address in the bit-band region */


/*!< Peripheral memory map */
#define APB1PERIPH_BASE       PERIPH_BASE
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x00010000UL)
#define AHBPERIPH_BASE        (PERIPH_BASE + 0x00020000UL)

#define TIM2_BASE             (APB1PERIPH_BASE + 0x00000000UL)
#define TIM3_BASE             (APB1PERIPH_BASE + 0x00000400UL)
#define RTC_BASE              (APB1PERIPH_BASE + 0x00002800UL)
#define WWDG_BASE             (APB1PERIPH_BASE + 0x00002C00UL)
#define IWDG_BASE             (APB1PERIPH_BASE + 0x00003000UL)
#define USART2_BASE           (APB1PERIPH_BASE + 0x00004400UL)
#define I2C1_BASE             (APB1PERIPH_BASE + 0x00005400UL)
#define CAN1_BASE             (APB1PERIPH_BASE + 0x00006400UL)
#define BKP_BASE              (APB1PERIPH_BASE + 0x00006C00UL)
#define PWR_BASE              (APB1PERIPH_BASE + 0x00007000UL)
#define AFIO_BASE             (APB2PERIPH_BASE + 0x00000000UL)
#define EXTI_BASE             (APB2PERIPH_BASE + 0x00000400UL)
#define GPIOA_BASE            (APB2PERIPH_BASE + 0x00000800UL)
#define GPIOB_BASE            (APB2PERIPH_BASE + 0x00000C00UL)
#define GPIOC_BASE            (APB2PERIPH_BASE + 0x00001000UL)
#define GPIOD_BASE            (APB2PERIPH_BASE + 0x00001400UL)
#define ADC1_BASE             (APB2PERIPH_BASE + 0x00002400UL)
#define ADC2_BASE             (APB2PERIPH_BASE + 0x00002800UL)
#define TIM1_BASE             (APB2PERIPH_BASE + 0x00002C00UL)
#define SPI1_BASE             (APB2PERIPH_BASE + 0x00003000UL)
#define USART1_BASE           (APB2PERIPH_BASE + 0x00003800UL)


#define DMA1_BASE             (AHBPERIPH_BASE + 0x00000000UL)
#define DMA1_Channel1_BASE    (AHBPERIPH_BASE + 0x00000008UL)
#define DMA1_Channel2_BASE    (AHBPERIPH_BASE + 0x0000001CUL)
#define DMA1_Channel3_BASE    (AHBPERIPH_BASE + 0x00000030UL)
#define DMA1_Channel4_BASE    (AHBPERIPH_BASE + 0x00000044UL)
#define DMA1_Channel5_BASE    (AHBPERIPH_BASE + 0x00000058UL)
#define DMA1_Channel6_BASE    (AHBPERIPH_BASE + 0x0000006CUL)
#define DMA1_Channel7_BASE    (AHBPERIPH_BASE + 0x00000080UL)
#define RCC_BASE              (AHBPERIPH_BASE + 0x00001000UL)
#define CRC_BASE              (AHBPERIPH_BASE + 0x00003000UL)

#define FLASH_R_BASE          (AHBPERIPH_BASE + 0x00002000UL) /*!< Flash registers base address */
#define FLASHSIZE_BASE        0x1FFFF7E0UL    /*!< FLASH Size register base address */
#define UID_BASE              0x1FFFF7E8UL    /*!< Unique device ID register base address */
#define OB_BASE               0x1FFFF800UL    /*!< Flash Option Bytes base address */



#define DBGMCU_BASE          0xE0042000UL /*!< Debug MCU registers base address */

/* USB device FS */
#define USB_BASE              (APB1PERIPH_BASE + 0x00005C00UL) /*!< USB_IP Peripheral Registers base address */
#define USB_PMAADDR           (APB1PERIPH_BASE + 0x00006000UL) /*!< USB_IP Packet Memory Area base address */


/**
  * @}
  */
  
/** @addtogroup Peripheral_declaration
  * @{
  */  

#define TIM2                ((TIM_TypeDef *)TIM2_BASE)
#define TIM3                ((TIM_TypeDef *)TIM3_BASE)
#define RTC                 ((RTC_TypeDef *)RTC_BASE)
#define WWDG                ((WWDG_TypeDef *)WWDG_BASE)
#define IWDG                ((IWDG_TypeDef *)IWDG_BASE)
#define USART2              ((USART_TypeDef *)USART2_BASE)
#define I2C1                ((I2C_TypeDef *)I2C1_BASE)
#define USB                 ((USB_TypeDef *)USB_BASE)
#define CAN1                ((CAN_TypeDef *)CAN1_BASE)
#define BKP                 ((BKP_TypeDef *)BKP_BASE)
#define PWR                 ((PWR_TypeDef *)PWR_BASE)
#define AFIO                ((AFIO_TypeDef *)AFIO_BASE)
#define EXTI                ((EXTI_TypeDef *)EXTI_BASE)
#define GPIOA               ((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB               ((GPIO_TypeDef *)GPIOB_BASE)
#define GPIOC               ((GPIO_TypeDef *)GPIOC_BASE)
#define GPIOD               ((GPIO_TypeDef *)GPIOD_BASE)
#define ADC1                ((ADC_TypeDef *)ADC1_BASE)
#define ADC2                ((ADC_TypeDef *)ADC2_BASE)
#define ADC12_COMMON        ((ADC_Common_TypeDef *)ADC1_BASE)
#define TIM1                ((TIM_TypeDef *)TIM1_BASE)
#define SPI1                ((SPI_TypeDef *)SPI1_BASE)
#define USART1              ((USART_TypeDef *)USART1_BASE)
#define DMA1                ((DMA_TypeDef *)DMA1_BASE)
#define DMA1_Channel1       ((DMA_Channel_TypeDef *)DMA1_Channel1_BASE)
#define DMA1_Channel2       ((DMA_Channel_TypeDef *)DMA1_Channel2_BASE)
#define DMA1_Channel3       ((DMA_Channel_TypeDef *)DMA1_Channel3_BASE)
#define DMA1_Channel4       ((DMA_Channel_TypeDef *)DMA1_Channel4_BASE)
#define DMA1_Channel5       ((DMA_Channel_TypeDef *)DMA1_Channel5_BASE)
#define DMA1_Channel6       ((DMA_Channel_TypeDef *)DMA1_Channel6_BASE)
#define DMA1_Channel7       ((DMA_Channel_TypeDef *)DMA1_Channel7_BASE)
#define RCC                 ((RCC_TypeDef *)RCC_BASE)
#define CRC                 ((CRC_TypeDef *)CRC_BASE)
#define FLASH               ((FLASH_TypeDef *)FLASH_R_BASE)
#define OB                  ((OB_TypeDef *)OB_BASE)
#define DBGMCU              ((DBGMCU_TypeDef *)DBGMCU_BASE)

#endif