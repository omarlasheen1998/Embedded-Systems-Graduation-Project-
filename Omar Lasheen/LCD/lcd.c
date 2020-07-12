/*
 * CFile1.c
 *
 * Created: 5/8/2020 5:03:37 AM
 *  Author: Lasheen
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>			/* Include Delay header file */
#include <stdio.h>
#include "Gpio.h"
#include "lcd.h"
#include <stdint.h>

typedef union
{
	struct
	{
		unsigned char bit1 : 1;
		unsigned char bit2 : 1;
		unsigned char bit3 : 1;
		unsigned char bit4 : 1;
		unsigned char bit5 : 1;
		unsigned char bit6 : 1;
		unsigned char bit7 : 1;
		unsigned char bit8 : 1;
	}e;
	unsigned char cmd;
}Manual;

Manual lcd;
volatile unsigned char *LCD_Port;
volatile unsigned char *LCD_Dir;
unsigned char RS;
unsigned char EN;
unsigned char Mode;
unsigned char X;
unsigned char Y;
unsigned char PRT;
unsigned char PINS[8];


void LCD_Command( unsigned char cmnd );


void LCD_Command( unsigned char cmnd )
{
	if(Mode == _4_bitMode)
	{
		
	if(PRT%10>=4 && PRT%10<=7)
	{
	*LCD_Port = (*LCD_Port & 0x0F) | (cmnd & 0xF0); /* sending upper nibble */
	digitalWrite(RS,LOW);		/* RS=0, command reg. */
	digitalWrite(EN,HIGH);		/* Enable pulse */
	_delay_us(1);
	digitalWrite(EN,LOW);
    _delay_us(200);

	*LCD_Port = (*LCD_Port & 0x0F) | (cmnd << 4);  /* sending lower nibble */
	digitalWrite(EN,HIGH);		/* Enable pulse */
	_delay_us(1);
	digitalWrite(EN,LOW);
	_delay_ms(2);
	
	}
    
	else if(PRT%10>=0 && PRT%10<=3)
	{
		*LCD_Port = (*LCD_Port & 0xF0) | (cmnd >> 4); /* sending upper nibble */
		digitalWrite(RS,LOW);		/* RS=0, command reg. */
		digitalWrite(EN,HIGH);		/* Enable pulse */
		_delay_us(1);
		digitalWrite(EN,LOW);
		_delay_us(200);

		*LCD_Port = (*LCD_Port & 0xF0) | (cmnd & 0X0F);  /* sending lower nibble */
		digitalWrite(EN,HIGH);		/* Enable pulse */
		_delay_us(1);
		digitalWrite(EN,LOW);
		_delay_ms(2);
		
	}
		
	}
	
	else if(Mode == _8_bitMode)
	{
	
	*LCD_Port = cmnd;
	digitalWrite(RS,LOW);		/* RS=0, command reg. */
	digitalWrite(EN,HIGH);		/* Enable pulse */
	_delay_us(1);
	digitalWrite(EN,LOW);
    _delay_ms(3);			
	
	}
	else if(Mode == _8_MANUAL)
	{
		
		lcd.cmd = cmnd;
		digitalWrite(PINS[0],lcd.e.bit1);
		digitalWrite(PINS[1],lcd.e.bit2);
		digitalWrite(PINS[2],lcd.e.bit3);
		digitalWrite(PINS[3],lcd.e.bit4);
		digitalWrite(PINS[4],lcd.e.bit5);
		digitalWrite(PINS[5],lcd.e.bit6);
        digitalWrite(PINS[6],lcd.e.bit7);
		digitalWrite(PINS[7],lcd.e.bit8);
		
		digitalWrite(RS,LOW);		/* RS=0, command reg. */
		digitalWrite(EN,HIGH);		/* Enable pulse */
		_delay_us(10);
		digitalWrite(EN,LOW);
		_delay_ms(5);
		
	}
	
	else if(Mode == _4_MANUAL)
	{
		
		lcd.cmd = cmnd&0xF0;
		digitalWrite(PINS[0],lcd.e.bit5);
		digitalWrite(PINS[1],lcd.e.bit6);
		digitalWrite(PINS[2],lcd.e.bit7);
		digitalWrite(PINS[3],lcd.e.bit8);
	
	digitalWrite(RS,LOW);		/* RS=0, command reg. */
	digitalWrite(EN,HIGH);		/* Enable pulse */
	_delay_us(10);
	digitalWrite(EN,LOW);
	_delay_us(200);

		lcd.cmd = cmnd<<4;
		digitalWrite(PINS[0],lcd.e.bit5);
		digitalWrite(PINS[1],lcd.e.bit6);
		digitalWrite(PINS[2],lcd.e.bit7);
		digitalWrite(PINS[3],lcd.e.bit8);
	digitalWrite(EN,HIGH);		/* Enable pulse */
	_delay_us(10);
	digitalWrite(EN,LOW);
	_delay_ms(5);
		
	}
}


