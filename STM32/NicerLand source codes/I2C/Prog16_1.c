#include <stm32f10x.h>

void i2c_init(void);
void i2c_waitForReady(void);
void i2c_sendStart(void);
uint8_t i2c_sendAddrForWrite(uint8_t addr);
uint8_t i2c_sendData(uint8_t data);
void i2c_sendStop(void);

int main()
{
	i2c_init();	
	
	do{
		i2c_waitForReady();
		i2c_sendStart();
	}while(i2c_sendAddrForWrite(0x68) != 0);
	
	i2c_sendData(0x0E); 
	i2c_sendData(0); 
	i2c_sendStop();	
	
	while(1);
}

void i2c_init()
{
	RCC->APB2ENR |= (0xFC); /* enable clocks for GPIOs */
	RCC->APB1ENR |= (1<<21); /* enable clock for I2C1 */
	GPIOB->CRL |= 0xFF000000; /* configure PA6 and PA7 as alt. func. open drain */

	I2C1->CR2 = 0x0020;
	I2C1->CCR = 0x00B4;
	I2C1->TRISE = 37;
	I2C1->CR1 = 1;	/* PE = 1 */
}

void i2c_waitForReady()
{
	while((I2C1->SR2&(1<<1)) != 0); /* check bus busy */
}

void i2c_sendStart()
{
	I2C1->CR1 |= (1<<8); /* start */
	while((I2C1->SR1&(1<<0)) == 0); /* wait for SB */
	int stat = I2C1->SR2;
}

void i2c_sendStop()
{
	I2C1->CR1 |= (1<<9); /* stop */
	while((I2C1->SR2&(1<<0)) != 0); /* wait for becoming slave */
}

uint8_t i2c_sendAddr(uint8_t addr)
{
	I2C1->DR = addr;
	int stat;
	do{
		stat = I2C1->SR1;
		if((stat&(1<<9)) != 0) /* arbitration lost */
			return 1;
		
		if((stat&(1<<1)) != 0) /* address sent */
		{
			stat = I2C1->SR2; /* read SR2 to clear ADDR flag */
			return 0;
		}
	}while(1);
}

uint8_t i2c_sendAddrForRead(uint8_t addr)
{
	return i2c_sendAddr((addr<<1) + 1); /* addr+Read(1) */
}

uint8_t i2c_sendAddrForWrite(uint8_t addr)
{
	return i2c_sendAddr((addr<<1)); /* addr+Write(0) */
}

uint8_t i2c_sendData(uint8_t data)
{
	I2C1->DR = data;
	int stat1;
	do{
		stat1 = I2C1->SR1;
		if((stat1&(1<<7)) != 0) /* TxE = 1 */
			return 0;
	}	while(1);
}

uint8_t i2c_readData(uint8_t ack)
{
	if(ack!= 0)
		I2C1->CR1 |= 1<<10;
	else
		I2C1->CR1 &= ~(1<<10);
	while((I2C1->SR1&(1<<6)) == 0); /* waiting for RxNE */
	return I2C1->DR;
}
