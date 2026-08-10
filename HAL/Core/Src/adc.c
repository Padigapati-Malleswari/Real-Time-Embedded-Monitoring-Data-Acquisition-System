  
	
	
#include "adc.h"
#include <stdint.h>



/*int  ADC_READ(int adc)
{
	int data=((adc*3.3*100)/4095);
	return data;
} */


int ADC_READ(int adc)
{
    return (adc * 330) / 4095;
}




		
