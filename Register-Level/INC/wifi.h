//#include  "stm32f401rbt6.h"

#include <stdint.h>

uint8_t UART_esp8266(void);
uint8_t check_send(void);
uint8_t wifi_found(void);
uint8_t wifi_connection(void);
uint8_t wifi_operation(void);
void KM_Delay_ms(uint32_t delay);
void KM_LCD_Write_Cmd(uint8_t cmd);

