/*
 * IncFile1.h
 *
 * Created: 5/13/2020 9:46:19 PM
 *  Author: Lasheen
 */ 


#ifndef Keypad_H_
#define Keypad_H_

#define NOKEY '\0'
#define  MAX_ROWS 8
#define  MAX_COLS 8

void Keypad_SetUp(unsigned char *rows,unsigned char *cols,int r,int c,unsigned char Keys[r][c]);
unsigned char Keypad_getKey();
unsigned char Keypad_waitUntilKey();

#endif /* INCFILE1_H_ */