void LCD_Begin (unsigned char x,unsigned char y)			/* LCD Initialize function */
{
	X=x;
	Y=y;
	
	if( Mode == _4_bitMode || Mode == _4_MANUAL)
	{
	
	_delay_ms(20);			/* LCD Power ON delay always >15ms */
	
	LCD_Command(0x33);/* send for 4 bit initialization of LCD  */
	LCD_Command(0x32);/* send for 4 bit initialization of LCD  */
	LCD_Command(Mode);              /* 2 line, 5*7 matrix in 4-bit mode */
	LCD_Command(HOME);
	LCD_Command(DIS_ON_CURSOR_OFF);              /* Display on cursor off*/
	LCD_Command(INCREMENT_CURSOR);              /* Increment cursor (shift cursor to right)*/
	LCD_Command(CLEAR);              /* Clear display screen*/
	_delay_ms(2);
	
	}
	else if( Mode == _8_bitMode || Mode == _8_MANUAL)
	{
	
	LCD_Command(Mode);              /* 2 line, 5*7 matrix in 4-bit mode */
	LCD_Command(HOME);
	LCD_Command(DIS_ON_CURSOR_OFF);              /* Display on cursor off*/
	LCD_Command(INCREMENT_CURSOR);              /* Increment cursor (shift cursor to right)*/
	LCD_Command(CLEAR);              /* Clear display screen*/
	_delay_ms(2);
		
		
	}
	
}

