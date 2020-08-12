/*
 * UART.c
 *
 * Created: 8/11/2020 7:32:22 PM
 *  Author: Mazen Sadek
 */ 

#include "RegDIO.h"
#include "UART.h"


void UART_init(int buadRate ){

UCSRB =0x18;

UCSRC =0x86;





switch (buadRate) 

{	
case 9600:  UBRRL =0x33;   break;  //9600
case 4800:  UBRRL =0x67;   break;  //4800
}	

}

void UART_sendChar(u8 data){
	
	while (  (UCSRA & (1<<5) ) == 0) ;
	UDR=data;
}


u8 UART_ReciveChar(void){
	
	u8 result;
	while (  (UCSRA & (0x80) ) == 0) ;
	result = UDR;
	return result;
}

