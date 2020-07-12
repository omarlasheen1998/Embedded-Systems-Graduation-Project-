/*
 * IncFile1.h
 *
 * Created: 5/21/2020 2:08:56 PM
 *  Author: Lasheen
 */ 


#ifndef I2C_H_
#define I2C_H_

/* I2C Status Bits in the TWSR Register */

//For MASTER 
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
 	  
void I2C_Master_Init(int SCL_CLK);
void I2C_Slave_Init(unsigned char slave_address);
unsigned char I2C_Start(unsigned char write_address);
unsigned char I2C_Repeated_Start(unsigned char read_address);
unsigned char I2C_Write(unsigned char data);
char I2C_Read(unsigned char no);
void I2C_Stop()	;
unsigned char I2C_Slave_Listen();
char I2C_Slave_Transmit(unsigned char data);
char I2C_Slave_Receive();

#endif /* INCFILE1_H_ */