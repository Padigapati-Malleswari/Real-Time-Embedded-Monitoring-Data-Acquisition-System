/*
 * task.c
 *
 *  Created on: 26-Jul-2026
 *      Author: JAYASIMHA REDDY
 */
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "lcdheader.h"
#include "adc.h"
#include "wifi.h"
void GO_TO_config(void);

extern ADC_HandleTypeDef hadc1;
extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart6;
uint32_t t1 = 0;
uint32_t t2 = 0;
uint32_t t3 = 0;
uint32_t t4 = 0;
volatile uint8_t t1_flag = 0;
volatile uint8_t t2_flag = 0;
volatile uint8_t t3_flag = 0;
volatile uint8_t t4_flag = 0;

uint8_t sec;
uint8_t min;
uint8_t hour;
uint8_t days;
uint8_t date;
uint8_t month;
uint8_t year;

int32_t change = 0;
extern volatile uint8_t adc_done;
extern volatile uint16_t sw_dw_flag,sw_up_flag,sw_en_flag;

char *day[8] ={" ","MON","TUES","WED","THU","FRI","SAT","SUN"};
unsigned char rtc_data[7];
extern  unsigned char T_Date[7];
char buff[50];
int bcd_to_dec(unsigned char data)
{
	return ((data >> 4)*10) + (data & 0x0F);
}

uint8_t dec_to_bcd(uint8_t data)
	{
			return ((data/10)<<4) | (data%10);
	}
char buffer2[50];
 uint32_t temp;
 extern uint32_t adc;
 volatile uint8_t lm35_flag = 0;
 extern uint32_t jiffie;

 void  schedule(void)
 	{
 		if((jiffie - t1)>=1000)
 		{
 			t1_flag=1;
 			t1=jiffie;
 		}

 		if((jiffie - t2)>=5000)
 		{
 			t2_flag=1;
 			t2=jiffie;
 		}
 		if((jiffie - t3)>=6000)
 		{
 			t3_flag=1;
 			t3=jiffie;
 		}
 		if((jiffie - t4)>=9000)
 		 {
 		 	t4_flag=1;
 		 	t4=jiffie;
 		 }


 	}

void Task1_ReadRTC_WriteLCD_1Sec(void)
{
 HAL_I2C_Mem_Read(&hi2c1, 0X68<<1, 0X00, 0X01,rtc_data , 7, 100);

	  	 KM_LCD_Write_Cmd(0x80);
	  	sprintf(buff,"%02d:%02d:%02d",bcd_to_dec(rtc_data[2] &0x1F),bcd_to_dec(rtc_data[1]),bcd_to_dec(rtc_data[0]));
	  	KM_LCD_Write_str(buff);
	 /* 	if(rtc_data[2]>>5 & (0x01))
	  	{
	  		KM_LCD_Write_str("PM");
	  	}
	  	else
	  	{
	  		KM_LCD_Write_str("AM");
	  	} */

	  	KM_LCD_Write_Cmd(0xc0);
	  	sprintf(buff,"%02d-%0d-%02d",bcd_to_dec(rtc_data[4]),bcd_to_dec(rtc_data[5]),bcd_to_dec(rtc_data[6]));
	  		KM_LCD_Write_str(buff);

	  	KM_LCD_Write_Cmd(0xc8);
	  	//sprintf(buff,"%s",day[5]);
	  	KM_LCD_Write_str(day[rtc_data[3]]);

}


