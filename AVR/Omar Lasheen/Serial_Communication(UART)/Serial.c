/*
 * CFile1.c
 *
 * Created: 5/16/2020 5:00:32 PM
 *  Author: Lasheen
 */ 
/*
 * GccApplication1.c
 *
 * Created: 9/19/2018 3:28:52 PM
 * Author : Omar Lasheen
 */ 
#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#define BAUDRATE ((F_CPU)/(baud*16UL)-1)            // set baud rate value for UBRR
#define BAUDRATE_U2X ((F_CPU)/(baud*8UL)-1)
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Serial.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
int baud;
void (*RXC_ISR)(void)='\0';
void (*TXC_ISR)(void)='\0';
// function to send data
void Set_U2X_transmission(void){
	UBRRH = (BAUDRATE_U2X>>8);                      // shift the register right by 8 bits
	UBRRL = BAUDRATE_U2X;                           // set baud rate
	UCSRA|= 1<<U2X;
}
void Serial_print (void* data,unsigned char type)
{ 
	char array[16];
	if(type == INT)
	{
		sprintf(array, "%d", *(int *)data);
	
	for(int i=0;(array[i]!='\0');i++)
	{
		while (!( UCSRA & (1<<UDRE)));                // wait while register is free
		UDR = array[i];
		
	}                                   // load data in the register

	}
	
	else if(type == FLOAT)
	{
		float f1,f2;
		int i1,i2;
		f1=floor(*(float *)data);
		f2=(*(float *)data) - f1;
		i1 = (int)f1;
		i2 = (int)1000*f2;
		sprintf(array,"%d.%d", i1,i2);
	for(int i=0;(array[i]!='\0');i++)
	{
		while (!( UCSRA & (1<<UDRE)));                // wait while register is free
		UDR = array[i];
		
	}                                   // load data in the register

	}
	
	else if(type == CHAR)
	{
		
		UDR = *(char*)data;
		
	}
	else if(type == STRING)
	{
		
		for(int i=0;*(char*)(data+i)!='\0';i++)
		{
			while (!( UCSRA & (1<<UDRE)));                // wait while register is free
			UDR = *(char*)(data+i);
			
		}                                   // load data in the register

	}
	
	}
// function to initialize UART
void Serial_begin (int BAUD)
{
	baud=BAUD;
	UBRRH = (BAUDRATE>>8);                      // shift the register right by 8 bits
	UBRRL = BAUDRATE;                           // set baud rate
	UCSRB|= ((1<<TXEN)|(1<<RXEN));                // enable receiver and transmitter
	UCSRC|= (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);   // 8bit data format,1 stop bit
}


bool Serial_available(void){  return ((UCSRA) & (1<<RXC)); }   

void Add_ParityBit(unsigned char UART_PARITY){
	  if (UART_PARITY == NO_PARITY)
	 { UCSRC&= ~(1<<UPM0);
	   UCSRC&= ~(1<<UPM1);}
	  else if (UART_PARITY == EVEN_PARITY)
	  {UCSRC&= ~(1<<UPM0);
	  UCSRC|= (1<<UPM1);}
	  else if (UART_PARITY == ODD_PARITY)
      {UCSRC|= (1<<UPM0);
       UCSRC|= (1<<UPM1);}
  
}

void Serial_attachInterrupt(unsigned char Case,void (*Local_ISR)(void))
{
	if(Case == RX_INTERRUPT)
	{
	UCSRB|=1<<RXCIE;
	RXC_ISR=Local_ISR;
	}
	else if(Case == TX_INTERRUPT )
	{UCSRB|=1<<UDRIE;
	TXC_ISR=Local_ISR;
	}
	sei();
}
void Serial_flush(void){
	unsigned char dummy;
	while (Serial_available()>0)
	dummy=UDR;
}
// function to receive data
unsigned char Serial_read (void)
{
	return UDR;                                   // return 8-bit data
}

void Serial_readString(unsigned char *x, unsigned char size)
{
	strcpy(x,"");
	unsigned char i = 0;
	
	x[i]=Serial_read();
	i++;
	while (i < size - 1) {              // check space is available (including additional null char at end)
		unsigned char c;
		while ( !(UCSRA & (1<<RXC)) );  // wait for another char - WARNING this will wait forever if nothing is received
		c = UDR;
		if (c == '\0') break;           // break on NULL character
		x[i] = c;                       // write into the supplied buffer
		i++;
	}
	x[i] = '\0';                           // ensure string is null terminated

}

void Serial_readStringUntil(unsigned char *x, unsigned char c)
{
	strcpy(x,"");
	unsigned char i = 0;
	unsigned char a;
	x[i]=Serial_read();
	i++;
	
	if(x[i]!=c)
	{
		while (1) 
	{              	
		while ( !(UCSRA & (1<<RXC)) );  // wait for another char - WARNING this will wait forever if nothing is received
		a = UDR;
		x[i] = a;                       // write into the supplied buffer
		i++;
		if(a == c)
		{
		break;
		}
	}
	
	}
	x[i] = '\0';                           // ensure string is null terminated
	
	
}

ISR(USART_RXC_vect){
RXC_ISR();		
}
ISR(USART_UDRE_vect){
TXC_ISR();	
}