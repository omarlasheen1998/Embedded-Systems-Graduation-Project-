
//#include <avr/io.h>

#include "DIO.h"
#define cmd  HIGH
int main(void)
{
    /* Replace with your application code */
	/*pinModepin(portA,1,INPUT);
	pinModepin(portA,2,OUTPUT);
	pinModeport(portB,OUTPUT);*/
	
	pinModeport(portC,OUTPUT);
	
    while (1) 
    {
		/*if(digitalRead(portA,1)==HIGH)
		digitalWrightpin(portA,2,HIGH);
		
		else if(digitalRead(portA,1)==LOW)
		digitalWrightpin(portA,2,LOW);
		
		digitalWrightport(portB,HIGH);*/
		
		digitalWrightport(portC,cmd);
    }
}

