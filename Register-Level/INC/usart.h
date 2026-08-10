#include<stdint.h>
//#include  "stm32f401rbt6.h"

void UART_init(void);
void UART_config(void);
void UART6_OutChar(uint8_t ch);

 uint8_t UART6_TIMEOUT(int32_t x);
unsigned char UART6_InChar(void);

void UART6_OutChar_str(uint8_t ch[]);
  
