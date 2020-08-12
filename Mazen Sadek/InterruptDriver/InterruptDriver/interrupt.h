


#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#define  u8 unsigned char
#define set_bit(Address,bit) Address|=(1<<bit)
#define clc_bit(Address,bit) Address&=~(1<<bit)
//status
#define Falling 0
#define Rasing  1
#define changing 2
#define Low_level 3
//pinInterrupt
#define int0 0
#define int1 1
#define int2 2

void INT_initilizaiton(u8 pin_interrupt,u8 status);


#endif /* INTERRUPT_H_ */