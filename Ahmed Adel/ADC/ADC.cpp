/*
 * ADC.cpp
 *
 * Created: 7/8/2020 8:37:44 AM
 *  Author: ahmed
 */ 

#include "ADC.h"

uint8_t conversionType = 0;


uint8_t setConversionType(uint8_t convType){
	if (convType == CONVERSION_10_BIT || convType == CONVERSION_8_BIT){
		conversionType = convType;
		switch(convType){
			case CONVERSION_10_BIT:
				ADMUX &= ~(1 << ADLAR);
				break;
			case CONVERSION_8_BIT:
				ADMUX |= (1 << ADLAR);
				break;
		}
		return 0;
	}
	else{
		return 1;
	}
}

uint8_t setPrescaler(uint8_t divFactor){
	if (divFactor >= DIV_FACTOR_2 && divFactor <= DIV_FACTOR_128){
		ADCSRA &= ~(1 << ADPS0) & ~(1 << ADPS1) & ~(1 << ADPS2);
		ADCSRA |= (divFactor << ADPS0); 	
		return 0;
	}
	else{
		return 1;
	}
	
}

uint8_t setAnalogReference(uint8_t refVolt){
	if (refVolt == REF_DEFAULT || refVolt == REF_INTERNAL_2V56 || refVolt == REF_EXTERNAL){
		ADMUX &= ~(1 << REFS0) & ~(1 << REFS1);
		ADMUX |= (refVolt << REFS0);
		return 0;
	}
	else{
		return 1;
	}
}

uint8_t ADC_Init(uint8_t divFactor, uint8_t convType, uint8_t referenceVolt){
	ADCSRA |= (1 << ADEN);
	if (!setAnalogReference(referenceVolt) && !setConversionType(convType) && !setPrescaler(divFactor))
	{
		return 0;
	}
	else{
		return 1;
	}
}


uint16_t analogRead(uint8_t channel){
	ADMUX &= ~(1 << MUX0) & ~(1 << MUX1) & ~(1 << MUX2);
	if (channel > 7 || channel < 0)
	{
		channel &= 0x07;
	}
	ADMUX |= (channel << MUX0);
	ADCSRA |= (1 << ADSC);
	while(ADCSRA & (1 << ADSC));
	return ADCW;
}
