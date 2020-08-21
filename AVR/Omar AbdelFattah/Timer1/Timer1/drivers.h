/*
 * drivers.h
 *
 * Created: 18/07/2020 06:25:02 ã
 *  Author: omar
 */


#include "mytypedef.h"


#ifndef DRIVERS_H_
#define DRIVERS_H_

void GetPinVal(U8 PORT,U8 PINNUMB,U8*container);
void DIO_SetPinDir (U8 port,U8 pinnum,U8 state);
void DIO_SetPortDir(U8 Port,U8 state );
void DIO_SetPinValue(U8 port,U8 pinnum,U8 state);
void DIO_SetPortValue(U8 port,U8 state);




#define DIO_PINA (*((U8*)0x39))
#define DIO_DDRA (*((U8*)0x3A))
#define DIO_PORTA (*((U8*)0x3B))

#define DIO_PINB (*((U8*)0x36))
#define DIO_DDRB (*((U8*)0x37))
#define DIO_PORTB (*((U8*)0x38))

#define DIO_PINC (*((U8*)0x33))
#define DIO_DDRC (*((U8*)0x34))
#define DIO_PORTC (*((U8*)0x35))

#define DIO_PIND (*((U8*)0x30))
#define DIO_DDRD (*((U8*)0x31))
#define DIO_PORTD (*((U8*)0x32))

#define DIO_HIGH 1u
#define DIO_LOW 0u

#define DIO_OUTPUT 1u
#define DIO_INPUT 0u



#endif /* DRIVERS_H_ */
