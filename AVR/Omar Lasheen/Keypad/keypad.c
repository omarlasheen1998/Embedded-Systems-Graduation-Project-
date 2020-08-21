/*
 * CFile1.c
 *
 * Created: 5/13/2020 9:45:46 PM
 *  Author: Lasheen
 */ 
#include "keypad.h"
#include <avr/io.h>
#include "Gpio.h"
#include <util/delay.h>
unsigned int Xcol,Yrow;
 
unsigned char ROWS[MAX_ROWS];
unsigned char COLS[MAX_COLS];
unsigned char KEYS[MAX_ROWS][MAX_COLS];

void Keypad_SetUp(unsigned char *rows,unsigned char *cols,int r,int c,unsigned char Keys[r][c])
{
	Xcol = c;
	Yrow = r;
    char i,j;
	for(i=0;i<Yrow;i++)
	{ROWS[i]=rows[i];
	pinMode(ROWS[i],OUTPUT);
	digitalWrite(ROWS[i],HIGH);
    }
	for(i=0;i<Xcol;i++)
	{   COLS[i]=cols[i];
		pinMode(cols[i],INPUT_PULLUP);
	}
	for(i=0;i<Yrow;i++)
	for(j=0;j<Xcol;j++)
	KEYS[i][j]=Keys[i][j];
	
}

unsigned char Keypad_getKey(){
	int i,j;
	for(i=0;i<Yrow;i++)
	 digitalWrite(ROWS[i],HIGH);
	 asm volatile("NOP");
	for(i=0;i<Yrow;i++)
     {
	  digitalWrite(ROWS[i],LOW);
	  if(i>=1)
	  digitalWrite(ROWS[i-1],HIGH);
		asm volatile("NOP");
		for(j=0;j<Xcol;j++)
		if(digitalRead(COLS[j])==0)
	    return(KEYS[i][j]);
	  digitalWrite(ROWS[i],HIGH);
	 }
	 
	return NOKEY;
}

unsigned char Keypad_waitUntilKey(){
	
	unsigned char c=NOKEY;
	while(c==NOKEY)
	 c=Keypad_getKey();
	 
	 return c;
}
