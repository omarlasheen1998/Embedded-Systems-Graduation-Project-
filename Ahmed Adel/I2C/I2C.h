/*
 * I2C.h
 *
 * Created: 7/22/2020 6:18:25 PM
 *  Author: ahmed
 */ 


#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>

#define PS_VALUE PS_VALUE_1     //Prescalar Value
#define BIT_RATE 0x20

#define SLA_W 0
#define SLA_R 1

#define TYPE_SLAVE 0
#define TYPE_MASTER 1

// Status Register Values for Master Transmitter
#define START_TRANSMITTED 0x08
#define M_SLA_W_TRANSMITTED_WITH_ACK 0x18
#define M_SLA_W_TRANSMITTED_WITH_NACK 0x20
#define M_DATA_TRANSMITTED_WITH_ACK 0x28
#define M_DATA_TRANSMITTED_WITH_NACK 0x30

// Status Register Values for Master Receiver
#define M_SLA_R_TRANSMITTED_WITH_ACK 0x40
#define M_SLA_R_TRANSMITTED_WITH_NACK 0x48
#define M_DATA_RECEIVED_WITH_ACK 0x50
#define M_DATA_RECEIVED_WITH_NACK 0x58


// Status Register Values for Slave Transmitter
#define S_SLA_R_RECEIVED_WITH_ACK 0xA8
#define S_DATA_TRANSMITTED_WITH_ACK 0xB8
#define S_DATA_TRANSMITTED_WITH_NACK 0xC0
#define S_DATA_TRANSMITTED_WITH_ACK_INSTEAD_OF_NACK 0xC8


// Status Register Values for Slave Receiver
#define S_SLA_W_RECEIVED_WITH_ACK 0x60
#define S_GC_SLA_W_RECEIVED_WITH_ACK 0x70
#define S_DATA_RECEIVED_WITH_ACK 0x80
#define S_GC_DATA_RECEIVED_WITH_ACK 0x90
#define S_DATA_RECEIVED_WITH_NACK 0x88
#define S_GC_DATA_RECEIVED_WITH_NACK 0x98
#define STOP_OR_RS_RECEIVED 0xA0


 

class I2C{
	
	public:
	static void begin(uint8_t type);
	static uint8_t beginTransmission(uint8_t addr);
	static uint8_t requestFrom(uint8_t addr, uint8_t bytes);
	static uint8_t write(uint8_t data);
	static uint8_t read();
	static void endTransmission(void);
	static void setAddress(uint8_t addr);
	static uint8_t listen(void);
	static void disableGeneralCall(void);
	
	private:
	static uint8_t slaveFlag;
	static uint8_t bytesNumber;
	static uint8_t checkStatusCode(uint8_t code);
	static const uint8_t PS_VALUE_1 = 0x00;
	static const uint8_t PS_VALUE_4 = 0x01;
	static const uint8_t PS_VALUE_16 = 0x02;
	static const uint8_t PS_VALUE_64 = 0x03;
	
	
	
	
	
};



#endif /* I2C_H_ */