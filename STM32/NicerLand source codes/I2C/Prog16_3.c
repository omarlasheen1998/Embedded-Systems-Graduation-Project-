#include <stm32f10x.h>
#include <stdio.h>

void i2c_init(void);
void i2c_waitForReady(void);
void i2c_sendStart(void);
void i2c_sendStop(void);
uint8_t i2c_sendAddrForRead(uint8_t addr);
uint8_t i2c_sendAddrForWrite(uint8_t addr);

void setSquareWave(uint8_t rateSelect);

void getTime(uint8_t *year, uint8_t *month, uint8_t *day, uint8_t *hour, uint8_t *min, uint8_t *sec);

void usart1_init(void);
void usart1_sendByte(unsigned char c);
void usart1_sendStr(char *str);

void delay_ms(uint16_t t);

int main()
{
	char str[30];
	uint8_t year, month, day, hour, min, sec;

	RCC->APB2ENR |= (0xFC)|(1<<14); /* enable clocks for GPIOs and usart1 */
	
	i2c_init();	
	usart1_init();
	
	usart1_sendStr("\n\rDate and Time");
	
	while(1)
	{
		getTime(&year, &month, &day, &hour,&min,&sec);
		sprintf(str,"\n\r%d/%d/%d %d:%d:%d",day,month,year,hour,min,sec);
		usart1_sendStr(str);	
		delay_ms(1000);
	}
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
	}	while(1);
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

void setSquareWave(uint8_t rateSelect)
{
	do{
	i2c_waitForReady();
	i2c_sendStart();
	}while(i2c_sendAddrForWrite(0x68) != 0);
	
	i2c_sendData(0x0E); 
	i2c_sendData((rateSelect&0x03)<<3); 
	i2c_sendStop();	
}

/* The function gets a BCD number and converts it to binary */
uint8_t bcd2int(uint8_t n)
{
	return ((n&0xF0)>>4)*10 + (n&0x0F);
}

void getTime(uint8_t *year, uint8_t *month, uint8_t *day, uint8_t *hour, uint8_t *min, uint8_t *sec)
{
	do{
	i2c_waitForReady(); /* wait while the bus is busy */
	i2c_sendStart();	/* generate start condition */
	}while(i2c_sendAddrForWrite(0x68) != 0); /* send addr. 0x68 for write; repeat if arbitration lost */
	
	i2c_sendData(0x00); /* set register pointer to 0 */
	i2c_sendStop();		/* generate stop condition */
	
	do{
	i2c_waitForReady();	/* wait while the bus is busy */
	i2c_sendStart();	/* generate start condition */
	}while(i2c_sendAddrForRead(0x68) != 0); /* send addr. 0x68 for read; repeat if arbitration lost */

	
	*sec = bcd2int(i2c_readData(0x01)); /* read sec */
	*min = bcd2int(i2c_readData(0x01)); 	/* read min */
	*hour = bcd2int(i2c_readData(0x01));  /* read hour */
	i2c_readData(0x01); 	/* read day of week */
	*day = bcd2int(i2c_readData(0x01)); 	/* read day of month */
	*month = bcd2int(i2c_readData(0x01)); /* read month */
	*year = bcd2int(i2c_readData(0x00)); /* read year (the last read) */
	
	i2c_sendStop();		/* generate stop */
}


void usart1_init()
{
	RCC->APB2ENR |= (1<<14); 	/* enable clock for usart1 */
	
	//USART1 init.
	GPIOA->ODR |= (1<<10);  /* pull-up PA10 */
	GPIOA->CRH = 0x444448B4; /* RX1=input with pull-up, TX1=alt. func output */
	USART1->CR1 = 0x200C;
	USART1->BRR = 7500;	 /* 72MHz/9600bps = 7500	*/
}

void usart1_sendByte(unsigned char c)
{	
	while((USART1->SR&(1<<6)) == 0);  /* wait until the TC flag is set */
	USART1->DR = c;
}

/* the function sends a zero ending string via USART1 */
void usart1_sendStr(char *str)
{
	while(*str != 0)
	{
		usart1_sendByte(*str);
		str++;
	}
}

void delay_ms(uint16_t t)
{
	volatile unsigned long l = 0;
	for(uint16_t i = 0; i < t; i++)
		for(l = 0; l < 6000; l++)
		{
		}
}
