/*
 * GPIO_DRIVERS.c
 *
 * Created: 18/07/2020 06:21:02 ã
 *  Author: omar
 */

#include <util/delay.h>
#include "drivers.h"
#include "mytypedef.h"


int main(void)
{
	DIO_SetPortDir('A',DIO_OUTPUT);
    while(1)
    {
DIO_SetPinValue('A',0,DIO_HIGH);
_delay_ms(200);
DIO_SetPinValue('A',1,DIO_HIGH);
_delay_ms(200);
DIO_SetPinValue('A',2,DIO_HIGH);
_delay_ms(200);
DIO_SetPinValue('A',3,DIO_HIGH);
_delay_ms(200);
DIO_SetPinValue('A',4,DIO_HIGH);
_delay_ms(200);
DIO_SetPinValue('A',5,DIO_HIGH);
_delay_ms(200);
DIO_SetPinValue('A',6,DIO_HIGH);
_delay_ms(200);
DIO_SetPinValue('A',7,DIO_HIGH);
_delay_ms(200);

DIO_SetPortValue('A',DIO_LOW);
_delay_ms(200);


    }
	return 1;
}
