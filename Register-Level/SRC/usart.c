#include<stdint.h>
#include "usart.h"
#include "lcd.h"
#include "stm32f401rbt6.h"

//unsigned char str[20] = "MALLISWARI";

uint8_t buff1;                         // Variable to store received UART data

void UART_init()
{
    // USART initialization

    RCC->AHB1ENR |= (0x1 << 2);     // Enable clock for GPIOC

    RCC->APB2ENR |= (0x1 << 5);     // Enable clock for USART6

    GPIOC->MODER &= ~(0xF << 12);   // Clear mode bits for PC6 and PC7

    GPIOC->MODER |= (0xA << 12);    // Configure PC6 and PC7 as Alternate Function mode

    GPIOC->AFRL &= ~(0xFF << 24);   // Clear alternate function bits
    GPIOC->AFRL |= (0x88 << 24);    // Select AF8 (USART6) for PC6 and PC7
}

void UART_config()
{
    // USART configuration

    USART6->BRR = 0x8B;            // Set baud rate

    USART6->CR1 |= (0x1 << 13);    // Enable USART6

    USART6->CR1 |= (0x1 << 3);     // Enable transmitter

    USART6->CR1 |= (0x1 << 2);     // Enable receiver
}

void UART6_OutChar(uint8_t ch)
{
    while(!(USART6->SR & (0x1 << 7)));   // Wait until TXE bit becomes 1

    USART6->DR = ch;                     // Load character into data register
}

uint8_t UART6_TIMEOUT(int32_t x)
{
    // x = x * 1229;

    while(x--)
    {
        if((USART6->SR & (0x1 << 5)))   // Check RXNE flag
        {
            buff1 = USART6->DR;           // Read received character

            // KM_LCD_Write_str(buff);

            return 0;                   // Data received successfully
        }
    }

    return 1;                           // Timeout occurred
}

unsigned char UART6_InChar(void)
{
    while(!(USART6->SR & (0x1 << 5)));   // Wait until RXNE bit becomes 1

    return USART6->DR;                   // Return received data
}

void UART6_OutChar_str(uint8_t ch[])
{
    uint32_t i = 0;

    for(i = 0; ch[i]; i++)
    {
        UART6_OutChar(ch[i]);           // Transmit string character by character
    }
}