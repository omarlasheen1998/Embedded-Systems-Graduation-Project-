/*
 * GPIO_DRIVERS.c
 *
 * Created: 18/07/2020 06:21:02 ã
 *  Author: omar
 */
#include <avr/io.h>
#include <util/delay.h>
#include "drivers.h"


int main(void)
{
	typedef char U8;
	DIO_DDRA=0xFF;
	PORTA=0x00;
    while(1)
    {
		DIO_PORTA=0x01;
		_delay_ms(500);
		DIO_PORTA=0x03;
		_delay_ms(500);
		DIO_PORTA=0x07;
		_delay_ms(500);
		DIO_PORTA=0xF;
		_delay_ms(500);

    }
	return 1;
}
