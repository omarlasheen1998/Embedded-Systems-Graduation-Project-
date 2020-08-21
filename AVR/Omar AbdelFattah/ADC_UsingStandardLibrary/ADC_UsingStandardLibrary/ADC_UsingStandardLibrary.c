/*
 * ADC_UsingStandardLibrary.c
 *
 * Created: 17/08/2020 07:26:50 ص
 *  Author: omar
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void)
{
	int result;
	DDRA&=~(1<<PINA0);
	DDRD=0xFF;
	ADCSRA|= 1<<ADEN; // enable ADC in register ADC control & status register A
	ADCSRA|=1<<ADPS2; //enable a prescaler in internal/external clock , datasheet says best freq for 8-bit is between 50Khz and 200Khz ,1M/50K=20 , use ps=16
	ADMUX&=~(0x0F);	//use ADC0 then no change
	ADMUX|=1<<REFS0; // AVCC with external capacitor at AREF pin
	ADMUX|=1<<ADLAR; // choose the higher 8-bit to be in data register high  (from 2 to 9 ), this is an approximation to ignore first 2-bits
    while(1)
    {
		
		
		ADMUX&=~(0x0F);	//use ADC0 then no change
		ADCSRA |= (1<<ADSC); //start coversion 
		while (ADCSRA&(1<<ADIF)==0); //wait until interrupt flag be set ( conversion has end) 
		_delay_us(10);
		result=ADCH; 
		PORTD=result;
	   
    }
return 1;
}



//********