/*
 * CFile1.c
 *
 * Created: 4/30/2020 3:59:21 AM
 *  Author: Lasheen
 */ 
#include <avr/io.h>
#include "Gpio.h"
#include <avr/interrupt.h>
#include <stdbool.h>

void (*ISR0)(void) = '\0';
void (*ISR1)(void) = '\0';
void (*ISR2)(void) = '\0';


void pinMode(uint8_t pinNo,uint8_t State){
	
	if(pinNo>=0&&pinNo<=7)
    {
	if(State == OUTPUT)
	DDRA|=1<<(pinNo%10);
	else if(State == INPUT)
	DDRA&=~(1<<(pinNo%10));
	else if(State == INPUT_PULLUP)
	{DDRA&=~(1<<(pinNo%10));
	SFIOR&=~(1<<PUD);
	PORTA|=(1<<(pinNo%10));
	}
	
	}
	
	else if(pinNo>=10&&pinNo<=17)
	{
		if(State == OUTPUT)
		DDRB|=1<<(pinNo%10);
		else if(State == INPUT)
		DDRB&=~(1<<(pinNo%10));
		else if(State == INPUT_PULLUP)
		{DDRB&=~(1<<(pinNo%10));
		 SFIOR&=~(1<<PUD);
		 PORTB|=(1<<(pinNo%10));
		}
	
	}
	else if(pinNo>=20&&pinNo<=27)
	{
		if(State == OUTPUT)
		DDRC|=1<<(pinNo%10);
		else if(State == INPUT)
		DDRC&=~(1<<(pinNo%10));
		else if(State == INPUT_PULLUP)
		{DDRC&=~(1<<(pinNo%10));
		 SFIOR&=~(1<<PUD);
		 PORTC|=(1<<(pinNo%10));
		}
	
	}
	else if(pinNo>=30&&pinNo<=37)
	{
		if(State == OUTPUT)
		DDRD|=1<<(pinNo%10);
		else if(State == INPUT)
		DDRD&=~(1<<(pinNo%10));
		else if(State == INPUT_PULLUP)
		{DDRD&=~(1<<(pinNo%10));
		 SFIOR&=~(1<<PUD);
		 PORTD|=(1<<(pinNo%10));
		}
	}
		
}

void digitalWrite(uint8_t pinNo,uint8_t Status)
{
	
	if(pinNo>=0&&pinNo<=7)
	{
		if(Status%10 == HIGH%10)
		PORTA|=1<<(pinNo%10);
		else if(Status%10 == LOW%10)
		PORTA&=~(1<<(pinNo%10));
	}
	else if(pinNo>=10&&pinNo<=17)
	{
		if(Status%10 == HIGH%10)
		PORTB|=1<<(pinNo%10);
		else if(Status%10 == LOW%10)
		PORTB&=~(1<<(pinNo%10));
	}
	else if(pinNo>=20&&pinNo<=27)
	{
		if(Status%10 == HIGH%10)
		PORTC|=1<<(pinNo%10);
		else if(Status%10 == LOW%10)
		PORTC&=~(1<<(pinNo%10));
	}
	else if(pinNo>=30 && pinNo<=37)
	{
		if(Status%10 == HIGH%10)
		PORTD|=1<<(pinNo%10);
		else if(Status%10 == LOW%10)
		PORTD&=~(1<<(pinNo%10));
	}
	
}
bool digitalRead(uint8_t pinNo){
	
	if(pinNo>=0&&pinNo<=7)
	{
	return (bool)(((PINA)>>(pinNo%10)) & 0x01);
	}
	else if(pinNo>=10&&pinNo<=17)
	{
		return (bool)(((PINB)>>(pinNo%10)) & 0x01);
	}
	else if(pinNo>=20&&pinNo<=27)
	{
		return (bool)(((PINC)>>(pinNo%10)) & 0x01);
	}
	else if(pinNo>=30&&pinNo<=37)
	{
		return (bool)(((PIND)>>(pinNo%10)) & 0x01);
	}
}

void attachInterrupt(uint8_t pinNo,uint8_t state,void (*Local_ISR)(void))
{
	
	
	if(pinNo == D2)
	{
		if(state == INT_LOW)
		MCUCR&=~((1<<ISC00)|(1<<ISC01));
		else if(state == INT_CHANGE)
		{
			MCUCR|=(1<<ISC00);
			MCUCR&=~(1<<ISC01);
		}
		else if(state == INT_FALLING)
		{
		MCUCR|=(1<<ISC01);
		MCUCR&=~(1<<ISC00);
		}
		else if(state == INT_RISING)
		MCUCR|=((1<<ISC00)|(1<<ISC01));
		
		GICR|=1<<INT0;
		ISR0 = Local_ISR;
     	
	}
	else if(pinNo == D3)
	{
		if(state == INT_LOW)
		MCUCR&=~((1<<ISC10)|(1<<ISC11));
		else if(state == INT_CHANGE)
		{
			MCUCR|=(1<<ISC10);
			MCUCR&=~(1<<ISC11);
		}
		else if(state == INT_FALLING)
		{
			MCUCR|=(1<<ISC11);
			MCUCR&=~(1<<ISC10);
		}
		else if(state == INT_RISING)
		MCUCR|=((1<<ISC10)|(1<<ISC11));
		
		
		GICR|=1<<INT1;
		ISR1 = Local_ISR;
		
	}
	else if(pinNo == B2)
	{
        if(state == INT_FALLING)
          MCUSR&=~(1<<ISC2);
        else if(state == INT_RISING)
        MCUSR|=1<<ISC2;
		
		GICR|=1<<INT2;
		ISR2 = Local_ISR;
	
	}
	sei();
}
void noInterrupts(void)
{

cli();

}

void Interrupts(void){
	
	sei();
}


ISR(INT0_vect)
{
	ISR0();
}

ISR(INT1_vect)
{
	ISR1();
}

ISR(INT2_vect)
{
	ISR2();
}

