#include "stm32f401rbt6.h"
#include "usart.h"
#include "lcd.h"
#include "systick.h"
#include "wifi.h"
#include "adc.h"
#include "i2c.h"
#include "i2coperation.h"
#include "swicth.h"
#include <stdio.h>
#include <string.h>
#include<stdint.h>


void Task1_ReadRTC_WriteLCD_1Sec(void);
void Task2_ReadLM35_WriteLCD_5Sec(void);
void Task3_WiFi_Tx(void);
void Task4_Check_InternetStatus(void);
void Task5_SWMS_Config(void);
void schedule();
int32_t change = 0;

extern volatile uint8_t t1_flag;
extern volatile uint8_t t2_flag;
extern volatile uint8_t t4_flag;


uint8_t sec;
uint8_t min;
uint8_t hour;
uint8_t days;
uint8_t date;
uint8_t month;
uint8_t year;

uint32_t i;

volatile uint8_t SW_UP_FLAG = 0;
volatile uint8_t SW_DW_FLAG = 0;
volatile uint8_t SW_FLAG    = 0;

volatile uint32_t jiffie = 0;
volatile uint16_t adc_data;
extern volatile uint8_t lm35_flag;

	const char *day[8]={
"",
"SUN",
"MON",
"TUE",
"WED",
"THU",
"FRI",
"SAT"
};
//unsigned char rtc_data[7]; 
//signed char T_Date[7]={0x254x12,0x71,0x1,0x28,0x06,0x26};
uint8_t T_Date[7]={0x25,0x37,0x60,0x1,0x30,0x06,0x26};

uint8_t buff[50];
	
	int main(void)
{
	GPIO_PORT_INIT();   
	SYSTICK_TIMER_INIT();      // Initialize SysTick timer
   lcd_config();              // Configure LCD
   KM_LCD_Init();             // Initialize LCD
  //  lcd_config();              // Configure LCD
	KM_I2C1_Init();
	KM_I2C1_Config();
	KM_ADC_INIT();
 UART_init();
  UART_config();

	 swichs();

  
	UART6_OutChar_str("AT\r\n"); 
		  	KM_Delay_ms(10);
//		   	UART6_OutChar_str("AT+RST\r\n"); 
//		  	KM_Delay_ms(10);
          UART6_OutChar_str("AT+CWMODE=0\r\n");
           KM_Delay_ms(10);
			// UART6_OutChar_str("AT+CWJAP=\"KMLearnX2-2.4G\",\"9963111084\"\r\n"); // Connect to WiFi
			 UART6_OutChar_str("AT+CWJAP=\"Sri Karthikeya 1st Floor\",\"6304617881\"\r\n"); // Connect to WiFi

			KM_Delay_ms(10);
		//	KM_I2C_Mem_Write(0x68,0x00,0x01,T_Date,7);
 
while(1)
{      
         schedule();
	      if(t1_flag)
        {
        Task1_ReadRTC_WriteLCD_1Sec();
					t1_flag = 0;
         }
	       if(t2_flag)
				{
    
	      Task2_ReadLM35_WriteLCD_5Sec();
					t2_flag = 0;
				}

	     Task3_WiFi_Tx();
				if(t4_flag)
				{
  
      Task4_Check_InternetStatus();
					t4_flag = 0;
				}
                              
	    if(SW_FLAG)
        {    KM_LCD_Write_Cmd(0x01);
	                SW_FLAG=0;
	
              Task5_SWMS_Config();
        }
}
}

void ADC_IRQHandler(void)
{
    adc_data = ADC->DR;              // Read ADC conversion result
     ADC->CR2 |=(0x1 << 30); 
    ADC->SR &= ~(0x1 << 1);     // Clear End Of Conversion flag
}

void EXTI9_5_IRQHandler(void)	
	{
		if(EXTI->PR & (0x1<<8))
		{
			SW_UP_FLAG=1;
		
		EXTI->PR |=(0x1<<8);
		}
		if(EXTI->PR & (0x1<<9))
		{
			SW_DW_FLAG=1;
		
		EXTI->PR |=(0x1<<9);
		}
		
	}
	
	
	
	
	void EXTI15_10_IRQHandler(void)
	{
		if(EXTI->PR & (0x1<<10))
		{
			SW_FLAG =1;
		
		EXTI->PR |=(0x1<<10);
		}
	}



void SysTick_Handler(void)
{
    jiffie++;                  // Increment millisecond counter
}