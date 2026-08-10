#include "usart.h"
#include "lcdheader.h"

//unsigned char str[20] = "MALLISWARI";


void UART6_OutChar_str(unsigned char ch[])
{
    int i = 0;

    for(i = 0; ch[i]; i++)
    {
        UART6_OutChar(ch[i]);           // Transmit string character by character
    }
}
