/*
 * LCD.h
 *
 * Created: 7/9/2020 7:52:08 AM
 *  Author: ahmed
 */ 


#ifndef LCD_H_
#define LCD_H_


#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "GPIO.h"

#define AUTO(var, expr) decltype(expr) var = (expr)

#define LCD_DPRT PORTC
#define LCD_DDDR DDRC
#define LCD_DPIN PINC
#define LCD_CPRT PORTB
#define LCD_CDDR DDRB
#define LCD_CPIN PINB
#define LCD_RS 0
#define LCD_RW 1
#define LCD_EN 2


class LCD {
	public:
	void Init(void);
	void printString(char *str);
	void gotoXY(uint8_t x, uint8_t y);
	void command(uint8_t cmd);
	void printData(uint8_t data);
	void clear(void);
	
	private:
	
	


};






#endif /* LCD_H_ */