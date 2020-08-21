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
#include "I2C.h"

// LCD I2C Settings 
#define LCD_I2C_ADDR 0x20

// LCD 4-Bit Settings 
#define LCD_PRT PORTA
#define LCD_DDR DDRA
#define LCD_PIN PINA

// LCD 8-Bit Settings
#define LCD_DPRT PORTC
#define LCD_DDDR DDRC
#define LCD_DPIN PINC
#define LCD_CPRT PORTB
#define LCD_CDDR DDRB
#define LCD_CPIN PINB

// Common Settings
#define LCD_RS 0
#define LCD_RW 1
#define LCD_EN 2

// Configurations
#define LCD_8_BIT 0
#define LCD_4_BIT 1
#define LCD_I2C 2




class LCD {
	public:
	LCD(uint8_t config);
	void Init(void);
	void printString(char *str);
	void gotoXY(uint8_t x, uint8_t y);
	void command(uint8_t cmd);
	void printData(uint8_t data);
	void clear(void);
	
	private:
	uint8_t configType = 0;
	uint8_t I2C_PRT = 0x00;


};






#endif /* LCD_H_ */