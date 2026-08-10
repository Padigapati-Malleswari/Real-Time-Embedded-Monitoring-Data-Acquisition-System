
//#include  "stm32f401rbt6.h"

void UART_init();
void UART_config();
void UART6_OutChar(unsigned char ch);

 int UART6_TIMEOUT(int);
unsigned char UART6_InChar(void);

void UART6_OutChar_str(unsigned char ch[]);
  