void LCD_Char( unsigned char data )
{
if(Mode == _8_bitMode )
{
	*LCD_Port = data; /* sending upper nibble */
	digitalWrite(RS,HIGH);		/* RS=1, data reg. */
	digitalWrite(EN,HIGH);		/* Enable pulse */
	_delay_us(1);
	digitalWrite(EN,LOW);
	
	_delay_ms(2);
}

else if(Mode == _8_MANUAL)
{	
	lcd.cmd = data;
	digitalWrite(PINS[0],lcd.e.bit1);
	digitalWrite(PINS[1],lcd.e.bit2);
	digitalWrite(PINS[2],lcd.e.bit3);
	digitalWrite(PINS[3],lcd.e.bit4);
	digitalWrite(PINS[4],lcd.e.bit5);
	digitalWrite(PINS[5],lcd.e.bit6);
	digitalWrite(PINS[6],lcd.e.bit7);
	digitalWrite(PINS[7],lcd.e.bit8);
	
	digitalWrite(RS,HIGH);		/* RS=1, data reg. */
	digitalWrite(EN,HIGH);		/* Enable pulse */
	_delay_us(10);
	digitalWrite(EN,LOW);
	_delay_ms(5);
	
}

else if(Mode == _4_MANUAL)
{
	
	lcd.cmd = data&0xF0;
	digitalWrite(PINS[0],lcd.e.bit5);
	digitalWrite(PINS[1],lcd.e.bit6);
	digitalWrite(PINS[2],lcd.e.bit7);
	digitalWrite(PINS[3],lcd.e.bit8);
	
	digitalWrite(RS,HIGH);		/* RS=1, data reg. */
	digitalWrite(EN,HIGH);		/* Enable pulse */
	_delay_us(10);
	digitalWrite(EN,LOW);
	_delay_us(200);

	lcd.cmd = data<<4;
	digitalWrite(PINS[0],lcd.e.bit5);
	digitalWrite(PINS[1],lcd.e.bit6);
	digitalWrite(PINS[2],lcd.e.bit7);
	digitalWrite(PINS[3],lcd.e.bit8);
	digitalWrite(EN,HIGH);		/* Enable pulse */
	_delay_us(10);
	digitalWrite(EN,LOW);
	_delay_ms(5);
	
}

else if(Mode == _4_bitMode)
{
	
	if(PRT%10>=4 && PRT%10<=7)
	{
		*LCD_Port = (*LCD_Port & 0x0F) | (data & 0xF0); /* sending upper nibble */
		digitalWrite(RS,HIGH);		/* RS=1, data reg. */
		digitalWrite(EN,HIGH);		/* Enable pulse */
		_delay_us(1);
		digitalWrite(EN,LOW);
		_delay_us(200);

		*LCD_Port = (*LCD_Port & 0x0F) | (data << 4);  /* sending lower nibble */
		digitalWrite(EN,HIGH);		/* Enable pulse */
		_delay_us(1);
		digitalWrite(EN,LOW);
		_delay_ms(2);
		
	}
	
	else if(PRT%10>=0 && PRT%10<=3)
	{
		*LCD_Port = (*LCD_Port & 0xF0) | (data >> 4); /* sending upper nibble */
		digitalWrite(RS,HIGH);		/* RS=1, data reg. */
		digitalWrite(EN,HIGH);		/* Enable pulse */
		_delay_us(1);
		digitalWrite(EN,LOW);
		_delay_us(200);

		*LCD_Port = (*LCD_Port & 0xF0) | (data & 0X0F);  /* sending lower nibble */
		digitalWrite(EN,HIGH);		/* Enable pulse */
		_delay_us(1);
		digitalWrite(EN,LOW);
		_delay_ms(2);
		
	}
	
}

}


void LCD_SetPosition(unsigned char row,unsigned char pos){
	
	    LCD_Command(HOME);	
		if (row == 0 )
		LCD_Command( pos + 0x80 );	/* Command of first row and required position<16 */
		else if (row == 1)
		LCD_Command( pos + 0xC0 );	/* Command of 2nd row and required position<16 */
		else if (row == 2)
		LCD_Command( pos + 0x94 );	/* Command of 3rd row and required position<16 */
		else if (row == 3)
		LCD_Command( pos + 0xD4 );	/* Command of 4th row and required position<16 */	
	
	
}

void LCD_String(unsigned char *str)		/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)		/* Send each char of string till the NULL */
	{
		LCD_Char (str[i]);
	}
}

void LCD_String_xy (unsigned char *str,unsigned char row,unsigned char pos)	/* Send string to LCD with xy position */
{ 		
	
   LCD_SetPosition(row,pos);		
   LCD_String(str);		/* Call LCD string function */
}

void LCD_Clear()
{
	LCD_Command (0x01);		/* Clear display */
	_delay_ms(2);
	LCD_Command (0x80);		/* Cursor at home position */
}

