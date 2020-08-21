/*
 * IncFile1.h
 *
 * Created: 5/3/2020 3:24:33 AM
 *  Author: Lasheen
 */ 

// this ADC driver is written in Arduino functions Format with additional functions to allow modification of ADC parameters and functions

#ifndef ADC_H_
#define ADC_H_
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <stdint.h>

#define DEFAULT 100 //depend on AVCC pin voltage
#define EXTERNAL 101 //depend on Aref pin voltage
#define INTERNAL2V56 102 //depend on internal 2.56V reference

void setADC_Prescaler(uint8_t x);
void analogReference(uint8_t ref);
uint16_t analogRead(uint8_t channel);
float analogReadVolts(uint8_t channel,float voltage);
void ADC_Init(void);
void ADC_attachInterrupt(void (*ADC_Finish)(void));
uint16_t ADC_ReturnValue(void);
uint8_t ADC_ReturnADCL(void);
uint8_t ADC_ReturnADCH(void);
void ADC_startConversion(uint8_t channel);
int16_t differentialRead(uint8_t channel);
#endif /* INCFILE1_H_ */