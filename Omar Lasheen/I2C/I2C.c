/*
 * CFile1.c
 *
 * Created: 5/21/2020 2:09:29 PM
 *  Author: Lasheen
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <math.h>
#include "I2C.h"

#define BITRATE(TWSR)	((F_CPU/SCL_CLK)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1)))))

unsigned char I2C_Read_Ack();
unsigned char I2C_Read_Nack();

void I2C_Master_Init(int SCL_CLK)
{
	
TWBR = BITRATE(TWSR=0x00);

}

unsigned char I2C_Start(unsigned char write_address)
{
	/* I2C start function */
	uint8_t status;		/* Declare variable */
	TWCR=(1<<TWSTA)|(1<<TWEN)|(1<<TWINT); /* Enable TWI, generate START */
	while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
	status=TWSR&0xF8;		/* Read TWI status register */
	if(status!=TW_START)		/* Check weather START transmitted or not? */
	return 0;			/* Return 0 to indicate start condition fail */
	TWDR=(write_address<<1)&0xFE;		/* Write SLA+W in TWI data register */
	TWCR=(1<<TWEN)|(1<<TWINT);	/* Enable TWI & clear interrupt flag */
	while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
	status=TWSR&0xF8;		/* Read TWI status register */
	if(status==TW_MT_SLA_W_ACK)		/* Check for SLA+W transmitted &ack received */
	return 1;			/* Return 1 to indicate ack received */
	else if(status==TW_MT_SLA_W_NACK)		/* Check for SLA+W transmitted &nack received */
	return 2;			/* Return 2 to indicate nack received */
	else
	return 3;			/* Else return 3 to indicate SLA+W failed */
}

unsigned char I2C_Repeated_Start(unsigned char read_address)
{
	 /* I2C repeated start function */
	
		unsigned char status;		/* Declare variable */
		TWCR=(1<<TWSTA)|(1<<TWEN)|(1<<TWINT);/* Enable TWI, generate start */
		while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
		status=TWSR&0xF8;		/* Read TWI status register */
		if(status!=TW_REP_START)		/* Check for repeated start transmitted */
		return 0;			/* Return 0 for repeated start condition fail */
		TWDR=(read_address<<1)|0x01;		/* Write SLA+R in TWI data register */
		TWCR=(1<<TWEN)|(1<<TWINT);	/* Enable TWI and clear interrupt flag */
		while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
		status=TWSR&0xF8;		/* Read TWI status register */
		if(status == TW_MT_SLA_R_ACK)		/* Check for SLA+R transmitted &ack received */
		return 1;			/* Return 1 to indicate ack received */
		else if(status == TW_MT_SLA_R_NACK)	/* Check for SLA+R transmitted &nack received */
		return 2;			/* Return 2 to indicate nack received */
		else
		return 3;			/* Else return 3 to indicate SLA+W failed */
	
}
unsigned char I2C_Write(unsigned char data)	
{
	/* I2C write function */
	
	unsigned char status;		/* Declare variable */
	TWDR=data;			/* Copy data in TWI data register */
	TWCR=(1<<TWEN)|(1<<TWINT);	/* Enable TWI and clear interrupt flag */
	while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
	status=TWSR&0xF8;		/* Read TWI status register */
	if(status == TW_MT_DATA_ACK)		/* Check for data transmitted &ack received */
	return 0;			/* Return 0 to indicate ack received */
	else if(status == TW_MT_DATA_NACK)		/* Check for data transmitted &nack received */
	return 1;			/* Return 1 to indicate nack received */
	else
	return 2;			/* Else return 2 for data transmission failure */
}

unsigned char I2C_Read_Ack()		
{
	/* I2C read ack function */
	TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA); /* Enable TWI, generation of ack */
	while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
	return TWDR;			/* Return received data */
}

unsigned char I2C_Read_Nack()		/* I2C read nack function */
{
	TWCR=(1<<TWEN)|(1<<TWINT);	/* Enable TWI and clear interrupt flag */
	while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
	return TWDR;		       /* Return received data */
}

void I2C_Stop()			/* I2C stop function */
{
	TWCR=(1<<TWSTO)|(1<<TWINT)|(1<<TWEN);/* Enable TWI, generate stop */
	while(TWCR&(1<<TWSTO));	/* Wait until stop condition execution */
}

void I2C_Slave_Init(unsigned char slave_address)
{
	TWAR=(slave_address<<1)|(1<<TWGCE);		/* Assign Address in TWI address register */
	TWCR=(1<<TWEN)|(1<<TWEA)|(1<<TWINT);/* Enable TWI, Enable ack generation */
}

unsigned char I2C_Slave_Listen()
{
	while(1)
	{
		char status;			/* Declare variable */
		while(!(TWCR&(1<<TWINT)));	/* Wait to be addressed */
		status=TWSR&0xF8;		/* Read TWI status register */
		if(status==0x60||status==0x68)	/* Own SLA+W received &ack returned */
		return 0;			
		else if(status==0xA8||status==0xB0)	/* Own SLA+R received &ack returned */
		return 1;		
		else if(status==0x70||status==0x78)	/* General call received &ack returned */
		return 2;			/* Return 1 to indicate ack returned */
		else
		continue;			/* Else continue */
	}
}

char I2C_Slave_Transmit(unsigned char data){

	  char status;
	  TWDR=data;			/* Write data to TWDR to be transmitted */
	  TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA);/* Enable TWI & clear interrupt flag */
	  while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
	  status=TWSR&0xF8;		/* Read TWI status register */
	  if(status==TW_SLAVE_ST)		/* Check for STOP/REPEATED START received */
	  {
		  TWCR|=(1<<TWINT);	/* Clear interrupt flag & return -1 */
		  return -1;
	  }
	  else if(status == TW_SLAVE_DATA_ACK)		/* Check for data transmitted &ack received */
	  return 0;			/* If yes then return 0 */
	  else if(status == TW_SLAVE_DATA_NACK)		/* Check for data transmitted &nack received */
	  {
		  TWCR|=(1<<TWINT);	/* Clear interrupt flag & return -2 */
		  return -2;
	  }
	  else if(status == TW_SLAVE_LAST_DATA_ACK)		/* Last byte transmitted with ack received //this is an error as last byte should transmit with nack */
	  return -3;			/* If yes then return -3 */
	  else			/* else return -4 */
	  return -4;
	
}

char I2C_Slave_Receive()
{
	char status;		/* Declare variable */
	TWCR=(1<<TWEN)|(1<<TWEA)|(1<<TWINT);/* Enable TWI & generation of ack */
	while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
	status=TWSR&0xF8;		/* Read TWI status register */
	if(status==0x80||status==0x90)/* Check for data received &ack returned */
	return TWDR;		/* If yes then return received data */

	/* Check for data received, nack returned & switched to not addressed slave mode */
	if(status==0x88||status==0x98)
	return TWDR;		/* If yes then return received data */
	if(status==TW_SLAVE_ST)		/* Check wether STOP/REPEATED START */
	{
		TWCR|=(1<<TWINT);	/* Clear interrupt flag & return -1 */
		return -1;
	}
	else
	return -2;			/* Else return -2 */
}

char I2C_Read(unsigned char no)
{
	
	static unsigned char i=0;
	
	if(i<no)
	{
		i++;
		return I2C_Read_Ack();
	}
	
	else if(i==(no-1))
	{
		i=0;
		return I2C_Read_Nack();
	}

return (-127);	

}
