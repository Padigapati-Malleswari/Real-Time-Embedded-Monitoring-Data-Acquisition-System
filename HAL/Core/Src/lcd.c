  
	
	
#include "lcdheader.h"
//#include "stm32f401rbt6.h"
#include "main.h"
	
	

void  KM_LCD_Write_Cmd(unsigned char data)
	  {
	      //GPIOB_ODR &=~(0X1<<4);	//clearing the 4th bit position to make rs 0 which is for command
	      HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, 0);
	      write_high_nibble(data);
	      write_low_nibble(data);

	  }
	  void KM_LCD_Write_Data(unsigned  char data)

	  {
	      //GPIOB_ODR |=(0X1<<4);	//clearing the 4th bit position to make rs 0 which is for command
	     HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, 1);
	  	 write_high_nibble(data);
	  	 write_low_nibble(data);

	  }
	  void write_high_nibble(unsigned char data)
	  {
	     //GPIOB_ODR &=~(0X0F);//clearing the bit positions 0,1,2,3
		  data>>=4;
	     HAL_GPIO_WritePin(GPIOB,D1_Pin|D2_Pin|D3_Pin|D4_Pin, 0);
	     //GPIOB_ODR |=data>>4;//left shifting for 4 times so higher nibble get at lower nibble
	     HAL_GPIO_WritePin(GPIOB, D1_Pin, data&0x1);
	     HAL_GPIO_WritePin(GPIOB, D2_Pin, data&0x2);
	     HAL_GPIO_WritePin(GPIOB, D3_Pin, data&0x4);
	     HAL_GPIO_WritePin(GPIOB, D4_Pin, data&0x8);
	    // GPIOB_ODR |=(0X1<<8);//setting the 8th bit position to set the enable which allows to transmit data to lcd
	     HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, 1);
	     //delay(10);//delay
	     HAL_Delay(10);
	    // GPIOB_ODR &=~(0X1<<8);//clearing the 8th bit position to clear the enable which makes it low
	     HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, 0);
	  }


	  void KM_LCD_Init(void)
	  {
	  	//delay(20);
	  	HAL_Delay(20);
	  	KM_LCD_Write_Cmd(0x33); // 0x33 and 032 which converts the 8 bit into 4 bit
	  	//delay(1);
	  	HAL_Delay(1);
	  	KM_LCD_Write_Cmd(0x32);
	  	//HAL_Delay(10);
	  	KM_LCD_Write_Cmd(0x0c); // 0x0c is display on cursor off
	  //	HAL_Delay(10);
	  	KM_LCD_Write_Cmd(0x01); // 0x01 is to clear the display
	  	//HAL_Delay(10);
	  }

	  void KM_LCD_Write_str(char str[])
	  {
	  	int i=0;
	  	while(str[i]!='\0')
	  	{
	  		KM_LCD_Write_Data(str[i]); //calling the lcd data write function and passing each character to display on lcd
	  		i++;
	  	}
	  	}


	 void  delay(volatile int n)
	  {
	  	unsigned int i;
	  for(i=0;i<=2677*n;i++); //delay function
	  }

	  void write_low_nibble(unsigned char data)
	  {
	  //GPIOB_ODR &=~(0X0F);//clearing the bit positions 0,1,2,3
	  HAL_GPIO_WritePin(GPIOB,D4_Pin|D3_Pin|D2_Pin|D1_Pin, 0);
	  	//GPIOB_ODR |= data&(0x0f);//by performing bitwise and with 0x0f with data and or to the gpio_odr to get the lower nibble
	  	HAL_GPIO_WritePin(GPIOB, D1_Pin, data&0x01);
	  	   HAL_GPIO_WritePin(GPIOB, D2_Pin, data&0x02);
	  	   HAL_GPIO_WritePin(GPIOB, D3_Pin, data&0x04);
	  	   HAL_GPIO_WritePin(GPIOB, D4_Pin, data&0x08);
	  		//GPIOB_ODR |=(0X1<<8);//setting the enable control line
	  		HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, 1);
	  	//delay(10);
	  	HAL_Delay(10);
	  	//GPIOB_ODR &=~(0X1<<8);//clearing the enable control line
	  	HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, 0);
	  }
