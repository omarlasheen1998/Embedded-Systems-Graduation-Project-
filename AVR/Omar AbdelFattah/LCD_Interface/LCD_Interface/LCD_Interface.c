/*
 * LCD_Interface.c
 *
 * Created: 20/08/2020 04:46:34 ص
 *  Author: omar
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define MrLCDsCrib PORTB
#define MrLCDsControl PORTD
#define DataDirMrLCDsControl DDRD
#define DataDir_MrLCDsCrib DDRB
#define LCDEN 5
#define ReadWriteBar 7
#define DataCommandBar 2 
//#define BusyPin 7
//#define MrLCDsCribPin PINB
void LCD_Init(void);
void Check_IF_MrLCD_isBusy (void);
void Peek_A_Boo(void);
void Send_A_Command (unsigned char command);
void SendCharacter (unsigned char character);
int main(void)
{
	LCD_Init();
	SendCharacter(0x4E);
	SendCharacter(0x4E);
	SendCharacter(0x4E);
    while(1)
    {
	}       
}

void Check_IF_MrLCD_isBusy (void)
{
	DataDir_MrLCDsCrib=0; //tell Mcu to be input
	MrLCDsControl |=1<<ReadWriteBar; // tell LCD to be in read mode
	MrLCDsControl &=~(1<<DataCommandBar); //tell lcd to give us a command
	while (MrLCDsCrib>=0x80) //busy means D7  =1
	{
		Peek_A_Boo();
	}
	DataDir_MrLCDsCrib=0xFF;
}
void Peek_A_Boo(void)
{
	MrLCDsControl |= 1<<LCDEN;
asm volatile ("nop");
asm volatile ("nop");
MrLCDsControl &= ~1<<LCDEN;
}
void Send_A_Command (unsigned char command)
{
	Check_IF_MrLCD_isBusy();
MrLCDsCrib = command;
MrLCDsControl &= ~ ((1<<ReadWriteBar)|(1<<DataCommandBar));
Peek_A_Boo();
MrLCDsCrib = 0;
}
void SendCharacter (unsigned char character)
{
	Check_IF_MrLCD_isBusy();
MrLCDsCrib = character;
MrLCDsControl &= ~ (1<<ReadWriteBar);
MrLCDsControl |= 1<<DataCommandBar;
Peek_A_Boo();
MrLCDsCrib = 0;
}
void LCD_Init(void){
	DataDirMrLCDsControl |= 1<<LCDEN | 1<<ReadWriteBar | 1<DataCommandBar;
	_delay_ms(15);
	Send_A_Command(0x01);
	_delay_ms(2);
	Send_A_Command(0x38);
	_delay_us(50);
	Send_A_Command(0b00001110);
	_delay_us(50);
}