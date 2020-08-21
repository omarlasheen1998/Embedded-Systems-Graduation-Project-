/*
 * LCD.cpp
 *
 * Created: 7/9/2020 7:51:58 AM
 *  Author: ahmed
 */ 

#include "LCD.h"

LCD::LCD(uint8_t config){
	if (config >= 0 && config <= 2)
	{
		configType = config;
	}
}

void LCD::command(uint8_t cmd){
	if (configType == LCD_8_BIT)
	{
		LCD_DPRT = cmd;
		LCD_CPRT &= ~(1 << LCD_RS);
		LCD_CPRT &= ~(1 << LCD_RW);
		LCD_CPRT |= (1 << LCD_EN);
		
		_delay_us(1);
		LCD_CPRT &= ~(1 << LCD_EN);
		_delay_us(100);
	}
	else if (configType == LCD_4_BIT)
	{
		LCD_PRT = (LCD_PRT & 0x0F) | (cmd & 0xF0); 
		LCD_PRT &= ~(1 << LCD_RS);
		LCD_PRT &= ~(1 << LCD_RW);
		LCD_PRT |= (1 << LCD_EN);
		
		_delay_us(1);
		LCD_PRT &= ~(1 << LCD_EN);
		_delay_us(100);
		
		LCD_PRT = (LCD_PRT & 0x0F) | (cmd << 4); 
		LCD_PRT |= (1 << LCD_EN);
		_delay_us(1);
		LCD_PRT &= ~(1 << LCD_EN);
		_delay_us(100);
	}
	else if (configType == LCD_I2C)
	{
		I2C::beginTransmission(LCD_I2C_ADDR);
		
		I2C_PRT = (I2C_PRT & 0x0F) | (cmd & 0xF0);
		I2C::write(I2C_PRT);
		I2C_PRT &= ~(1 << LCD_RS);
		I2C::write(I2C_PRT);
		I2C_PRT &= ~(1 << LCD_RW);
		I2C::write(I2C_PRT);
		I2C_PRT |= (1 << LCD_EN);
		I2C::write(I2C_PRT);
		
		_delay_us(1);
		I2C_PRT &= ~(1 << LCD_EN);
		I2C::write(I2C_PRT);
		_delay_us(100);
		
		I2C_PRT = (I2C_PRT & 0x0F) | (cmd << 4);
		I2C::write(I2C_PRT);
		I2C_PRT |= (1 << LCD_EN);
		I2C::write(I2C_PRT);
		
		_delay_us(1);
		I2C_PRT &= ~(1 << LCD_EN);
		I2C::write(I2C_PRT);
		_delay_us(100);
		
		I2C::endTransmission();
		
	}
	
	
}


void LCD::Init(){
	if (configType == LCD_8_BIT)
	{
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
	else if (configType == LCD_4_BIT)
	{
		LCD_DDR = 0xFF;

		LCD_PRT &= ~(1 << LCD_EN);
		
		_delay_us(2000);
		command(0x33);
		command(0x32);
		command(0x28);
		command(0x0E);
		command(0x01);
		
		_delay_us(2000);
		command(0x06);
	}
	else if (configType == LCD_I2C)
	{
		I2C::begin(TYPE_MASTER);
		I2C::beginTransmission(LCD_I2C_ADDR);
				
		I2C_PRT &= ~(1 << LCD_EN);
		I2C::write(I2C_PRT);
		
		I2C::endTransmission();
		
		_delay_us(2000);
		command(0x33);
		command(0x32);
		command(0x28);
		command(0x0E);
		command(0x01);
		
		_delay_us(2000);
		command(0x06);
		
		
	}
}


void LCD::printData(uint8_t data){
	if (configType == LCD_8_BIT)
	{
		LCD_DPRT = data;
		LCD_CPRT |= (1 << LCD_RS);
		LCD_CPRT &= ~(1 << LCD_RW);
		LCD_CPRT |= (1 << LCD_EN);
		
		_delay_us(1);
		LCD_CPRT &= ~(1 << LCD_EN);
		_delay_us(100);	
	}
	else if (configType == LCD_4_BIT)
	{
		LCD_PRT = (LCD_PRT & 0x0F) | (data & 0xF0);
		LCD_PRT |= (1 << LCD_RS);
		LCD_PRT &= ~(1 << LCD_RW);
		LCD_PRT |= (1 << LCD_EN);
		
		_delay_us(1);
		LCD_PRT &= ~(1 << LCD_EN);
		
		LCD_PRT = (LCD_PRT & 0x0F) | (data << 4);
		LCD_PRT |= (1 << LCD_EN);
		_delay_us(1);
		LCD_PRT &= ~(1 << LCD_EN);
		_delay_us(100);
		
	}
	else if(configType == LCD_I2C){
		I2C::beginTransmission(LCD_I2C_ADDR);
		
		I2C_PRT = (I2C_PRT & 0x0F) | (data & 0xF0);
		I2C::write(I2C_PRT);
		I2C_PRT |= (1 << LCD_RS);
		I2C::write(I2C_PRT);
		I2C_PRT &= ~(1 << LCD_RW);
		I2C::write(I2C_PRT);
		I2C_PRT |= (1 << LCD_EN);
		I2C::write(I2C_PRT);
		
		_delay_us(1);
		I2C_PRT &= ~(1 << LCD_EN);
		I2C::write(I2C_PRT);
		
		I2C_PRT = (I2C_PRT & 0x0F) | (data << 4);
		I2C::write(I2C_PRT);
		I2C_PRT |= (1 << LCD_EN);
		I2C::write(I2C_PRT);
		_delay_us(1);
		I2C_PRT &= ~(1 << LCD_EN);
		I2C::write(I2C_PRT);
		_delay_us(100);
		
		I2C::endTransmission();
	}
	
	
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