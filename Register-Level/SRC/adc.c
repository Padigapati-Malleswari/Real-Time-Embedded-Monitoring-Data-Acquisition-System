#include <stdint.h>
#include "adc.h"
#include "stm32f401rbt6.h"


extern volatile uint32_t jiffie;

void GPIO_PORT_INIT(void)
{
    RCC->AHB1ENR |= (0x3 << 1);      // Enable clock for GPIOB and GPIOC

    GPIOC->MODER &= ~(0x3);         // Clear mode bits for PC0
    GPIOC->MODER |=  (0x3);         // Configure PC0 as analog mode

    RCC->APB2ENR |= (0x1 << 8);     // Enable ADC1 clock
}

void KM_ADC_INIT()
{
    ADC->SQR3 = 0xA;                // Select ADC channel 10

    ADC->CR1 |= (0x1 << 5);         // Enable End Of Conversion interrupt

    NVIC->ISER0 |= (0x1 << 18);     // Enable ADC interrupt in NVIC

    ADC->CR2 |= (0x1 << 0);         // Enable ADC

    ADC->CR2 |= (0x1 << 30);        // Start ADC conversion
}

uint16_t ADC_READ(uint16_t adc)
{
    
    uint16_t data = ((adc * 3.3 * 100) / 4095);  // Convert ADC value to voltage percentage

    return data;                            // Return converted value
}