void LCD_SetUpManual(unsigned char no,unsigned char rs,unsigned char en,unsigned char pins[no]){
RS=rs;
EN=en;
pinMode(RS,OUTPUT);
pinMode(EN,OUTPUT);
if(no==4)
Mode=_4_MANUAL;
else if(no==8)
Mode=_8_MANUAL;
char i;

for(i=0;i<no;i++)	
{
PINS[i]=pins[i];
pinMode(PINS[i],OUTPUT);	
}
	
}
void LCD_SetUpReg(unsigned char rs,unsigned char en,unsigned char port)
{

RS=rs;
EN=en;
PRT=port;

if( port>=REGA && port<=REGD )
{
  
  Mode=_8_bitMode;
  if(port == REGA)
  {LCD_Dir=&DDRA;
  LCD_Port=&PORTA;
  *LCD_Dir = 0xFF;
  }
 else if(port == REGB)
  {LCD_Dir=&DDRB;
  LCD_Port=&PORTB;
  *LCD_Dir = 0xFF;
  }
 else if(port == REGC)
 {LCD_Dir=&DDRC;
 LCD_Port=&PORTC;
 *LCD_Dir = 0xFF;
 }
 else if(port == REGD)
 {LCD_Dir=&DDRD;
 LCD_Port=&PORTD;
 *LCD_Dir = 0xFF;
 }

}
			/* Make LCD port direction as o/p */
else if( port>=REGA_LOWER && port<=REGD_UPPER )
{
	Mode=_4_bitMode;
	if(port == REGA_UPPER)
	{LCD_Dir=&DDRA;
	LCD_Port=&PORTA;
	*LCD_Dir |= 0xF0;
	}

	else if(port == REGA_LOWER)
	{LCD_Dir=&DDRA;
	LCD_Port=&PORTA;
	*LCD_Dir |= 0x0F;
	}
	else if(port == REGB_UPPER)
	{LCD_Dir=&DDRB;
		LCD_Port=&PORTB;
		*LCD_Dir |= 0xF0;
	}

	else if(port == REGB_LOWER)
	{LCD_Dir=&DDRB;
		LCD_Port=&PORTB;
		*LCD_Dir |= 0x0F;
	}
	else if(port == REGC_UPPER)
	{LCD_Dir=&DDRC;
		LCD_Port=&PORTC;
		*LCD_Dir |= 0xF0;
	}

	else if(port == REGC_LOWER)
	{LCD_Dir=&DDRC;
		LCD_Port=&PORTC;
		*LCD_Dir |= 0x0F;
	}
	else if(port == REGD_UPPER)
	{LCD_Dir=&DDRD;
		LCD_Port=&PORTD;
		*LCD_Dir |= 0xF0;
	}

	else if(port == REGD_LOWER)
	{LCD_Dir=&DDRD;
	 LCD_Port=&PORTD;
	*LCD_Dir |= 0x0F;
	}
		
}
pinMode(RS,OUTPUT);
pinMode(EN,OUTPUT);
}

void LCD_Print(void* x,unsigned char type){
	
	char array[16];
	
	if(type == INT)
	{
		sprintf(array, "%d", *(int *)x);
		LCD_String(array);
		
	}
	
else if(type == FLOAT)
   {
	   float f1,f2;
	   int i1,i2;
	f1=floor(*(float *)x);
	f2=(*(float *)x) - f1;
	i1 = (int)f1;
	i2 = (int)100*f2;
	if(i2<10)
	sprintf(array,"%d.0%d", i1,i2);
	else
	sprintf(array,"%d.%d", i1,i2);
	
   LCD_String(array);
   }
   
}

void DISPLAY_ON(){
	LCD_Command(DIS_ON_CURSOR_OFF);
}
void DISPLAY_OFF(){
	LCD_Command(DIS_OFF_CURSOR_OFF);
}
void CURSOR_ON(){
	LCD_Command(DIS_ON_CURSOR_ON);
}
void CURSOR_OFF()
{
	LCD_Command(DIS_ON_CURSOR_OFF);
}
void shift_left(){
	
	LCD_Command(LEFT);
}
void shift_right(){
	LCD_Command(RIGHT);
}
void increment_right(){
	LCD_Command(INCREMENT_CURSOR);
}
void increment_Left()
{
	LCD_Command(DECREMENT_CURSOR);
}

void LCD_Custom_Char (unsigned char loc, unsigned char *msg)
{
	unsigned char i; // choose  a char number from 0 to 7 to store custom chars on gcram
	if(loc<8)
	{
		
		LCD_Command (0x40 + (loc*8));	/* Command 0x40 and onwards forces the device to point CGRAM address */
		for(i=0;i<8;i++)	/* Write 8 byte for generation of 1 character */
		LCD_Char(msg[i]);
	}

}