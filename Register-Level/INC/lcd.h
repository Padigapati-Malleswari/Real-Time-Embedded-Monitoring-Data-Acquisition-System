#include <stdint.h>


void KM_LCD_Init(void);
 
//svoid delay(int);

void KM_LCD_Write_str(const char str[]);
void lcd_config(void);
void KM_Delay_ms(uint32_t delay);

void write_high_nibble(uint8_t data);
void write_low_nibble(uint8_t data);
void KM_LCD_Write_Cmd(uint8_t cmd);
void KM_LCD_Write_Data(uint8_t data);