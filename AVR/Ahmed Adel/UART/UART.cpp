#include "UART.h"
char Serial::stringBuffer[64];


void Serial::setBaudRate(uint32_t baudrate){
	uint16_t reg = (F_CPU/(16 * baudrate)) - 1;
	UBRRL = reg & 0x00FF;
	UCSRC &= ~(1 << URSEL);
	UBRRH = (reg >> 8) & 0x00FF;
}

void Serial::begin(uint32_t baudrate){
	setBaudRate(baudrate);
	UCSRB |= (1 << TXEN) | (1 << RXEN);
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1) ;
	UCSRB &= ~(1 << UCSZ2);

}

void Serial::print(char *s){
	uint16_t stringIndex = 0;
	while(s[stringIndex] != '\0'){
		while(! (UCSRA & (1 << UDRE)));
		UDR = s[stringIndex];
		stringIndex++;
	}
}

void Serial::print(uint8_t data){
	while(! (UCSRA & (1 << UDRE)));
	UDR = data;
}



uint8_t Serial::read(void){
	while(!(UCSRA & (1 << RXC)));
	return UDR;
}


char* Serial::readString(void){
	char readchar = 0;
	stringBuffer[0] = '\0';

	while ((readchar = Serial::read()) != 13)
	{
		strncat(stringBuffer, &readchar, 1);
	}

	return stringBuffer;
}


char* Serial::readStringUntill(char terminator){
	char readchar = 0;
	stringBuffer[0] = '\0';

	while ((readchar = Serial::read()) != terminator)
	{
		strncat(stringBuffer, &readchar, 1);
	}

	return stringBuffer;
}

int Serial::parseInt(void){
	char* str = readString();
	return atoi(str);
}


float Serial::parseFloat(void){
	char* str = readString();
	return atof(str);
}
