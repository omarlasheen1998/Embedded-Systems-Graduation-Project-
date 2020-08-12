#ifndef F_CPU 
#define F_CPU 16000000ul
#endif

#include "DIO.h"
#include "LCD.h"
#include "RegDIO.h"
#include <util/delay.h>

void LCD_commend(u8 comnd ,u8 states)
{
	if(states== Eight_bits)
	{
	digitalWrightport(data,comnd);
	digitalWrightpin(command,RS,LOW);
	digitalWrightpin(command,RW,LOW);
	digitalWrightpin(command,E,HIGH);
	_delay_us(1);
	digitalWrightpin(command,E,LOW);
	_delay_us(100);
	
	}
	
	else if(states== Four_bits)
		
		{
		digitalWrightport(datacomm,( (datacomm&0x0f) | (comnd&0xf0) ) );
		digitalWrightpin(datacomm,RS,LOW);
		digitalWrightpin(datacomm,RW,LOW);
		digitalWrightpin(datacomm,E,HIGH);
		_delay_us(1);
		digitalWrightpin(datacomm,E,LOW);
		_delay_us(100);
		digitalWrightport(datacomm,((datacomm&0x0f)|(comnd<<4) ));
		digitalWrightpin(datacomm,E,HIGH);
		_delay_us(1);
		digitalWrightpin(datacomm,E,LOW);
		_delay_us(100);
		
	}
	
}


void LCD_data(u8 statment,u8 states){
	
	if(states== Eight_bits)
	{
	digitalWrightport(data,statment);
	digitalWrightpin(command,RS,HIGH);
	digitalWrightpin(command,RW,LOW);
	digitalWrightpin(command,E,HIGH);
	_delay_us(1);
	digitalWrightpin(command,E,LOW);
	_delay_us(100);
	}
	
	else if(states== Four_bits){
		
		
		digitalWrightport(datacomm,((datacomm&0x0f)|(statment&0xf0)));
		digitalWrightpin(datacomm,RS,HIGH);
		digitalWrightpin(datacomm,RW,LOW);
		digitalWrightpin(datacomm,E,HIGH);
		_delay_us(1);
		digitalWrightpin(datacomm,E,LOW);
		_delay_us(100);
		digitalWrightport(datacomm,((datacomm&0x0f)|(statment<<4)));
		digitalWrightpin(datacomm,E,HIGH);
		_delay_us(1);
		digitalWrightpin(datacomm,E,LOW);
		_delay_us(100);
		
		
	}
	
	
}


void LCD_initalizaion(u8 states){
	if(states== Eight_bits)
	{
		
	
	pinModeport(data,OUTPUT);
	pinModeport(command,OUTPUT);

	digitalWrightpin(data,E,LOW);
	_delay_ms(15);
	LCD_commend(0x38,Eight_bits);
	LCD_commend(0x0E,Eight_bits);
	LCD_commend(0x01,Eight_bits);
	_delay_us(1000);
	LCD_commend(0x06,Eight_bits);
	
	}
	else if(states== Four_bits){
		
		 pinModeport(datacomm,OUTPUT);
		 digitalWrightpin(datacomm,E,LOW);
		 _delay_ms(15);
		 LCD_commend(0x33,Four_bits);
		 LCD_commend(0x32,Four_bits);
		 LCD_commend(0x28,Four_bits);
		 LCD_commend(0x0E,Four_bits);
		 LCD_commend(0x01,Four_bits);
		 _delay_us(1000);
		 LCD_commend(0x06,Four_bits);
		
	}
	
	
}

void LCD_goto(u8 x, u8 y,u8 states){
	u8 arr[]={0x80,0xC0};
		if(states==Eight_bits){
	LCD_commend(arr[y-1]+x-1,Eight_bits);
		}
		
		else if(states==Four_bits){
			LCD_commend(arr[y-1]+x-1,Four_bits);
		}
}


void LCD_print(u8 *str ,u8 states){
	
	if (states==Eight_bits)
	{
		u8 i=0;
		
		while(str[i]!=0)
		{
			LCD_data(str[i],Eight_bits);
			i++;
		}
	}
		
		else if (states==Four_bits)
		{
			u8 i=0;
			
			while(str[i]!=0)
			{
				
				LCD_data(str[i],Four_bits);
				i++;
				
			}
		
	}
	
	
}
