/*
 * DIO_register.h
 *  Created on: Aug 2, 2020
 *      Author: Hosny
 *
 * This code is for easing accessing and writing in registers
 * instead of typing the address every time you want to access the register
 * its easier to type the name directly
 */

#ifndef MY_REPO_MCAL_DIO_DIO_REGISTERS_H_
#define MY_REPO_MCAL_DIO_DIO_REGISTERS_H_

/* volatile .. for the repeat value checking .. because it depends on hardware connection
 * unsigned char .. for the 8 bits
 * */


//PORTA
#define DDRA_register (*(volatile unsigned char *)0x3A)
#define PORTA_register (*(volatile unsigned char *)0x3B)
#define PINA_register (*(volatile unsigned char *)0x39)
/******/

//PORTB
#define DDRB_register (*(volatile unsigned char *)0x37)
#define PORTB_register (*(volatile unsigned char *)0x38)
#define PINB_register (*(volatile unsigned char *)0x36)
/******/

//PORTC
#define DDRC_register (*(volatile unsigned char *)0x34)
#define PORTC_register (*(volatile unsigned char *)0x35)
#define PINC_register (*(volatile unsigned char *)0x33)
/******/

//PORTD
#define DDRD_register (*(volatile unsigned char *)0x31)
#define PORTD_register (*(volatile unsigned char *)0x32)
#define PIND_register (*(volatile unsigned char *)0x30)
/******/


#endif /* MY_REPO_MCAL_DIO_DIO_REGISTERS_H_ */
