/*
 * Timer1.c
 *
 * Created: 18/08/2020 09:11:09 ص
 *  Author: omar
 */ 

//Timer/Counter1 Control Register B TCCR1B
// timer 1 is 16-bit while timer 0 is 8-bit 
// 1Mhz >> 16Bit (65535 : 34an a2dr awsl l sania kamla fe tcnt1 minimum prescaler is 1000000/65535 = 16 ) ther is 8 and 64 , ana 75tar 8 kda kda 3awz 1/5 sania  
//1Mhz//8 = 125000 >> every 1 second in TCN1 , 200 ms = 125000/5= 25000 ,
//data stored in TCNT1 h and l , can be accessed in one line TCNT1
//************
// this version of code uses interrupts  
//OCR1A TIMSK sei ISR

#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "drivers.h"
int LEDNUMBER [2]={3,0};
int main(void)
{
	sei();
	DIO_DDRA=0xFF;
	DIO_DDRD=0xFF;
	DIO_PORTA=0x00;
	DIO_PORTD=0x00;
	TCCR1B|=   1<<CS11 | 1<<CS10 | 1<<WGM12 ; //WGM10=0 , WGM11=0, WGM12=0 this mode is clear timer on compare match (ctc) 
	TIMSK |= 1<< OCIE1A; // compare match interrupt enabled 
	OCR1A = 3125;
	
	
    while(1)
    {
	}
			  
}

ISR(TIMER1_COMPA_vect){
	DIO_PORTD= 1<<LEDNUMBER[0];
	LEDNUMBER[0]++;
	if (LEDNUMBER[0] > 7){
		DIO_PORTA = 1 <<LEDNUMBER[1];
		LEDNUMBER[0]=3;
		LEDNUMBER[1]++;
		if (LEDNUMBER[1] > 4) LEDNUMBER[1]=0;
	}
}