void Task2_ReadLM35_WriteLCD_5Sec(void)
{
    adc_done = 0;

    HAL_ADC_Start_IT(&hadc1);

    while(adc_done == 0);      // Wait for conversion to complete

    HAL_ADC_Stop_IT(&hadc1);

    temp = ADC_READ(adc);

    KM_LCD_Write_Cmd(0x8A);
    KM_LCD_Write_str("      ");

    KM_LCD_Write_Cmd(0x8A);

    sprintf(buffer2,"%ld",(long unsigned int)temp);

    KM_LCD_Write_str("T:");
    KM_LCD_Write_str(buffer2);
    KM_LCD_Write_Data(0xDF);
    KM_LCD_Write_Data('C');

    lm35_flag = 1;





/*	HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 100);
    adc = HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);

    temp=ADC_READ(adc);
	sprintf(buffer2, "%lu", temp);
	KM_LCD_Write_str("T:");
		KM_LCD_Write_str(buffer2);
		KM_LCD_Write_Data(0xDF);
		KM_LCD_Write_Data('C');
		HAL_Delay(5000);
		KM_LCD_Write_Cmd(0x01);
}*/
}


void Task3_WiFi_Tx(void)
{
if(lm35_flag == 1)
{
	wifi_operation();


}  }


void Task4_Check_InternetStatus(void)
{
    uint8_t time[3];
     uint8_t temp1;

     HAL_UART_Transmit(&huart6,"AT+CIPSTATUS\r\n",20,20);
    if(!(UART_esp8266()))
    {
        // Internet not available
    }
    else
    {
        /* Test values */
        time[0] = 0x12;
        time[1] = 0x34;
        time[2] = 0x56;

        temp1 = (uint8_t)temp;   // Test temperature

        /* Write to EEPROM */
        HAL_I2C_Mem_Write(&hi2c1, 0X50<<1, 0X00,0x01, time, 3,10);

        HAL_I2C_Mem_Write(&hi2c1,0x50<<1, 0x10, 0x01, &temp1, 1,10);


       //  Clear variables
        time[0] = 0;
        time[1] = 0;
        time[2] = 0;
        temp = 0;

     //   Read back from EEPROM
        HAL_I2C_Mem_Read(&hi2c1, 0X50<<1, 0X00,0x01, time,3,10);

        HAL_I2C_Mem_Read(&hi2c1,0x50<<1, 0x10, 0x01, &temp1, 1,10);

    }}


void Task5_SWMS_Config(void)
{
 // KM_LCD_Write_Cmd(0x01);
HAL_Delay(100);
HAL_I2C_Mem_Read(&hi2c1, 0X68<<1, 0X00, 0X01,rtc_data , 7, 100);

	 KM_LCD_Write_Cmd(0x80);
	KM_LCD_Write_str("T=");
	sprintf(buff,"%02d:%02d:%02d",bcd_to_dec(rtc_data[2] &0x1F),bcd_to_dec(rtc_data[1]),bcd_to_dec(rtc_data[0]));
	KM_LCD_Write_str(buff);
    KM_LCD_Write_Cmd(0xc0);
	KM_LCD_Write_str("D=");
	sprintf(buff,"%02d-%02d-%02d",bcd_to_dec(rtc_data[4]),bcd_to_dec(rtc_data[5]),bcd_to_dec(rtc_data[6]));
		KM_LCD_Write_str(buff);


		KM_LCD_Write_Cmd(0x8c);
		KM_LCD_Write_str("Y=PU");

		KM_LCD_Write_Cmd(0xcc);
		KM_LCD_Write_str("N=DW");
		  sw_en_flag=0;
		//  HAL_Delay(5);
while(1)
{
if(sw_dw_flag)
{
    sw_dw_flag= 0;
    HAL_Delay(5);
	  KM_LCD_Write_Cmd(0x01);
	  return ;
}
if(sw_up_flag)
{
    sw_up_flag = 0;
    HAL_Delay(20);

    sec = bcd_to_dec(rtc_data[0]);
    min = bcd_to_dec(rtc_data[1]);
    hour = bcd_to_dec(rtc_data[2] & 0x1F);
    days = bcd_to_dec(rtc_data[3]);
    date  = bcd_to_dec(rtc_data[4]);
    month = bcd_to_dec(rtc_data[5]);
    year  = bcd_to_dec(rtc_data[6]);
   KM_LCD_Write_Cmd(0x01);

	GO_TO_config();



}
}
}

