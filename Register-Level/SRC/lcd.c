#include "lcd.h"
#include "stm32f401rbt6.h"
#include "systick.h"
#include <stdint.h>

void lcd_config()
{
    RCC->AHB1ENR |= (0x1 << 1);          // Enable clock for GPIOB

    GPIOB->MODER &= (0xFFFCF000);        // Clear mode bits for PB0-PB5 and PB8

    GPIOB->MODER |= (0x00010555);        // Configure PB0-PB5 and PB8 as output

    GPIOB->ODR |= (0xFFFFFEC0);          // Initialize output pins
}

void write_high_nibble(uint8_t data)   // Function to write higher nibble
{
    GPIOB->ODR &= ~(0xF);                // Clear D4-D7 data lines

    GPIOB->ODR |= (data >> 4);           // Send higher nibble

    GPIOB->ODR |= (0x1 << 8);            // Enable pin HIGH

    KM_Delay_ms(20);                       // Delay

    GPIOB->ODR &= ~(0x1 << 8);           // Enable pin LOW
}

void KM_LCD_Write_str(const char str[])
{
    uint32_t i;

    for(i = 0; str[i]; i++)
    {
        KM_LCD_Write_Data(str[i]);      // Send string character by character
    }
}

void KM_LCD_Write_Cmd(uint8_t cmd)
{
    GPIOB->ODR &= ~(0x1 << 4);           // RS = 0 for command

    write_high_nibble(cmd);             // Send higher nibble

    write_low_nibble(cmd);              // Send lower nibble
}

void KM_LCD_Write_Data(uint8_t data)
{
    GPIOB->ODR |= (0x1 << 4);            // RS = 1 for data

    write_high_nibble(data);            // Send higher nibble

    write_low_nibble(data);             // Send lower nibble
}

void KM_LCD_Init(void)                  // LCD initialization
{
    KM_Delay_ms(20);                       // Power-on delay

    KM_LCD_Write_Cmd(0x33);             // Initialize sequence

    KM_Delay_ms(2);

    KM_LCD_Write_Cmd(0x32);             // Set 4-bit mode

    KM_LCD_Write_Cmd(0x0C);             // Display ON, Cursor OFF

    KM_LCD_Write_Cmd(0x01);             // Clear display
}

void write_low_nibble(uint8_t data)
{
    GPIOB->ODR &= ~(0xF);                // Clear D4-D7 data lines

    GPIOB->ODR |= (data & 0x0F);         // Send lower nibble

    GPIOB->ODR |= (0x1 << 8);            // Enable pin HIGH

    KM_Delay_ms(20);                       // Delay

    GPIOB->ODR &= ~(0x1 << 8);           // Enable pin LOW
}

/*void delay(volatile int n)
{
    int i;
    for(i=0;i<=2667*n;i++);
}*/