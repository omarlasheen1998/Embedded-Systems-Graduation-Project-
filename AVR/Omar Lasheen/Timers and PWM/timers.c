/*
 * CFile1.c
 *
 * Created: 8/18/2020 6:13:49 PM
 *  Author: osama
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Gpio.h"
#include "timers.h"

long long milliseconds=0;
long timing=0;
volatile long elapsed_time=0;
unsigned char repetitions=0;
volatile unsigned char counts=0;

void (*ISR_T2)(void)='\0';

void setUpPWM(char pinno) //Fast PWM Mode 
{
	
	if(pinno == B3) //timer0
	{
		pinMode(B3,OUTPUT);
		TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS00);
	}
	
	else if(pinno == D7) //timer2
	{
		pinMode(D7,OUTPUT);
		TCCR2 = (1<<WGM20) | (1<<WGM21) | (1<<COM21) | (1<<CS20);
	}
	
	else if(pinno == D4) //timer1B
	{
		pinMode(D4,OUTPUT);
		TCCR1A  |= ((1<<WGM11) | (1<<COM1B1));
		TCCR1B = (1<<WGM12) | (1<<WGM13) |  (1<<CS10);
		ICR1=255; 
	}
	else if(pinno == D5) //timer1A
	{
		pinMode(D5,OUTPUT);
		TCCR1A  |= (1<<WGM11) | (1<<COM1A1);
		TCCR1B = (1<<WGM12) | (1<<WGM13) |  (1<<CS10);
		ICR1=255;
	}
	
}


void pwmWrite(char pinno,unsigned char pinval)
{
	if(pinno == B3) //timer0
	{
		
	OCR0= pinval;
	}
	
	else if(pinno == D7) //timer2
	{
		OCR2= pinval;
	}
	
	else if(pinno == D4) //timer1B
	{
		OCR1B= pinval;
	}
	else if(pinno == D5) //timer1A
	{
	OCR1A= pinval;
	}
	
}


void WDT_ON(char prescaler) // prescaler from 0 to 7
{
	/* 
	0 --> 16.3 ms
	1 --> 32.5 ms
	2 --> 65 ms
	3 --> 0.13 s
	4 --> 0.26 s
	5 --> 0.52 s
	6 --> 1 s
	7 --> 2.1 s
	*/
	
	if( prescaler == 0)
	{
		WDTCR &= ~((1<<WDP2)|(1<<WDP1)|(1<<WDP0));
		WDTCR |= (1<<WDE);
	}
	else if( prescaler == 1)
	{
		WDTCR &= ~((1<<WDP2)|(1<<WDP1)|(1<<WDP0));
		WDTCR |= (1<<WDP0);
		WDTCR |= (1<<WDE);
	}
	else if( prescaler == 2)
	{
		WDTCR &= ~((1<<WDP2)|(1<<WDP1)|(1<<WDP0));
		WDTCR |= (1<<WDP1);
		WDTCR |= (1<<WDE);
	}
	else if( prescaler == 3)
	{
		WDTCR &= ~((1<<WDP2)|(1<<WDP1)|(1<<WDP0));
		WDTCR |= (1<<WDP1)|(1<<WDP0);
		WDTCR |= (1<<WDE);
	}
	else if( prescaler == 4)
	{
		WDTCR &= ~((1<<WDP2)|(1<<WDP1)|(1<<WDP0));
		WDTCR |= (1<<WDP2);
		WDTCR |= (1<<WDE);
	}
	else if( prescaler == 5)
	{
		WDTCR &= ~((1<<WDP2)|(1<<WDP1)|(1<<WDP0));
		WDTCR |= (1<<WDP2)|(1<<WDP0);
		WDTCR |= (1<<WDE);
	}
	else if( prescaler == 6)
	{
		WDTCR &= ~((1<<WDP2)|(1<<WDP1)|(1<<WDP0));
		WDTCR |= (1<<WDP2)|(1<<WDP1);
		WDTCR |= (1<<WDE);
	}
	else if( prescaler == 7)
	{
		WDTCR &= ~((1<<WDP2)|(1<<WDP1)|(1<<WDP0));
		WDTCR |= (1<<WDP2)|(1<<WDP1)|(1<<WDP0);
		WDTCR |= (1<<WDE);
	}
}

void WDT_OFF()
{
	/*
	This function use for disable the watchdog timer.
	*/
	WDTCR = (1<<WDTOE)|(1<<WDE);
	WDTCR = 0x00;
}

