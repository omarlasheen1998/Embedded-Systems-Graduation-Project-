
#include "ADC.h"
#include "DIO.h"

int main(void)
{
	u16 x=0;
   pinModepin(portA,1,INPUT);
   pinModeport(portC,OUTPUT);
   ADC_initilization(AREF,1,10);
   
   
    while (1) 
    {
		x=ADC_getValue(10);
		digitalWrightport(portC,x);
    }
}

