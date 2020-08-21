

#ifndef ADC_H_
#define ADC_H_

#define u8 unsigned char
#define u16 short int 
#define set_bit(Register,bit)  Register|=(1<<bit)
#define clc_bit(Register,bit)  Register&=~(1<<bit)
#define Internal 0
#define AREF     1

//mode_source INternal or Aref
void ADC_initilization(u8 mode_source,u8 pin,u8 number_bits );
u16 ADC_getValue(u8 number_bits);


#endif /* ADC_H_ */