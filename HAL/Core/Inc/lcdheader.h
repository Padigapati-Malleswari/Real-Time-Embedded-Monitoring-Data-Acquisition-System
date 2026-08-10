

void write_high_nibble( unsigned char data );
void write_low_nibble( unsigned char data );
void KM_LCD_Init(void);
void delay(volatile int n);

void KM_LCD_Write_Cmd(unsigned char cmd);
void KM_LCD_Write_str(char str[]);
void KM_LCD_Write_Data(unsigned  char data);