void GO_TO_config()
{

	    while(1)
			{
          KM_LCD_Write_Cmd(0x80);
				KM_LCD_Write_str("T=");
					sprintf(buff,"%02d:%02d:%02d",
									hour,min,sec);
				KM_LCD_Write_str(buff);
	     KM_LCD_Write_Cmd(0xC0);
				KM_LCD_Write_str("D=");
					sprintf(buff,"%02d-%02d-%02d",
									date,month,year);
					KM_LCD_Write_str(buff);

		KM_LCD_Write_Cmd(0xcb);
	if(days >= 1 && days <= 7)
			KM_LCD_Write_str(day[days]);

		//		KM_LCD_Write_Cmd(0x01);

					if(sw_up_flag)
					{
						sw_up_flag=0;
						HAL_Delay(5);

							switch(change)
							{
									case 0: hour++;
									if (hour > 12)
									{
										hour =1;

									}

									break;
									case 1: min++;
									if (min > 59)
									{
										min =0;

									}

									break;

									case 2: sec++;

									if (sec > 59)
									{
										sec =0;

									}
									break;

									case 3:
			                      date++;

		                	if(month==4 || month==6 || month==9 || month==11)
                       {
				                	if(date > 30) date = 1;
		                      	}
		                    	else
		                  	{
			                		if(date > 31) date = 1;
			                    }
		                    	break;



									 case 4: month++;
									if (month > 12)
									{
										month=1;
									}

									break;


									case 5: year++;
									if (year > 99)
									{
										year=0;
									}
									break;

									case 6:
											 days++;
										if(days > 7)
										{
										 days = 1;
										}
										 break;

							}
					}

					if(sw_dw_flag)
					{    HAL_Delay(5);
							sw_dw_flag=0;

							switch(change)
							{
									case 0:
									if(hour <= 1)
	                  {
		               	hour = 12;
	                    }
	                    else
	                     {
	               		hour--;
                     	}

								break;

									case 1:

									if(min == 0)
	                   {
	                		min = 59;
	                      }
	                      else
	                         {
		                     	min--;
	                        }

									break;
									case 2:
										if(sec == 0)
	                    {
		               	sec = 59;
	                  }
	                  else
	                   {
		             	sec--;
	                  }


				break;
              case 3:
			if(date <= 1)
			{
					if(month==4 || month==6 || month==9 || month==11)
							date = 30;
					else
							date = 31;
			}
			else
			{
					date--;
			}
			break;




									case 4:
			if(month <= 1)
			{
					month = 12;
			}
			else
			{
					month--;
			}
			break;


									case 5:

									if(year == 0)
	                  {
		               	year = 99;
	                  }
                     	else
	                  {
			              year--;
	                     }
									break;

									case 6:
											if(days <= 1)
	                      {
			               days = 7;
	                         }
	                       else
	                          {
		                   	days--;
                          	}
											break;
							}
					}

					if(sw_en_flag)
					{
							sw_en_flag=0;

							change++;

							if(change>6)
							{
									T_Date[0]=dec_to_bcd(sec);
									T_Date[1]=dec_to_bcd(min);
									T_Date[2]=dec_to_bcd(hour);
							 //		T_Date[2] = dec_to_bcd(hour) | 0x40;
									T_Date[3]=dec_to_bcd(days);
									T_Date[4]=dec_to_bcd(date);
									T_Date[5]=dec_to_bcd(month);
									T_Date[6]=dec_to_bcd(year);

									HAL_I2C_Mem_Write(&hi2c1, 0X68<<1, 0X00, 0X01,T_Date , 7, 100);

	KM_LCD_Write_Cmd(0x01);
	KM_LCD_Write_str("TIME UPDATED");
      HAL_Delay(1000);

	sw_en_flag= 0;
	sw_up_flag= 0;
	sw_dw_flag = 0;

	change = 0;
    HAL_Delay(300);

	KM_LCD_Write_Cmd(0x01);
	//break;

							}}
					}
				}






