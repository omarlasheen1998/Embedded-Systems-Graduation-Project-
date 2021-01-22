
#include "STD_TYPES.h"
#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

#define NULL_PTR ((void*)0)


void ADC_voidInit(void);
u16 ADC_u16ReadChannelPoll(u16 Channel_u16Number);
void ADC_voidReadChannelInterrupt(u16 Channel_u16Number);
void ADC1_voidSetCallBack(void(*a_ptr)(void));
u16 ADC_u16ReturnValue(void);
#endif
