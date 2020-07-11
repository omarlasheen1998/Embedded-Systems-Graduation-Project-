/*
 * IncFile1.h
 *
 * Created: 5/8/2020 5:03:44 AM
 *  Author: Lasheen
 */ 


#ifndef lcd_H_
#define lcd_H_

//connect E,RS,and data pins to the microcontroller in 8-bit mode, and from D4-D7 in 4-bit mode
#include <avr/io.h>
#include "Gpio.h"


#define FLOAT 40
#define INT 41
//arguments to lcd_begin in addition to  PORTA,PORTB,PORTC,PORTD

#define REGA_LOWER 50
#define REGB_LOWER 51
#define REGC_LOWER 52 
#define REGD_LOWER 53
#define REGA_UPPER 54
#define REGB_UPPER 55
#define REGC_UPPER 56
#define REGD_UPPER 57
#define REGA 58
#define REGB 59
#define REGC 60
#define REGD 61


void LCD_Begin (unsigned char x,unsigned char y);
void LCD_String(unsigned char *str);		/* Send string to LCD function */
void LCD_String_xy (unsigned char *str,unsigned char row,unsigned char pos);		
void LCD_Clear();
void LCD_SetUpManual(unsigned char no,unsigned char rs,unsigned char en,unsigned char pins[no]);
void LCD_SetUpReg(unsigned char rs,unsigned char en,unsigned char port);
void LCD_SetPosition(unsigned char row,unsigned char pos);
void LCD_Print(void* x,unsigned char type);
void DISPLAY_ON();
void DISPLAY_OFF();
void CURSOR_ON();
void CURSOR_OFF();
void shift_left();
void shift_right();
void increment_right();
void increment_Left();
void LCD_Custom_Char (unsigned char loc, unsigned char *msg);
void LCD_Char( unsigned char data );
//lcd Commands

#define CLEAR 0x01 
#define HOME 0x02
#define _4_bitMode 0x28
#define _8_bitMode 0x38
#define _4_MANUAL 127
#define _8_MANUAL 128
#define DECREMENT_CURSOR 0x04
#define INCREMENT_CURSOR 0x06
#define DIS_ON_CURSOR_ON 0x0E 
#define DIS_ON_CURSOR_OFF 0x0C
#define DIS_OFF_CURSOR_OFF 0x08
#define RIGHT 0x1C
#define LEFT 0x18

/* this library is designed to access lcd pixels of	16X2, 20x4 , 40x2 LCDS
address of first line starts at 0x80
address of 2nd line starts at 0xC0
address of 3rd line starts at 0x94
address of 4th line starts at 0xD4 */

#endif /* INCFILE1_H_ */