void setUpPeriodicTimer(long time,unsigned char no_of_times,void (*Local_ISR)(void)) //using timer2
{
	
	sei();
	TIMSK=(1<<OCIE2);  	/* Enable Timer2 CTC interrupts */
	TCNT2 = 0;  		/* Load TCNT0, count for 1 ms*/
	OCR2=115;
	timing = time;
	repetitions = no_of_times;
	ISR_T2=Local_ISR;  
	elapsed_time=0;
	counts=0;
	TCCR2 = (1<<CS21)|(1<<WGM21); /* Start timer0 with /8 prescaler*/
	
}
void Timer() // setup millis using timer0
{
	
		sei();
		TIMSK=(1<<TOIE0);  	/* Enable Timer0 overflow interrupts */
		TCNT0 = 0x89;  		/* Load TCNT0, count for 1 ms*/
		TCCR0 = (1<<CS01); /* Start timer0 with /8 prescaler*/
	
}
unsigned int measurePeriod() // return no. of timer counts in microseconds for the period
{
	
	unsigned int t;
	
	TCCR1A = 0;
	TIFR = (1<<ICF1);		/* clear input capture flag */
	TCCR1B = 0x41;			/* capture on rising edge , no prescaler*/ 

	while ((TIFR&(1<<ICF1)) == 0);  /* monitor for capture*/
	t = ICR1;			
	TIFR = (1<<ICF1);		/* clear capture flag */

	while ((TIFR&(1<<ICF1)) == 0);  /* monitor for next rising edge capture */

	t = ICR1 - t;  			/* period= recent capture- previous capture */
	return t; // no. of microseconds 

}
unsigned int measureFrequency(){
	
	
	unsigned int a,b,c,period_counts;
	unsigned long freq;
	
		TCCR1A = 0;
		TCNT1=0;
		TIFR = (1<<ICF1);  	/* Clear ICF (Input Capture flag) flag */

		TCCR1B = 0x41;  	/* Rising edge, no prescaler */
		while ((TIFR&(1<<ICF1)) == 0);
		a = ICR1;  		/* Take value of capture register */
		TIFR = (1<<ICF1);  	/* Clear ICF flag */
		
		TCCR1B = 0x01;  	/* Falling edge, no prescaler */
		while ((TIFR&(1<<ICF1)) == 0);
		b = ICR1;  		/* Take value of capture register */
		TIFR = (1<<ICF1);  	/* Clear ICF flag */
		
		TCCR1B = 0x41;  	/* Rising edge, no prescaler */
		while ((TIFR&(1<<ICF1)) == 0);
		c = ICR1;  		/* Take value of capture register */
		TIFR = (1<<ICF1);  	/* Clear ICF flag */

		TCCR1B = 0;  		/* Stop the timer */
		
		if(a<b && b<c)  	/* Check for valid condition, 
					to avoid timer overflow reading */
		{
			period_counts = c-a;
			
			freq= F_CPU / period_counts;/* Calculate frequency */

		}
		
		else
		{
			return 0;
		}
	return freq;
}

float measureDutyCycle()
{

	unsigned int a,b,c,high_counts,period_counts;
	float duty_cycle;
	
		TCCR1A = 0;
		TCNT1=0;
		TIFR = (1<<ICF1);  	/* Clear ICF (Input Capture flag) flag */

		TCCR1B = 0x41;  	/* Rising edge, no prescaler */
		while ((TIFR&(1<<ICF1)) == 0);
		a = ICR1;  		/* Take value of capture register */
		TIFR = (1<<ICF1);  	/* Clear ICF flag */
		
		TCCR1B = 0x01;  	/* Falling edge, no prescaler */
		while ((TIFR&(1<<ICF1)) == 0);
		b = ICR1;  		/* Take value of capture register */
		TIFR = (1<<ICF1);  	/* Clear ICF flag */
		
		TCCR1B = 0x41;  	/* Rising edge, no prescaler */
		while ((TIFR&(1<<ICF1)) == 0);
		c = ICR1;  		/* Take value of capture register */
		TIFR = (1<<ICF1);  	/* Clear ICF flag */

		TCCR1B = 0;  		/* Stop the timer */
		
		if(a<b && b<c)  	/* Check for valid condition, 
					to avoid timer overflow reading */
		{
			high_counts = b-a;
			period_counts = c-a;

						/* Calculate duty cycle */
            		duty_cycle =((float) high_counts /(float)period_counts)*100;				
		}
		
		else
		{
			return 0;
		}
	
	return duty_cycle;
	}


long long millis(){
	
return milliseconds;	//return elapsed time in millis
	} 

ISR(TIMER0_OVF_vect)
{

milliseconds++;
TCNT0 = 0x89;  		/* Load TCNT0, count for 1 ms*/
	
}

ISR(TIMER2_COMP_vect)
{  
	
    elapsed_time++;
	TCNT2 = 0;  		/* Load TCNT0, count for 1 ms*/
	if(elapsed_time >= timing)
	{ISR_T2();
	elapsed_time=0;
	counts++;
	}
	if(counts >= repetitions && repetitions!=PERIODIC)
	{
		noInterrupts();
		TCCR2=0;
	}
	
}