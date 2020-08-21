/*
 * UARTDriver.c
 *
 * Created: 8/11/2020 7:29:17 PM
 * Author : Mazen Sadek
 */ 

//#include <avr/io.h>

#include "UART.h"
#include "RegDIO.h"
#include "DIO.h"

int main(void)
{
   // code TX
	
	UART_init(9600);
	UART_sendChar('c');
	
	//code RX
	
	/*
	UART_init(9600);
	pinModepin(portA,0,OUTPUT);
	
	u8 recive=0;
	recive= UART_ReciveChar();
	if (recive == 'c'){
		digitalWrightpin(portA,0,HIGH);
	}
*/
	
    while (1) 
    {
    }
}

