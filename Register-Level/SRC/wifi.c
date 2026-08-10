#include "wifi.h"
#include <string.h>

#include "stm32f401rbt6.h"
#include "usart.h"
#include "lcd.h"
#include <stdio.h>
#include<stdint.h>


uint32_t timeout = 1000000;                 // Timeout value

uint8_t buffer[1000];            // Buffer to store ESP8266 responses

extern uint8_t buff1;             // UART received character

//extern unsigned char buff[1000];

char buffer1[100];                     // Buffer for HTTP request string

uint8_t UART_esp8266()
{
    uint32_t i;

    for(i = 0; i < 100; i++)
    {
        if(!(UART6_TIMEOUT(100)))    // Wait for UART data
        {
            buffer[i] = buff1;          // Store received character

            if(i > 0 && buffer[i] == 'K' && buffer[i - 1] == 'O')
                return 0;              // "OK" received
        }
    }

    return 1;                          // Timeout or response not received
}

uint8_t check_send(void)
{
    uint32_t i;


    for(i = 0; i < 1000; i++)
    {
        if(!(UART6_TIMEOUT(2000)))     // Wait for UART data
        {
            buffer[i] = buff1;          // Store received character

            if(i > 0 &&
               buffer[i] == 'e' &&
               buffer[i - 1] == 'n' &&
               buffer[i - 2] == 'o' &&
               buffer[i - 3] == 'd')
                return 0;              // Detect "done"
        }
    }

    return 1;                          // Data send failed
}

uint8_t wifi_found(void)
{
    UART6_OutChar_str("AT\r\n");       // Send AT command

    //delay(1000);

    if(!(UART_esp8266()))
    {
        return 0;                      // ESP8266 found
    }
    else
    {
        return 1;                      // ESP8266 not found
    }
}

uint8_t wifi_connection(void)
{
    UART6_OutChar_str("AT+RST\r\n");   // Reset ESP8266

    //delay_IT(5000);

    UART6_OutChar_str("AT+CWMODE=3\r\n"); // Set WiFi mode

    //delay_IT(1000);

    if(!(UART_esp8266()))
    {
        UART6_OutChar_str("AT+CWJAP=\"KMLearnX2-2.4G\",\"9963111084\"\r\n"); // Connect to WiFi

        KM_Delay_ms(100);

        if(!(UART_esp8266()))
        {
            // UART6_OutChar_str("AT+CIFSR\r\n");

            // delay_IT(20);

            // if(!(UART_esp8266()))
            // {

            UART6_OutChar_str("AT+CIPMUX=0\r\n"); // Single connection mode

            // delay_IT(1000);

            if(!(UART_esp8266()))
            {
                return 0;              // WiFi connected successfully
            }
        }
    }

    return 1;                          // WiFi connection failed
}

uint8_t wifi_operation()
{
    // if(!(UART_esp8266()))

    UART6_OutChar_str("AT+CIPSTATUS\r\n"); // Check connection status

    // delay_IT(50);

    if(!(UART_esp8266()))
    {
        UART6_OutChar_str("AT+CIPSTART=\"TCP\",\"142.93.218.33\",80\r\n"); // Open TCP connection

        // delay_IT(50);

        if(!(UART_esp8266()))
        {
            UART6_OutChar_str("AT+CIPSEND=37\r\n"); // Set data length

            // delay_IT(100);

            if(!(UART_esp8266()))
            {
                sprintf(buffer1,
                        "GET /page.php?temp=35&hum=20&dev=21\r\n"); // HTTP GET request

                UART6_OutChar_str(buffer1); // Send request

                // delay_IT(200);

                // UART6_OutChar_str("AT+CIPCLOSE\r\n");

                if(!(check_send()))
                {
                    return 0;          // Data transmitted successfully
                }
            }
        }
    }

    return 1;                          // Data transmission failed
}