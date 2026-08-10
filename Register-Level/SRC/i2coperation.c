#include <stdio.h>
	#include <string.h>
	#include "lcd.h"
	#include "i2c.h"
	#include "adc.h"
	#include "wifi.h"
	#include "stm32f401rbt6.h"
	#include <stdint.h>

	#include "usart.h"
	#include "systick.h"
	#include "i2coperation.h"

extern uint8_t sec;
extern uint8_t min;
extern uint8_t hour;
extern uint8_t days;
extern uint8_t date;
extern uint8_t month;
extern uint8_t year;

	extern char buff[50];
	char buffer2[20];
	
extern volatile uint16_t adc_data;
uint16_t lm35_data = 0;uint8_t lm35[20];
volatile uint8_t lm35_flag = 0;	

extern volatile uint32_t jiffie;

uint32_t t1 = 0;
uint32_t t2 = 0;
uint32_t t4 = 0;

volatile uint8_t t1_flag = 0;
volatile uint8_t t2_flag = 0;
volatile uint8_t t4_flag = 0;

extern volatile uint8_t SW_UP_FLAG;
extern volatile uint8_t SW_DW_FLAG;
extern volatile uint8_t SW_FLAG;

extern uint8_t change;

extern uint8_t T_Date[7];
uint8_t rtc_data[7];

extern const char *day[8];
	
	uint8_t bcd_to_dec(uint8_t data)
{
	return ((data >> 4)*10) + (data & 0x0F);
}


uint8_t dec_to_bcd(uint8_t data)
	{
			return ((data/10)<<4) | (data%10);
	}
	
	
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
		if((jiffie - t4)>=8000)
		{
			t4_flag=1;
			t4=jiffie;
		}
		
		
	}	
	
	void Task1_ReadRTC_WriteLCD_1Sec(void)
	{
  KM_I2C_Mem_Read(0x68, 0x00, 0x01, rtc_data, 7);
  //KM_LCD_Write_Cmd(0x01); 
	//	KM_Delay_ms(5);

	 KM_LCD_Write_Cmd(0x80); 
	//KM_LCD_Write_str("T=");
	sprintf(buff,"%02d:%02d:%02d",bcd_to_dec(rtc_data[2] &0x1F),bcd_to_dec(rtc_data[1]),bcd_to_dec(rtc_data[0]));
	KM_LCD_Write_str(buff);
  KM_LCD_Write_Cmd(0xc0);
//	KM_LCD_Write_str("D=");
	sprintf(buff,"%02d-%02d-%02d",bcd_to_dec(rtc_data[4]),bcd_to_dec(rtc_data[5]),bcd_to_dec(rtc_data[6]));
		KM_LCD_Write_str(buff);
 // KM_LCD_Write_Cmd(0xCA);

	}
	
	void Task2_ReadLM35_WriteLCD_5Sec(void)
		
	{
	      //  KM_Delay_ms(5000);  // Wait before next reading
    		lm35_data= ADC_READ(adc_data);     // Convert ADC value to temperatu
     		    lm35_flag = 1;

     //     KM_LCD_Write_Cmd(0x01);     // Clear LCD
        KM_Delay_ms(2);

           KM_LCD_Write_Cmd(0x8A);     // Set cursor to first line
		    
          sprintf(lm35, "%d",lm35_data); // Convert temperature to string

        KM_LCD_Write_str("T:");
        KM_LCD_Write_str(lm35);

        KM_LCD_Write_Data(0xDF);    // Display degree symbol
        KM_LCD_Write_Data('C');     // Display Celsius symbol
     //      KM_LCD_Write_Cmd(0x01); 
	}
	
	void Task3_WiFi_Tx(void)
	{
    if(lm35_flag == 1)
    {
        char buffer[100];
      UART6_OutChar_str("AT+CIPSTATUS\r\n"); // Check connection status
             KM_Delay_ms(6);
       UART6_OutChar_str("AT+CIPSTART=\"TCP\",\"142.93.218.33\",80\r\n");
        KM_Delay_ms(10);
			 UART6_OutChar_str("AT+CIPSEND=38\r\n"); // Set data length
			KM_Delay_ms(10);
      sprintf(buffer,"GET /page.php?temp=%d&hum=20&dev=21\r\n",lm35_data); // HTTP GET request

      UART6_OutChar_str(buffer); // Send request

        KM_Delay_ms(50);
			UART6_OutChar_str("AT+CIPCLOSE\r\n");
        lm35_flag = 0;
    }
}
	

void Task4_Check_InternetStatus(void)
{
    uint8_t time[3];
     uint8_t temp;

    UART6_OutChar_str("AT+CIPSTATUS\r\n");
    KM_Delay_ms(50);

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

        temp = (uint8_t)lm35_data;   // Test temperature

        /* Write to EEPROM */
        KM_I2C_Mem_Write(0x50, 0x00, 0x01, time, 3);
        KM_Delay_ms(20);

        KM_I2C_Mem_Write(0x50, 0x10, 0x01, &temp, 1);
        KM_Delay_ms(20);

       //  Clear variables 
        time[0] = 0;
        time[1] = 0;
        time[2] = 0;
        temp = 0;

     //   Read back from EEPROM 
        KM_I2C_Mem_Read(0x50, 0x00, 0x01, time, 3);
        KM_I2C_Mem_Read(0x50, 0x10, 0x01, &temp, 1);

//        sprintf(buffer2,
//                "%02X:%02X:%02X T=%dC",
//                time[0],
//                time[1],
//                time[2],
//                temp);

//        KM_LCD_Write_Cmd(0x01);
//        KM_Delay_ms(2);

//        KM_LCD_Write_Cmd(0x80);
//        KM_LCD_Write_str(buffer2);

//        KM_Delay_ms(3000);
    }
}

void Task5_SWMS_Config(void)
{
 // KM_LCD_Write_Cmd(0x01);
     KM_Delay_ms(5);
		KM_I2C_Mem_Read(0x68, 0x00, 0x01, rtc_data, 7);

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
		SW_FLAG = 0;
while(1)
{	
if(SW_DW_FLAG)
{
    SW_DW_FLAG = 0;
	  KM_LCD_Write_Cmd(0x01);
	  return ;
}
if(SW_UP_FLAG)
{
    SW_UP_FLAG = 0;

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

					if(SW_UP_FLAG)
					{
							SW_UP_FLAG=0;

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

					if(SW_DW_FLAG)
					{
							SW_DW_FLAG=0;

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

					if(SW_FLAG)
					{
							SW_FLAG=0;

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

									KM_I2C_Mem_Write(0x68,0x00,0x01,T_Date,7);

	KM_LCD_Write_Cmd(0x01);
	KM_LCD_Write_str("TIME UPDATED");

	KM_Delay_ms(1000);

	SW_FLAG = 0;
	SW_UP_FLAG = 0;
	SW_DW_FLAG = 0;

	change = 0;

	KM_Delay_ms(300);

	KM_LCD_Write_Cmd(0x01);
	//break;

							}}
					}
				}
		

		
	
