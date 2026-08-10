#include <stdint.h>
#include "systick.h"
#include "stm32f401rbt6.h"
extern volatile uint32_t jiffie;
uint32_t temp;

void GPIOB_PORTB_init(void)
{
    RCC->AHB1ENR |= (0x1 << 1);      // Clock enable for GPIOB

    GPIOB->MODER &= ~(0x3 << 26);    // Clear PB13 mode bits
    GPIOB->MODER |= (0x1 << 26);     // Configure PB13 as output

    GPIOB->ODR |= (0x1 << 13);       // Set PB13 HIGH
}

void SYSTICK_TIMER_INIT(void)
{
    STK->CTRL |= (0x07);             // Enable SysTick, interrupt and processor clock
    STK->VAL = 0;                    // Clear current value register
    STK->LOAD = 16000 - 1;           // Load value for 1ms delay
}

void KM_Delay_ms(uint32_t delay)
{
    STK->VAL = 0;                    // Clear current value register
    STK->LOAD = (16000 - 1);         // Load value for 1ms delay

    temp = jiffie + delay;          // Calculate target tick count

    while(jiffie <= temp)           // Wait until delay expires
    {
        ;
    }
}

void km_delay_us_it(uint32_t delay)
{
    STK->VAL = 0;                    // Clear current value register
    STK->LOAD = (16 * delay) - 1;    // Load value for 1us delay
}