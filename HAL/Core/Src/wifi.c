#include "wifi.h"
#include <string.h>
#include "usart.h"
#include "lcdheader.h"
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"
//#include "main.h"

 //UART_HandleTypeDef huart6;                // Timeout value
//UART_HandleTypeDef huart6;
//extern uint32_t huart6;
extern UART_HandleTypeDef huart6;

uint8_t buffer[1000];            // Buffer to store ESP8266 responses

extern uint8_t buff;
extern uint32_t temp;// UART received character

//extern unsigned char buff[1000];

char buffer1[100];
int strstr1(char s[],char sub[]){
	int i,p;
	for(i=0;s[i];i++){
		p=i;
		 if(s[i]==sub[0]){
			 int j;
			 for(j=0;sub[j];j++,p++)
			 {
				 if(s[p]!=sub[j])
				 {
					 break;
				 }
			 }
		 	 if(sub[j]=='\0')
			 {
				 return 0;
			 }
		 }
	}
	return 1;
}// Buffer for HTTP request string

int UART_esp8266()
{

	HAL_UART_Receive(&huart6, buffer, 100, 100);  // Wait for UART data

	for(int i=0;i<100;i++)
	{
		   if(!strstr1((char *)buffer, "OK"))
				{
					return 0;
				}

			}
			return 1;
	}


                           // Timeout or response not re

int check_send(void)
{
	HAL_UART_Receive(&huart6,buffer,100,100);
		for(int i=0;i<100;i++)
			{
			if(!strstr1((char *)buffer, "done"))
			{
				return 0;
			}
			}
		return 1;

	}


int wifi_found()
{
  //  UART6_OutChar_str("AT\r\n");
	HAL_UART_Transmit(&huart6,"AT\r\n",15,20);// Send AT command

    //delay(1000);

    if(!(UART_esp8266()))
    {
    /*	KM_LCD_Write_Cmd(0x01);    // Clear LCD
    	 HAL_Delay(2);
         KM_LCD_Write_str("WIFI FOUND"); */
         return 0;// ESP8266 found
    }
    else
    {
    	   /*  KM_LCD_Write_Cmd(0x01);    // Clear LCD
    	    	 HAL_Delay(2);
    	         KM_LCD_Write_str("WIFI NOT FOUND");*/
    	         return 1;               // ESP8266 not found
    }
}

int wifi_connection()
{
  //  UART6_OutChar_str("AT+RST\r\n");   // Reset ESP8266
	HAL_UART_Transmit(&huart6,"AT+RST\r\n",15,200);

    //delay_IT(5000);

  //  UART6_OutChar_str("AT+CWMODE=3\r\n"); // Set WiFi mode
	HAL_UART_Transmit(&huart6,"AT+CWMODE=3\r\n",15,20);


    //delay_IT(1000);

    if(!(UART_esp8266()))
    {
    //    UART6_OutChar_str("AT+CWJAP=\"Sri Karthikeya 1st Floor\",\"6304617881\"\r\n"); // Connect to WiFi
    	HAL_UART_Transmit(&huart6,"AT+CWJAP=\"Sri Karthikeya 1st Floor\",\"6304617881\"\r\n",100,100);
        HAL_Delay(500);

        if(!(UART_esp8266()))
        {
            // UART6_OutChar_str("AT+CIFSR\r\n");
        	HAL_UART_Transmit(&huart6,"AT+CIFSR\r\n",15,100);

            // delay_IT(20);

            // if(!(UART_esp8266()))
            // {

         //   UART6_OutChar_str("AT+CIPMUX=0\r\n"); // Single connection mode
        	HAL_UART_Transmit(&huart6,"AT+CIPMUX=0\r\n",20,100);

        	HAL_Delay(20);
            // delay_IT(1000);

            if(!(UART_esp8266()))
            {
            	/*KM_LCD_Write_Cmd(0x01); // Clear LCD
            	  HAL_Delay(2);
               KM_LCD_Write_str("CONNECTION DONE");*/
                return 0;              // WiFi connected successfully
            }
        }
    }
   /* KM_LCD_Write_Cmd(0x01); // Clear LCD
      HAL_Delay(2);
   KM_LCD_Write_str("NOT CONNECTED"); */

    return 1;                          // WiFi connection failed
}

int wifi_operation()
{
    // if(!(UART_esp8266()))

 //   UART6_OutChar_str("AT+CIPSTATUS\r\n"); // Check connection status
	HAL_UART_Transmit(&huart6,"AT+CIPSTATUS\r\n",20,20);
    // delay_IT(50);

    if(!(UART_esp8266()))
    {
    //    UART6_OutChar_str("AT+CIPSTART=\"TCP\",\"142.93.218.33\",80\r\n"); // Open TCP connection
    	HAL_UART_Transmit(&huart6,"AT+CIPSTART=\"TCP\",\"142.93.218.33\",80\r\n",50,20);
    	HAL_Delay(100);
        // delay_IT(50);

        if(!(UART_esp8266()))
        {
        //    UART6_OutChar_str("AT+CIPSEND=37\r\n"); // Set data length
        	HAL_UART_Transmit(&huart6,"AT+CIPSEND=37\r\n",50,20);
        	HAL_Delay(10);
            // delay_IT(100);

            if(!(UART_esp8266()))
            {
                sprintf(buffer1,
                        "GET /page.php?temp=%d&hum=20&dev=21\r\n",temp); // HTTP GET request
                HAL_UART_Transmit(&huart6,buffer1,50,20);
                HAL_Delay(10);
//
          //      UART6_OutChar_str(buffer1); // Send request
               // HAL_UART_Transmit(&huart6,buffer1,50,100);

                // delay_IT(200);

                // UART6_OutChar_str("AT+CIPCLOSE\r\n");

                if(!(check_send()))
                {
                	/*HAL_Delay(2);
                	KM_LCD_Write_Cmd(0x01);
                   KM_LCD_Write_Cmd(0x80);
                 KM_LCD_Write_str("DATA TRANSMITTED"); */
                //	 KM_LCD_Write_Cmd(0x01);
                	 KM_LCD_Write_Cmd(0xCC);
                	 KM_LCD_Write_str("    ");
                	 KM_LCD_Write_Cmd(0xCD);
                	 KM_LCD_Write_str("OK");
                  return 0;          // Data transmitted successfully
                }
            }
        }
    }
    HAL_Delay(2);
  /*  KM_LCD_Write_Cmd(0x01);
    KM_LCD_Write_Cmd(0x80);
    KM_LCD_Write_str("TRANSMISSION");
    KM_LCD_Write_Cmd(0xC0);
     KM_LCD_Write_str("FAILED"); */
 //   KM_LCD_Write_Cmd(0x01);
    KM_LCD_Write_Cmd(0xCC);
    KM_LCD_Write_str("     ");
    KM_LCD_Write_Cmd(0xCC);
    KM_LCD_Write_str("NO");
    return 1;                          // Data transmission failed
}
