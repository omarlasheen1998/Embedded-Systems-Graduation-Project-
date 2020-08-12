/*
 * Interrupt.c
 *
 *  Created on: Aug 12, 2020
 *      Author: Hosny
 */


#define F_CPU 1000000UL  //CPU speed according to the crystal
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void)
{
DDRA |= (1 << PA0);  //connecting led to PINA0
DDRB |= (1 << PB0) | (1 << PB1);  //connecting led to PINB0 and PINB1

DDRD &= ~((1 << PD2)|(1 << PD3));  //setting interrupt pins INT0 and INT1 as input
PORTD |= (1 << PD2)|(1 << PD3);    //Pull up


MCUCR |= (1 << ISC01) | (1 << ISC11);  //Interrupt at falling edge for both INT0 and INT1  (Interrupt Sensing)
GICR |= (1 << INT0) | (1 << INT1);     //Enabling the pins INT0 and INT1 (General Interrupt Control Register)


Sei();  //sets the bit the global interrupt flag in SREG and switches interrupts on
//Cli();  //clears the global interrupt flag in SREG so prevent any form of interrupt occurring



while(1)  //The running code .. blinking led on PINA0 or whatever you need
{
PORTA ^= (1 << PA0);
_delay_ms(100);
}

return 0;
}



ISR(INT0_vect)  //Interrupt 1
{
PORTB ^= (1 << PB0);
//Or any
}


ISR(INT1_vect)  //Interrupt 2
{
PORTB ^= (1 << PB1);
}



