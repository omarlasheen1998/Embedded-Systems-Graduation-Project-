/*
 * UART.h
 *
 *  Created on: Aug 7, 2020
 *      Author: ahmed
 */

#ifndef UART_H_
#define UART_H_

#include "avr/io.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

class Serial{

	public:
	static void begin(uint32_t baudrate);
	static void print(uint8_t data);
	static void print(char *s);
	static void println(char *s);
	static uint8_t read(void);
	static char *readString(void);
	static char *readStringUntill(char terminator);
	static int parseInt(void);
	static float parseFloat(void);



	private:
	static void setBaudRate(uint32_t baudrate);
	static char stringBuffer[64];


	};



#endif /* UART_H_ */
