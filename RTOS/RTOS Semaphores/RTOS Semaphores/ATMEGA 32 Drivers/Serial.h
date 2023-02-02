/*
 * IncFile1.h
 *
 * Created: 5/16/2020 5:00:23 PM
 *  Author: Lasheen
 */ 


#ifndef Serial_H_
#define Serial_H_
#include <stdbool.h>


#define FLOAT 40
#define INT 41
#define CHAR 42
#define STRING 43


#define RX_INTERRUPT 50
#define TX_INTERRUPT 51
#define NO_PARITY 60
#define EVEN_PARITY 61
#define ODD_PARITY 62
   


void Serial_begin (int BAUD);
void Serial_print (void* data,unsigned char type);
bool Serial_available(void);
void Serial_flush(void);
unsigned char Serial_read (void);
void Serial_attachInterrupt(unsigned char Case,void (*Local_ISR)(void));
void Add_ParityBit(unsigned char UART_PARITY);
void Set_U2X_transmission(void);

void Serial_readString(unsigned char *x, unsigned char size);
void Serial_readStringUntil(unsigned char *x, unsigned char c);


#endif /* INCFILE1_H_ */
