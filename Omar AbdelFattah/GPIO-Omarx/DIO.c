#include "mytypedef.h"
#include "drivers.h"

#include <avr/io.h>


void GetPinVal(U8 PORT,U8 PINNUMB,U8*container)
{
	*container=((DIO_PINB>>PINNUMB)&(1<<0));
}
//void SetPinDir ()

void DIO_SetPinDir (U8 port,U8 pinnum,U8 state)
{
	switch (port)
	{
	case 'A':
		if (state == 1)
		{
			DIO_DDRA|=(1<<pinnum);
		}
		else
		{
			DIO_DDRA&=~(1<<pinnum);
		}
		break;
	case 'B':
		if (state == 1)
		{
			DIO_DDRB|=(1<<pinnum);
		}
		else
		{
			DIO_DDRB&=~(1<<pinnum);
		}
		break;
	case 'C':
		if (state == 1)
		{
			DIO_DDRC|=(1<<pinnum);
		}
		else
		{
			DIO_DDRC&=~(1<<pinnum);
		}
		break;
	case 'D':
		if (state == 1)
		{
			DIO_DDRD|=(1<<pinnum);
		}
		else
		{
			DIO_DDRD&=~(1<<pinnum);
		}
		break;
	}
}
void DIO_SetPortDir(U8 Port,U8 state )
{
	switch (Port)
	{
	case 'A':
		if (state == 1)
		{
			DIO_DDRA=0xFF;
		}
		else
		{
			DIO_DDRA=0x00;
		}
		break;
	case 'B':
		if (state == 1)
		{
			DIO_DDRB=0xFF;
		}
		else
		{
			DIO_DDRB=0x00;
		}
		break;
	case 'C':
		if (state == 1)
		{
			DIO_DDRC=0xFF;
		}
		else
		{
			DIO_DDRC=0x00;
		}
		break;
	case 'D':
		if (state == 1)
		{
			DIO_DDRD=0xFF;
		}
		else
		{
			DIO_DDRD=0x00;
		}
		break;
	}
}
void DIO_SetPinValue(U8 port,U8 pinnum,U8 state)
{
	switch (port)
		{
		case 'A':
			if (state == 1)
			{
				DIO_PORTA|=(1<<pinnum);
			}
			else
			{
				DIO_PORTA&=~(1<<pinnum);
			}
			break;
		case 'B':
			if (state == 1)
			{
				DIO_PORTB|=(1<<pinnum);
			}
			else
			{
				DIO_PORTB&=~(1<<pinnum);
			}
			break;
		case 'C':
			if (state == 1)
			{
				DIO_PORTC|=(1<<pinnum);
			}
			else
			{
				DIO_PORTC&=~(1<<pinnum);
			}
			break;
		case 'D':
			if (state == 1)
			{
				DIO_PORTD|=(1<<pinnum);
			}
			else
			{
				DIO_PORTD&=~(1<<pinnum);
			}
			break;
	}
}

void DIO_SetPortValue(U8 port,U8 state)
{
	switch (port)
	{
	case 'A':
		if (state == 1)
		{
			DIO_PORTA=0xFF;
		}
		else if (state == 0)
		{
			DIO_PORTA=0x00;
		}
		else
		{
			DIO_PORTA=state;
		}
		break;
	case 'B':
		if (state == 1)
		{
				DIO_PORTB=0xFF;
		}
		else if (state == 0)
		{
			DIO_PORTB=0x00;
		}
		else
		{
			DIO_PORTB=state;
		}
		break;
	case 'C':
		if (state == 1)
		{
			DIO_PORTC=0xFF;
		}
		else
		{
			DIO_PORTC=0x00;
		}
		break;
	case 'D':
		if (state == 1)
		{
			DIO_PORTD=0xFF;
		}
		else
		{
			DIO_PORTD=0x00;
		}
		break;
	}
}


