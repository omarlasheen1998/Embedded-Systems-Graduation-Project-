/*
 * uart_drivers.c
 *
 * Created: 25/08/2020 02:59:16 م
 *  Author: omar
 */ 
#include <avr/io.h>
void uart_init (void){
	
	UCSRC &= ~(1 << UMSEL); //setting the UMSEL bit to 0 for asynchronous mode
	//UBRR=f/(baud+1)= 1000000/(16*2400)-1=25
	// ubrr stamds for usart baud rate register 
	// to enable transmiter
	UCSRB|=1<<TXEN |1<<RXEN;
	//2 stop bit
	UCSRC|=1<<USBS;
	//usart char size
	UCSRC|= (1<<URSEL) |1<<UCSZ0 | 1<<UCSZ1; //for 8-bit
	UBRRH=(unsigned char) 25>>8; //25=0b00011001 ubrrh=000000000
	UBRRL=(unsigned char) 25;
	
}	
void uart_transmit(int data)
{
	
while ((UCSRA&(1<<UDRE))==0);
	UDR=data; //8-data bits
	
	
	
}

char uart_recieve(){
	while (! (UCSRA & (1 << RXC)) );
	int receiveData;
    receiveData = UDR;
	return receiveData;
	
}