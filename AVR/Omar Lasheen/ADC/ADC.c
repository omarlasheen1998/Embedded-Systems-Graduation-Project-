/*
 * CFile1.c
 *
 * Created: 5/3/2020 3:24:43 AM
 *  Author: Lasheen
 */ 
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "ADC.h"
#include "Gpio.h"
void (*ISR_ADC)(void) = '\0';

void analogReference(uint8_t ref)
{
	if( ref == DEFAULT)
	ADMUX&=~((1<<REFS0)|(1<<REFS1));
	else if(ref==EXTERNAL)
	{
	ADMUX&=~((1<<REFS0)|(1<<REFS1));
	ADMUX|=1<<REFS0;
	}
	else if(ref==INTERNAL2V56)
	ADMUX|=((1<<REFS0)|(1<<REFS1));
}

uint16_t analogRead(uint8_t channel){
	
	// select the corresponding channel 0~7
	// ANDing with ’7? will always keep the value
	// of ‘ch’ between 0 and 7
	channel &= 0b00000111;  // AND operation with 7
	ADMUX = (ADMUX & 0xF8)|channel; // clears the bottom 3 bits before ORing
	
	// start single conversion
	// write ’1? to ADSC
	ADCSRA |= (1<<ADSC);
	
	// wait for conversion to complete
	// ADSC becomes ’0? again
	// till then, run loop continuously
	while(ADCSRA & (1<<ADSC));
	
	return (ADC);
	
}

float analogReadVolts(uint8_t channel,float voltage)
{
	
	uint16_t result;
	if(ADCSRA &(1<<ADIE))
	{
	result = ADC_ReturnValue();
	return((1.0*result/1023)*voltage);
	}
	else
	{
	result = analogRead(channel);
	return((1.0*result/1023)*voltage);
	}
}

void ADC_Init(void){
	ADCSRA|=1<<ADEN;
	setADC_Prescaler(16);
	analogReference(DEFAULT);
	ADMUX&=1<<ADLAR;
}

void ADC_attachInterrupt(void (*ADC_Finish)(void))
{
	ISR_ADC = ADC_Finish;
	ADCSRA |= (1<<ADIE);
	ADCSRA&=~(1<<ADIF);
	sei();
	
}

void setADC_Prescaler(uint8_t x){
	
	if(x == 2) //001
	{
		
	ADCSRA&=~(1<<ADPS0|1<<ADPS1|1<<ADPS2);	
	ADCSRA|=1<<ADPS0;
	
	}
	else if(x == 4)//010
	{
		
		ADCSRA&=~(1<<ADPS0|1<<ADPS1|1<<ADPS2);
		ADCSRA|=(1<<ADPS1);
		
	}
	else if(x == 8)//011
	{
		
		ADCSRA&=~(1<<ADPS0|1<<ADPS1|1<<ADPS2);
		ADCSRA|=(1<<ADPS1|1<<ADPS0);
	
	}
	else if(x == 16)//100
	{
		
		ADCSRA&=~(1<<ADPS0|1<<ADPS1|1<<ADPS2);
		ADCSRA|=(1<<ADPS2);
	
	}
	else if(x == 32)//101
	{
	
	ADCSRA&=~(1<<ADPS0|1<<ADPS1|1<<ADPS2);
	ADCSRA|=(1<<ADPS0|1<<ADPS2);
	
	}	
	else if(x == 64) //110
	{
	
	ADCSRA&=~(1<<ADPS0|1<<ADPS1|1<<ADPS2);
	ADCSRA|=(1<<ADPS1|1<<ADPS2);
	
	}
	else if(x == 128) //111
	ADCSRA|=1<<ADPS0|1<<ADPS1|1<<ADPS2;
	
	
}
uint16_t ADC_ReturnValue(void){
 return ADCW;
}

void ADC_startConversion(uint8_t channel)
{
if(channel>=0 && channel<=31)
ADMUX = (ADMUX & 0xE0)|channel; // clears the bottom 5 bits before ORing

// start single conversion
// write ’1? to ADSC
ADCSRA |= (1<<ADSC);

}

uint8_t ADC_ReturnADCL(void){
	return ADCL;
}

uint8_t ADC_ReturnADCH(void){
	return ADCH;
}

int16_t differentialRead(uint8_t channel) //input numbers from 8 to 31 to get difference between Reading of 2 pins according to data sheet 
{
	if(channel>=8 && channel<=31)
	ADMUX = (ADMUX & 0xE0)|channel; // clears the bottom 5 bits before ORing
	
	// start single conversion
	// write ’1? to ADSC
	ADCSRA |= (1<<ADSC);
	
	// wait for conversion to complete
	// ADSC becomes ’0? again
	// till then, run loop continuously
	while(ADCSRA & (1<<ADSC));
	
	return (ADC);
	
}

ISR(ADC_vect)
{
	ISR_ADC();

}
