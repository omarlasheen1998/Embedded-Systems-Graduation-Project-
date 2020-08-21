/*
 * ADC.h
 *
 * Created: 7/8/2020 8:37:56 AM
 *  Author: ahmed
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>


#define CONVERSION_8_BIT 0
#define CONVERSION_10_BIT 1

#define DIV_FACTOR_2 1
#define DIV_FACTOR_4 2
#define DIV_FACTOR_8 3
#define DIV_FACTOR_16 4
#define DIV_FACTOR_32 5
#define DIV_FACTOR_64 6
#define DIV_FACTOR_128 7

#define REF_DEFAULT 1
#define REF_EXTERNAL 0
#define REF_INTERNAL_2V56 3


uint8_t ADC_Init(uint8_t divFactor, uint8_t convType, uint8_t referenceVolt);
uint8_t setAnalogReference(uint8_t refVolt);
uint8_t setConversionType(uint8_t convType);
uint8_t setPrescaler(uint8_t divFactor);

uint16_t analogRead(uint8_t channel);
uint16_t differentialRead(uint8_t channel);





#endif /* ADC_H_ */