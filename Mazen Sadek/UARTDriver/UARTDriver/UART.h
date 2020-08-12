/*
 * UART.h
 *
 * Created: 8/11/2020 7:31:57 PM
 *  Author: Mazen Sadek
 */ 


#ifndef UART_H_
#define UART_H_


#define  u8 unsigned char

void UART_init(int buadrate);    // No parity One Stop Bit  ASynchronous  8Bit Data  
void UART_sendChar(u8 data);
u8 UART_ReciveChar(void);

#endif /* UART_H_ */