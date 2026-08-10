#include "stm32f401rbt6.h"
#include "usart.h"
#include "lcd.h"
#include "systick.h"
#include "wifi.h"
#include "adc.h"
#include "i2c.h"
#include "swicth.h"
#include <stdio.h>
#include <string.h>
int config_mode = 0;
int field = 0;

unsigned char sec;
unsigned char min;
unsigned char hour;
unsigned char day_val;
unsigned char date;
unsigned char month;
unsigned char year;
unsigned int a, b, c;
int i;
volatile int  SW_UP_FLAG=0,SW_DW_FLAG=0,SW_FLAG=0;

int jiffie = 0;
int ret;
char *day[8]={
"",
"SUN",
"MON",
"TUE",
"WED",
"THU",
"FRI",
"SAT"
};
unsigned char rtc_data[7]; 
unsigned char T_Date[7]={0x50,0x17,0x70,0x5,0x26,0x06,0x26};
char buff[50];
unsigned char dec_to_bcd(unsigned char data)
{
    return ((data/10)<<4) | (data%10);
}
int bcd_to_dec(unsigned char data)
{
	return ((data >> 4)*10) + (data & 0x0F);
}



void GO_TO_config(void)
{
    KM_LCD_Write_Cmd(0x01);

    while(1)
    {
        KM_LCD_Write_Cmd(0x80);

        sprintf(buff,"%02d:%02d:%02d",
                hour,min,sec);
        KM_LCD_Write_str(buff);

        KM_LCD_Write_Cmd(0xC0);

        sprintf(buff,"%02d-%02d-%02d",
                date,month,year);
        KM_LCD_Write_str(buff);

        if(SW_UP_FLAG)
        {
            SW_UP_FLAG=0;

            switch(field)
            {
                case 0: hour++; break;
                case 1: min++; break;
                case 2: sec++; break;
                case 3: date++; break;
                case 4: month++; break;
                case 5: year++; break;
                case 6: day_val++; break;
            }
        }

        if(SW_DW_FLAG)
        {
            SW_DW_FLAG=0;

            switch(field)
            {
                case 0: hour--; break;
                case 1: min--; break;
                case 2: sec--; break;
                case 3: date--; break;
                case 4: month--; break;
                case 5: year--; break;
                case 6: day_val--; break;
            }
        }

        if(SW_FLAG)
        {
            SW_FLAG=0;

            field++;

            if(field>6)
            {
                T_Date[0]=dec_to_bcd(sec);
                T_Date[1]=dec_to_bcd(min);
                T_Date[2]=dec_to_bcd(hour);
                T_Date[3]=dec_to_bcd(day_val);
                T_Date[4]=dec_to_bcd(date);
                T_Date[5]=dec_to_bcd(month);
                T_Date[6]=dec_to_bcd(year);

                KM_I2C_Mem_Write(0x68,0x00,0x01,T_Date,7);

                KM_LCD_Write_Cmd(0x01);
                KM_LCD_Write_str("TIME SAVED");

                KM_Delay_ms(2000);

                field=0;
                break;
            }
        }
    }
	}


int main()
{
	void switchs();

 SYSTICK_TIMER_INIT();      // Initialize SysTick timer
   lcd_config();              // Configure LCD

    KM_LCD_Init();             // Initialize LCD
  //  lcd_config();              // Configure LCD

KM_I2C1_Init();
	KM_I2C1_Config();
	
//	KM_I2C_Mem_Write(0x68, 0x00, 0x01, T_Date, 7);
 
//	for(i=0;i<128;i++)
//	{
while(1)
{   
	//KM_LCD_Write_Cmd(0x01);
   //  KM_Delay_ms(2);
		KM_I2C_Mem_Read(0x68, 0x00, 0x01, rtc_data, 7);

	 KM_LCD_Write_Cmd(0x80); 
	sprintf(buff,"%02d:%02d:%02d",bcd_to_dec(rtc_data[2] &0x1F),bcd_to_dec(rtc_data[1]),bcd_to_dec(rtc_data[0]));
//KM_LCD_Write_Cmd(0x01);
//KM_Delay_ms(2);
	KM_LCD_Write_str(buff);
	if(rtc_data[2]>>5 & (0x01))
	{
		KM_LCD_Write_str("PM");
	}
	else
	{
		KM_LCD_Write_str("AM");
	}
		
	KM_LCD_Write_Cmd(0xc0); 
	sprintf(buff,"%02d-%02d-%02d",bcd_to_dec(rtc_data[4]),bcd_to_dec(rtc_data[5]),bcd_to_dec(rtc_data[6]));
		KM_LCD_Write_str(buff);
	
	KM_LCD_Write_Cmd(0xc8); 
	//sprintf(buff,"%s",day[5]);
	if(rtc_data[5] <= 7)
 //   KM_LCD_Write_str(day[rtc_data[3]]);
	KM_LCD_Write_str(day[rtc_data[5]]);
	

	if(SW_FLAG)
	{
		KM_LCD_Write_Cmd(0x8c);
		KM_LCD_Write_str("Y=PU");
	
		KM_LCD_Write_Cmd(0xcc);
		KM_LCD_Write_str("N=DW");
		
    SW_FLAG = 0;
}

if(SW_DW_FLAG)
{
    SW_DW_FLAG = 0;
}
if(SW_UP_FLAG)
{
    SW_UP_FLAG = 0;

    sec   = bcd_to_dec(rtc_data[0]);
    min   = bcd_to_dec(rtc_data[1]);
    hour  = bcd_to_dec(rtc_data[2] & 0x1F);
    day_val = rtc_data[3];
    date  = bcd_to_dec(rtc_data[4]);
    month = bcd_to_dec(rtc_data[5]);
    year  = bcd_to_dec(rtc_data[6]);

    GO_TO_config();
}

            
 }              
	
}
	
	





	void SysTick_Handler(void)
{
    jiffie++;                  // Increment millisecond counter
}


void EXTI9_5_IRQHandler(void)	
	{
		if(EXTI_PR & (0x1<<8))
		{
			SW_UP_FLAG=1;
		
		EXTI_PR |=(0x1<<8);
		}
		if(EXTI_PR & (0x1<<9))
		{
			SW_DW_FLAG=1;
		
		EXTI_PR |=(0x1<<9);
		}
		
	}
	
	
	
	
	void EXTI15_10_IRQHandler(void)
	{
		if(EXTI_PR & (0x1<<10))
		{
			SW_FLAG =1;
		
		EXTI_PR |=(0x1<<10);
		}
	}

