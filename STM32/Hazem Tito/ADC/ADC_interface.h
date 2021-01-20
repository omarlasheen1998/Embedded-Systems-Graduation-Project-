#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

#define NULL_PTR ((void*)0)


void ADC_voidInit(void);
uint16 ADC_u16ReadChannelPoll(uint16 Channel_u16Number);
void ADC_voidReadChannelInterrupt(uint16 Channel_u16Number);
void ADC1_voidSetCallBack(void(*a_ptr)(void));
#endif
