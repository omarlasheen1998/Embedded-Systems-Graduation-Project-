
#include <avr/interrupt.h>
#include "interrupt.h"
#include "DIO.h"
int main(void)
{
	pinModeport(portA,OUTPUT);
	pinModeport(portB,OUTPUT);
	pinModeport(portC,OUTPUT);
	
    INT_initilizaiton(int0,Falling);
	INT_initilizaiton(int1,Falling);
    INT_initilizaiton(int2,Falling);
    while (1) 
    {
    }
	
}

ISR(INT0_vect){
	
	digitalWrightpin(portA,0,HIGH);
	digitalWrightpin(portA,1,LOW);
	digitalWrightpin(portA,2,HIGH);
}

ISR(INT1_vect){
	digitalWrightpin(portB,0,HIGH);
	digitalWrightpin(portB,1,LOW);
	digitalWrightpin(portB,2,HIGH);
	
}

ISR(INT2_vect){
	
	digitalWrightpin(portC,0,HIGH);
	digitalWrightpin(portC,1,LOW);
	digitalWrightpin(portC,2,HIGH);
	
}
