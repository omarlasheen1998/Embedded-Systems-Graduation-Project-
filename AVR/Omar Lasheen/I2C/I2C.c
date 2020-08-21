/*
 * CFile1.c
 *
 * Created: 14-Jul-20 4:19:24 AM
 *  Author: Lasheen
 */ 
#include "I2C.h"
unsigned int I2C_CLOCK;
void I2C_Master_Init(unsigned int SCLK)												/* I2C initialize function */
{
   	I2C_CLOCK=SCLK;
	TWBR = BITRATE(TWSR = 0x00);							/* Get bit rate register value by formula */
}


uint8_t I2C_Start(char write_address)						/* I2C start function */
{
	uint8_t status;											/* Declare variable */
	TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);					/* Enable TWI, generate start condition and clear interrupt flag */
	while (!(TWCR & (1<<TWINT)));							/* Wait until TWI finish its current job (start condition) */
	status = TWSR & 0xF8;									/* Read TWI status register with masking lower three bits */
	if (status != TW_START)										/* Check weather start condition transmitted successfully or not? */
	return 0;												/* If not then return 0 to indicate start condition fail */
	TWDR = write_address;									/* If yes then write SLA+W in TWI data register */
	TWCR = (1<<TWEN)|(1<<TWINT);							/* Enable TWI and clear interrupt flag */
	while (!(TWCR & (1<<TWINT)));							/* Wait until TWI finish its current job (Write operation) */
	status = TWSR & 0xF8;									/* Read TWI status register with masking lower three bits */
	if (status == TW_MT_SLA_W_ACK)										/* Check weather SLA+W transmitted & ack received or not? */
	return 1;												/* If yes then return 1 to indicate ack received i.e. ready to accept data byte */
	else if (status == TW_MT_SLA_W_NACK)										/* Check weather SLA+W transmitted & nack received or not? */
	return 2;												/* If yes then return 2 to indicate nack received i.e. device is busy */
	else
	return 3;												/* Else return 3 to indicate SLA+W failed */
}

uint8_t I2C_Repeated_Start(char read_address)				/* I2C repeated start function */
{
	uint8_t status;											/* Declare variable */
	TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);					/* Enable TWI, generate start condition and clear interrupt flag */
	while (!(TWCR & (1<<TWINT)));							/* Wait until TWI finish its current job (start condition) */
	status = TWSR & 0xF8;									/* Read TWI status register with masking lower three bits */
	if (status != TW_REP_START)										/* Check weather repeated start condition transmitted successfully or not? */
	return 0;												/* If no then return 0 to indicate repeated start condition fail */
	TWDR = read_address;									/* If yes then write SLA+R in TWI data register */
	TWCR = (1<<TWEN)|(1<<TWINT);							/* Enable TWI and clear interrupt flag */
	while (!(TWCR & (1<<TWINT)));							/* Wait until TWI finish its current job (Write operation) */
	status = TWSR & 0xF8;									/* Read TWI status register with masking lower three bits */
	if (status == TW_MT_SLA_R_ACK)										/* Check weather SLA+R transmitted & ack received or not? */
	return 1;												/* If yes then return 1 to indicate ack received */
	else if (status == TW_MT_SLA_W_NACK)										/* Check weather SLA+R transmitted & nack received or not? */
	return 2;												/* If yes then return 2 to indicate nack received i.e. device is busy */
	else
	return 3;												/* Else return 3 to indicate SLA+R failed */
}

void I2C_Stop()												/* I2C stop function */
{
	TWCR=(1<<TWSTO)|(1<<TWINT)|(1<<TWEN);					/* Enable TWI, generate stop condition and clear interrupt flag */
	while(TWCR & (1<<TWSTO));								/* Wait until stop condition execution */
}

void I2C_Start_Wait(char write_address)						/* I2C start wait function */
{
	uint8_t status;											/* Declare variable */
	while (1)
	{
		TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);				/* Enable TWI, generate start condition and clear interrupt flag */
		while (!(TWCR & (1<<TWINT)));						/* Wait until TWI finish its current job (start condition) */
		status = TWSR & 0xF8;								/* Read TWI status register with masking lower three bits */
		if (status != TW_START)									/* Check weather start condition transmitted successfully or not? */
		continue;											/* If no then continue with start loop again */
		TWDR = write_address;								/* If yes then write SLA+W in TWI data register */
		TWCR = (1<<TWEN)|(1<<TWINT);						/* Enable TWI and clear interrupt flag */
		while (!(TWCR & (1<<TWINT)));						/* Wait until TWI finish its current job (Write operation) */
		status = TWSR & 0xF8;								/* Read TWI status register with masking lower three bits */
		if (status != TW_MT_SLA_W_ACK )								/* Check weather SLA+W transmitted & ack received or not? */
		{
			I2C_Stop();										/* If not then generate stop condition */
			continue;										/* continue with start loop again */
		}
		break;												/* If yes then break loop */
	}
}

