/*
 * IncFile1.h
 *
 * Created: 4/30/2020 3:47:45 AM
 *  Author: Lasheen
 */ 


#ifndef GPIO_H_
#define GPIO_H_

#include <stdbool.h>
#include <stdint.h>
#define A0 0
#define A1 1
#define A2 2
#define A3 3
#define A4 4
#define A5 5
#define A6 6
#define A7 7

#define B0 10
#define B1 11
#define B2 12
#define B3 13
#define B4 14
#define B5 15
#define B6 16
#define B7 17

#define C0 20
#define C1 21
#define C2 22
#define C3 23
#define C4 24
#define C5 25
#define C6 26
#define C7 27

#define D0 30
#define D1 31
#define D2 32
#define D3 33
#define D4 34
#define D5 35
#define D6 36
#define D7 37

#define INPUT 40
#define OUTPUT 41
#define INPUT_PULLUP 42
#define HIGH 51
#define LOW 50

#define INT_LOW 60
#define INT_CHANGE 61
#define INT_FALLING 62
#define INT_RISING 63

void pinMode(uint8_t pinNo,uint8_t State);
void digitalWrite(uint8_t pinNo,uint8_t Status);
bool digitalRead(uint8_t pinNo);
void attachInterrupt(uint8_t pinNo,uint8_t state,void (*Local_ISR)(void));
void noInterrupts(void);
void Interrupts(void);

#endif /* GPIO_H_ */