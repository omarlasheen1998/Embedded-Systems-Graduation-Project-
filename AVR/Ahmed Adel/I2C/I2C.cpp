/*
 * I2C.cpp
 *
 * Created: 7/22/2020 6:17:49 PM
 *  Author: ahmed
 */ 

 

#include "I2C.h"
uint8_t I2C::bytesNumber = 0;
uint8_t I2C::slaveFlag = 0;



void I2C::begin(uint8_t type){
	if (type == TYPE_MASTER)
	{
		TWSR &= 0xFC;
		TWSR |= PS_VALUE;
		TWBR = BIT_RATE;
		TWCR |= (1 << TWEN);
	}
	else if (type == TYPE_SLAVE)
	{
		TWCR |= (1 << TWEN);
		slaveFlag = 1;
	}
}



uint8_t I2C::checkStatusCode(uint8_t code){
	if (code == (TWSR & 0xF8))
	{
		return 0;
	}
	else{
		return 1;
	}
}

void I2C::setAddress(uint8_t addr){
	TWAR = addr << 1;
	TWAR |= (1 << TWGCE);
	TWCR |= (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
}

uint8_t I2C::write(uint8_t data){
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	while((TWCR & (1 << TWINT)) == 0);
	
	if (slaveFlag)
	{
		
		if (checkStatusCode(S_SLA_R_RECEIVED_WITH_ACK))					
		{
			return 0;
		}
		else if (checkStatusCode(S_DATA_TRANSMITTED_WITH_ACK))					
		{
			return 1;										
		}	
		else if (checkStatusCode(S_DATA_TRANSMITTED_WITH_NACK))					
		{
			TWCR |= (1<<TWINT);						
			return 2;
		}
		else if (checkStatusCode(S_DATA_TRANSMITTED_WITH_ACK_INSTEAD_OF_NACK))
		{
			return 3;									
		}
		else						
		{
			return 4;
		}
	}
	
	else{
		if (checkStatusCode(M_SLA_W_TRANSMITTED_WITH_ACK))
		{
			return 0;
		}
		else if (checkStatusCode(M_SLA_W_TRANSMITTED_WITH_NACK))
		{
			return 1;
		}
		else if (checkStatusCode(M_DATA_TRANSMITTED_WITH_ACK))
		{
			return 2;
		}
		else if (checkStatusCode(M_DATA_TRANSMITTED_WITH_NACK))
		{
			return 3;
		}
		else{
			return 4;
		}
	}
}

uint8_t I2C::beginTransmission(uint8_t addr){
	TWCR |= (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while((TWCR & (1 << TWINT)) == 0);
	addr = addr << 1;
	return write(addr);
}

uint8_t I2C::requestFrom(uint8_t addr, uint8_t bytes){
	TWCR |= (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while((TWCR & (1 << TWINT)) == 0);
	addr = (addr << 1 | 1);
	bytesNumber = bytes;
	return write(addr);
	
}


void I2C::endTransmission(){
	TWCR |= (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

uint8_t I2C::read(){
	if (!slaveFlag)
	{
		if (bytesNumber > 1)
		{
			TWCR |= (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
			bytesNumber--;
		}
		else{
			TWCR |= (1 << TWINT) | (1 << TWEN);
			TWCR &= ~(1 << TWEA);
		}
	}
	else{
		TWCR |= (1 << TWINT) | (1 << TWEN);
	}
	
	
	while((TWCR & (1 << TWINT)) == 0);
	return TWDR;
}

uint8_t I2C::listen(){
	//while ((TWCR & (1 << TWINT)) == 0);
	while(1)
	{
		while (!(TWCR & (1<<TWINT)));
		
		if (checkStatusCode(S_SLA_W_RECEIVED_WITH_ACK))
		{
			return 0;									
		}
		else if (checkStatusCode(S_SLA_R_RECEIVED_WITH_ACK))
		{
			return 1;
		}
		else if (checkStatusCode(S_GC_SLA_W_RECEIVED_WITH_ACK))
		{
			return 2;
		}
		else
			continue;								
	}
}

void I2C::disableGeneralCall(){
	TWAR &= ~(1 << TWGCE);
}