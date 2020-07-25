/*
 * drivers.h
 *
 * Created: 18/07/2020 06:25:02 ã
 *  Author: omar
 */





#ifndef DRIVERS_H_
#define DRIVERS_H_

/*void setpinIO (int pinnumber,int* portname,int IN_OUT);
void setpinval (int pinnumber,int* portname,int HIGH_LOW);
void getpinval (int pinnumber,int* portname,int HIGH_LOW);*/

#define DIO_PINA (*((U8*)0x39))
#define DIO_DDRA (*((U8*)0x3A))
#define DIO_PORTA (*((U8*)0x3B))

#define DIO_PINB (*((U8*)0x36))
#define DIO_DDRB (*((U8*)0x37))
#define DIO_PORTB (*((U8*))0x38))

#define DIO_PINC (*((U8*)0x33))
#define DIO_DDRC (*((U8*)0x34))
#define DIO_PORTC (*((U8*)0x35))

#define DIO_PIND (*((U8*)0x30))
#define DIO_DDRD (*((U8*)0x31))
#define DIO_PORTD (*((U8*)0x32))





#endif /* DRIVERS_H_ */
