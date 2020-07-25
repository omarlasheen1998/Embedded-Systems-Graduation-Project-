/*
 * CFile1.c
 *
 * Created: 23-Jul-20 3:52:37 AM
 *  Author: Lasheen
 */ 

#define F_CPU 1000000UL

#include "SPI.h"
#include <avr/io.h>
#include <util/delay.h>

void SPI_MasterInit()								/* SPI Initialize function */
{
	DDRB |= (1<<MOSI)|(1<<SCK);		/* Make MOSI, SCK, 0th pin direction as output pins */
	DDRB &= ~(1<<MISO);						/* Make MISO pin as input pin */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1)|(1<<SPR0);	/* Enable SPI, Enable in master mode, with Fosc/24 SCK frequency */
	SPSR &= ~(1<<SPI2X);					/* Disable speed doubler */
}

void SPI_SlaveInit()									/* SPI Initialize function */
{
	DDRB &= ~((1<<MOSI)|(1<<SCK)|(1<<SS));		/* Make MOSI, SCK, SS pin direction as input pins */
	DDRB |= (1<<MISO);							/* Make MISO pin as output pin */
	SPCR = (1<<SPE);					/* Enable SPI in slave mode */
}

void SPI_Write(unsigned char data)					/* SPI write data function */
{
	char flush_buffer;
	SPDR = data;							/* Write data to SPI data register */
	while(!(SPSR & (1<<SPIF)));				/* Wait till transmission complete */
	flush_buffer = SPDR;					/* Flush received data */
	/* Note: SPIF flag is cleared by first reading SPSR (with SPIF set) and then accessing SPDR hence flush buffer used here to access SPDR after SPSR read */
}

unsigned char SPI_Read()								/* SPI read data function */
{
	SPDR = 0xFF;
	while(!(SPSR & (1<<SPIF)));				/* Wait till reception complete */
	return(SPDR);							/* return received data */
}
