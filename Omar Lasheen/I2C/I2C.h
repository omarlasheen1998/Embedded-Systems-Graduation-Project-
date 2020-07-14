/*
 * IncFile1.h
 *
 * Created: 14-Jul-20 4:19:02 AM
 *  Author: Lasheen
 */ 


#ifndef I2C_H_
#define I2C_H_

#define F_CPU 1000000UL							/* Define CPU clock Frequency e.g. here its 8MHz */
#include <avr/io.h>								/* Include AVR std. library file */
#include <util/delay.h>							/* Include inbuilt defined Delay header file */
#include <math.h>								/* Include math function */
#include <stdint.h>


#define BITRATE(TWSR)	((F_CPU/I2C_CLOCK)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1))))) /* Define bit rate */
extern unsigned int I2C_CLOCK;


//I2C Status 
#define TW_START         0x08 // start has been sent
#define TW_REP_START     0x10 // repeated start
#define TW_MT_SLA_W_ACK  0x18 // Master transmit ( slave address + Write request ) to slave + Ack received from slave
#define TW_MT_SLA_W_NACK 0x20 // Master transmit ( slave address + Write request ) to slave + NAck received from slave
#define TW_MT_SLA_R_ACK  0x40 // Master transmit ( slave address + Read request ) to slave + Ack received from slave
#define TW_MT_SLA_R_NACK 0x48 // Master transmit ( slave address + Read request ) to slave + NAck received from slave
#define TW_MT_DATA_ACK   0x28 // Master transmit data and ACK has been received from Slave.
#define TW_MT_DATA_NACK  0x30 // Master transmit data and NACK has been received from Slave.
#define TW_MR_DATA_ACK   0x50 // Master received data and send ACK to slave
#define TW_MR_DATA_NACK  0x58 // Master received data but doesn't send ACK to slave
#define TW_SLAVE_ST   0xA0 // Check for STOP/REPEATED START received
#define TW_SLAVE_DATA_ACK   0xB8  // Check for slave data transmitted & ack received
#define TW_SLAVE_DATA_NACK  0xC0 // Check for slave data transmitted & nack received
#define TW_SLAVE_LAST_DATA_ACK  0xC8 //Last slave data byte in TWDR has been transmitted (TWEA = “0”); ACK has been received



void I2C_Master_Init(unsigned int SCLK);								/* I2C initialize function */
uint8_t  I2C_Start(char write_address);			/* I2C start function */
uint8_t  I2C_Repeated_Start(char read_address);	/* I2C repeated start function */
void I2C_Stop();								/* I2C stop function */
void I2C_Start_Wait(char write_address);		/* I2C start wait function */
uint8_t  I2C_Write(char data);					/* I2C write function */
char I2C_Read_Ack();							/* I2C read ack function */
char I2C_Read_Nack();							/* I2C read nack function */

void I2C_Slave_Init(uint8_t slave_address);		/* I2C slave initialize function with Slave address */
int8_t I2C_Slave_Listen();						/* I2C slave listen function */
int8_t I2C_Slave_Transmit(char data);			/* I2C slave transmit function */
char I2C_Slave_Receive();						/* I2C slave receive function */



#endif /* INCFILE1_H_ */