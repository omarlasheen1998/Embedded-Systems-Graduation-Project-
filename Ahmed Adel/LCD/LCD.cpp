/*
 * LCD.cpp
 *
 * Created: 7/9/2020 7:51:58 AM
 *  Author: ahmed
 */ 

#include "LCD.h"

void LCD::command(uint8_t cmd){
	LCD_DPRT = cmd;
	LCD_CPRT &= ~(1 << LCD_RS);
	LCD_CPRT &= ~(1 << LCD_RW);
	LCD_CPRT |= (1 << LCD_EN);
	
	_delay_us(1);
	LCD_CPRT &= ~(1 << LCD_EN);
	_delay_us(100);
	
}


void LCD::Init(){
	LCD_DDDR = 0xFF;
	LCD_CDDR = 0xFF;
	
	LCD_CPRT &= ~(1 << LCD_EN);
	
	_delay_us(2000);
	command(0x38);
	command(0x0E);
	command(0x01);
	
	_delay_us(2000);
	command(0x06);
	
	
}


void LCD::printData(uint8_t data){
	LCD_DPRT = data;
	LCD_CPRT |= (1 << LCD_RS);
	LCD_CPRT &= ~(1 << LCD_RW);
	LCD_CPRT |= (1 << LCD_EN);
	
	_delay_us(1);
	LCD_CPRT &= ~(1 << LCD_EN);
	_delay_us(100);
	
}

void LCD::clear(){
	command(0x01);
	_delay_us(100);
	command(0x02);
	_delay_us(100);
	command(0x80);
	_delay_us(100);
}


void LCD::printString(char *str){
	uint8_t index = 0;
	
	while (str[index] != '\0')
	{
		printData(str[index]);
		index++;
	}
}


void LCD::gotoXY(uint8_t x, uint8_t y){
	uint8_t firstCharADR[] = {0x80 , 0xc0, 0x94, 0xD4};
	command(firstCharADR[y- 1] + x - 1);
	_delay_us(100);
}