uint8_t I2C_Write(char data)								/* I2C write function */
{
	uint8_t status;											/* Declare variable */
	TWDR = data;											/* Copy data in TWI data register */
	TWCR = (1<<TWEN)|(1<<TWINT);							/* Enable TWI and clear interrupt flag */
	while (!(TWCR & (1<<TWINT)));							/* Wait until TWI finish its current job (Write operation) */
	status = TWSR & 0xF8;									/* Read TWI status register with masking lower three bits */
	if (status == TW_MT_DATA_ACK)										/* Check weather data transmitted & ack received or not? */
	return 0;												/* If yes then return 0 to indicate ack received */
	else if (status == TW_MT_DATA_NACK)										/* Check weather data transmitted & nack received or not? */
	return 1;												/* If yes then return 1 to indicate nack received */
	else
	return 2;												/* Else return 2 to indicate data transmission failed */
}

char I2C_Read_Ack()											/* I2C read ack function */
{
	TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA);					/* Enable TWI, generation of ack and clear interrupt flag */
	while (!(TWCR & (1<<TWINT)));							/* Wait until TWI finish its current job (read operation) */
	return TWDR;											/* Return received data */
}

char I2C_Read_Nack()										/* I2C read nack function */
{
	TWCR=(1<<TWEN)|(1<<TWINT);								/* Enable TWI and clear interrupt flag */
	while (!(TWCR & (1<<TWINT)));							/* Wait until TWI finish its current job (read operation) */
	return TWDR;											/* Return received data */
}

void I2C_Slave_Init(uint8_t slave_address)
{
	TWAR = slave_address;						/* Assign address in TWI address register */
	TWCR = (1<<TWEN) | (1<<TWEA) | (1<<TWINT);	/* Enable TWI, Enable ack generation, clear TWI interrupt */
}

int8_t I2C_Slave_Listen()
{
	while(1)
	{
		uint8_t status;							/* Declare variable */
		while (!(TWCR & (1<<TWINT)));			/* Wait to be addressed */
		status = TWSR & 0xF8;					/* Read TWI status register with masking lower three bits */
		if (status == 0x60 || status == 0x68)	/* Check weather own SLA+W received & ack returned (TWEA = 1) */
		return 0;								/* If yes then return 0 to indicate ack returned */
		else if (status == 0xA8 || status == 0xB0)	/* Check weather own SLA+R received & ack returned (TWEA = 1) */
		return 1;								/* If yes then return 1 to indicate ack returned */
		else if (status == 0x70 || status == 0x78)	/* Check weather general call received & ack returned (TWEA = 1) */
		return 2;								/* If yes then return 2 to indicate ack returned */
		else
		continue;								/* Else continue */
	}
}

int8_t I2C_Slave_Transmit(char data)
{
	uint8_t status;
	TWDR = data;								/* Write data to TWDR to be transmitted */
	TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWEA);		/* Enable TWI and clear interrupt flag */
	while (!(TWCR & (1<<TWINT)));				/* Wait until TWI finish its current job (Write operation) */
	status = TWSR & 0xF8;						/* Read TWI status register with masking lower three bits */
	if (status == TW_SLAVE_ST)							/* Check weather STOP/REPEATED START received */
	{
		TWCR |= (1<<TWINT);						/* If yes then clear interrupt flag & return -1 */
		return -1;
	}
	else if (status == TW_SLAVE_DATA_ACK)							/* Check weather data transmitted & ack received */
	return 0;									/* If yes then return 0 */
	else if (status == TW_SLAVE_DATA_NACK)							/* Check weather data transmitted & nack received */
	{
		TWCR |= (1<<TWINT);						/* If yes then clear interrupt flag & return -2 */
		return -2;
	}
	else if (status == TW_SLAVE_LAST_DATA_ACK)							/* If last data byte transmitted with ack received TWEA = 0 */
	return -3;									/* If yes then return -3 */
	else										/* else return -4 */
	return -4;
}

char I2C_Slave_Receive()
{
	uint8_t status;								/* Declare variable */
	TWCR=(1<<TWEN)|(1<<TWEA)|(1<<TWINT);		/* Enable TWI, generation of ack and clear interrupt flag */
	while (!(TWCR & (1<<TWINT)));				/* Wait until TWI finish its current job (read operation) */
	status = TWSR & 0xF8;						/* Read TWI status register with masking lower three bits */
	if (status == 0x80 || status == 0x90)		/* Check weather data received & ack returned (TWEA = 1) */
	return TWDR;								/* If yes then return received data */
	else if (status == 0x88 || status == 0x98)		/* Check weather data received, nack returned and switched to not addressed slave mode */
	return TWDR;								/* If yes then return received data */
	else if (status == TW_SLAVE_ST)							/* Check weather STOP/REPEATED START received */
	{
		TWCR |= (1<<TWINT);						/* If yes then clear interrupt flag & return 0 */
		return -1;
	}
	else
	return -2;									/* Else return 1 */
}
