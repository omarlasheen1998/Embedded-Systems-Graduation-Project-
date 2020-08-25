/*
 * UART.c
 *
 * Created: 22/08/2020 06:55:36 ص
 *  Author: omar
 */

#include <avr/io.h>
#include <util/delay.h>
void uart_init (void);
void debouncing (int* pressed,int* released_level,int* pressed_level,void (*f)(int),int data);
void uart_transmit(int data);
char uart_recieve();
int main(void)
{
	DDRB&=~(1<<PINB1);
	PORTB|=1<<PINB1;
	DDRB|=1<<PINB2;
	uart_init();
	int data=0b00001111;
	int pressed=0,rel_level=0,pres_level=0;
	char recieved;
    while(1)
    {
	 
	  debouncing(&pressed,&rel_level,&pres_level,uart_transmit,data);
	  //recieved=uart_recieve();
	}
}


