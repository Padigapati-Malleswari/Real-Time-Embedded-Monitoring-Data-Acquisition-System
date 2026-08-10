#include "stm32f401rbt6.h"

#include "swicth.h"

void swichs()
{
	// phase a intialization
RCC->AHB1ENR |=(0x3<<1);        //set bit 1,2 for enable port b,c
	RCC->APB2ENR |= (1<<14);
	
	//phase-b configuration
//GPIOB_MODER &=(0xF3FFFFFF);           // clearing bits 26-27 red led 
//GPIOB_MODER |=(0x04000000);     //   load the data red led 
//	
//GPIOB_MODER &=(0xCFFFFFFF);    // clearing bit 28-29 green led 
//GPIOB_MODER |=(0x10000000);    // load bits 28-29 green led 
	
	

GPIOC->PUPDR &=(0xFFFCFFFF);                   // in port c clear rhe 17-16 bits
GPIOC->PUPDR |=(0x00010000);                 // in port c load bit 01 in 17-16
	
GPIOC->PUPDR &=(0xFFF3FFFF);                   // in port c clear rhe 19-18 bits
GPIOC->PUPDR |=(0x00040000);                 // in port c load bit 01 in 19-18
	
GPIOC->PUPDR &= (0xFFCFFFFF);            // Clear bits 21-20
GPIOC->PUPDR |=  (0x00100000);           // in port c load bits 01 in 21-20
	
SYSCFG -> EXTICR3 &= ~(0x00000FFF);

SYSCFG->EXTICR3 |= (0x222);   // PC8

EXTI->FTSR |= (0x1<<8);           // set 8th bit for to configure fallig edge
EXTI->FTSR |= (0x1<<9);
EXTI->FTSR |= (0x1<<10);


  
EXTI->IMR |= (0x1<<8);                     // set 8th bit  to enable EXIT9_5 interupt line _
EXTI->IMR |= (0x1<<9);                      // set 8th bit  to enable EXIT9_5 interupt line _
EXTI->IMR |= (0x1<<10);

NVIC->ISER0 |= (0x1<<23);                    //set 23bit for nvic 
NVIC->ISER1 |= (0x1<<8);                    //set 40bit for nvic i

	
	//GPIOB_ODR |=((0x1<<13) | (0x1<<14)) ; // set 13 th bit ,14 th bit
}