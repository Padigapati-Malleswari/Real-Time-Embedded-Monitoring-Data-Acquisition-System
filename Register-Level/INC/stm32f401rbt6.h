//#ifndef STM32F401RBT6_H
//#define STM32F401RBT6_H
//#pragma once

#include<stdint.h>
//GPIO
#define GPIOAADD  0x40020000
#define GPIOBADD  0x40020400 
#define GPIOCADD  0x40020800 
typedef struct
{
	volatile uint32_t  MODER;
	volatile uint32_t  OTYPER;
	volatile uint32_t  OSPEEDR;
	volatile uint32_t  PUPDR;
	volatile uint32_t  IDR; 
	volatile uint32_t  ODR ;
	volatile uint32_t  BSRR;
	volatile uint32_t  LCKR ;
	volatile uint32_t  AFRL;
	volatile uint32_t   AFRH;
}GPIO_RegDef_t;

#define GPIOA ((GPIO_RegDef_t *)GPIOAADD)
#define GPIOB  ((GPIO_RegDef_t *)GPIOBADD)
#define GPIOC ((GPIO_RegDef_t *)GPIOCADD)



//RCC
#define RCCADD 0x40023800 
#define RCC ((RCC_RegDef_t *)RCCADD)

typedef struct
{
	volatile uint32_t   CR;
	volatile uint32_t   PLLCFGR;
	volatile uint32_t   CFGR;
	volatile uint32_t   CIR;
	volatile uint32_t   AHB1RSTR;
	volatile uint32_t   AHB2RSTR;
	volatile uint32_t   Reserved1[2];
	volatile uint32_t   APB1RSTR;
	volatile uint32_t   APB2RSTR;
	volatile uint32_t   Reserved2[2];
	volatile uint32_t    AHB1ENR;
	volatile uint32_t    AHB2ENR;
	volatile uint32_t    Reserved3[2];  
	volatile uint32_t    APB1ENR;
	volatile uint32_t    APB2ENR;  
	volatile uint32_t   Reserved4[2];
	volatile uint32_t    AHB1LPENR;
	volatile uint32_t    AHB2LPENR;
	volatile uint32_t      Reserved5[2];
	volatile uint32_t    APB1LPENR;
	volatile uint32_t    APB2LPENR;
	volatile uint32_t    Reserved6[2];
	volatile uint32_t     BDCR;
	volatile uint32_t    CSR;
	volatile uint32_t    Reserved7[2];
	volatile uint32_t    SSCGR;
	volatile uint32_t    PLLI2SCFGR;
	volatile uint32_t     DCKCFG;

}RCC_RegDef_t;




//ADC
#define ADCADD 0x40012000
#define ADC ((ADC_RegDef_t *)ADCADD)

typedef struct
{
  volatile uint32_t      SR;
	volatile uint32_t     CR1;
	volatile uint32_t     CR2;
	volatile uint32_t     SMPR1;
		volatile uint32_t   SMPR2;
	volatile uint32_t     JOFR1;
	volatile uint32_t     JOFR2;
	volatile uint32_t     JOFR3;
		volatile uint32_t    JOFR4;
	volatile uint32_t      HTR;
	volatile uint32_t      LTR;
	volatile uint32_t      SQR1;
		volatile uint32_t    SQR2;
	volatile uint32_t     SQR3;
	volatile uint32_t     JSQR;
	volatile uint32_t     JDR1;
		volatile uint32_t   JDR2;
	volatile uint32_t    JDR3;
	volatile uint32_t    JDR4;
	volatile uint32_t    DR;
	volatile uint32_t    CCR;
	}ADC_RegDef_t;
   
	//......EXTI.....//
	#define EXTIADD  0x40013C00
#define EXTI    ((EXTI_RegDef_t *)EXTIADD)
	typedef struct
{
  volatile uint32_t      IMR;
	volatile uint32_t      EMR;
	volatile uint32_t      RTSR;
	volatile uint32_t     FTSR; 
	volatile uint32_t     SWIER;
  volatile uint32_t     PR;			
	
}EXTI_RegDef_t;	
	

//.... SYSCFG....//

	#define SYSCFGADD 0x40013800 
#define  SYSCFG ((SYSCFG_RegDef_t *)SYSCFGADD)
	typedef struct
{
  volatile uint32_t      MEMRMP;
	volatile uint32_t     PMC;
	volatile uint32_t     EXTICR1;
  volatile uint32_t       EXTICR2;
  volatile uint32_t      EXTICR3;
  volatile uint32_t      EXTICR4;
  volatile uint32_t      CMPCR;
	
	
} SYSCFG_RegDef_t;	

//...systick timer...//

		#define      NVICADD    0xE000E100
#define  NVIC ((NVIC_RegDef_t *)NVICADD)
	typedef struct
{
  volatile uint32_t     ISER0;
	volatile uint32_t     ISER1;
	
	} NVIC_RegDef_t;	

	
	//...systick timer...//
#define STKADD 0xE000E010
#define  STK ((STK_RegDef_t *)STKADD)
	typedef struct
{
  volatile uint32_t      CTRL;
	volatile uint32_t     LOAD;
	volatile uint32_t     VAL;
	volatile uint32_t     CALIB;
	
	} STK_RegDef_t;	


	//protocols
//-.......usart.......//
	
	#define  USART1ADD 0x40011000 
	#define  USART2ADD 0x40004400
	#define  USART6ADD 0x40011400
	
#define USART1   ((USART_RegDef_t *)USART1ADD)
#define USART2   ((USART_RegDef_t *)USART2ADD)
#define USART6  ((USART_RegDef_t *)USART6ADD)
	
typedef struct
{
  volatile uint32_t    SR;  
	volatile uint32_t    DR;
	volatile uint32_t    BRR;
	volatile uint32_t      CR1;
		volatile uint32_t    CR2;
	volatile uint32_t      CR3;  
	volatile uint32_t      GTPR;   
	
}USART_RegDef_t;		


//....SPI......//

#define  SPIADD 0x40013000
#define  SPI ((SPI_RegDef_t *)SPIADD)

typedef struct
{
  volatile    uint32_t      CR1; 
	volatile uint32_t         SR;
	volatile uint32_t         DR;
	volatile uint32_t       CRCPR;
		volatile uint32_t     RXCRCR;
	volatile uint32_t        TXCRCR;  
	volatile uint32_t        I2SCFGR;
	volatile uint32_t         I2SPR;
	
}SPI_RegDef_t;	

//#endif


