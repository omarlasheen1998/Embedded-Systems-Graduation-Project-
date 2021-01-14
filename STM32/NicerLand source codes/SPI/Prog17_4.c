#include <stm32f10x.h>

void spi1_init(void);
uint8_t spi1_transfer(uint8_t d);

void max7219_send(uint8_t cmd, uint8_t data);

int main()
{
	RCC->APB2ENR |= 0xFC; 	/* enable clocks for GPIO */
	
	spi1_init(); /* initialize the SPI module */
	
	max7219_send(0x09, 0x02);	/* enable decoding for digit2 and disable for digit1  */
	max7219_send(0x0B, 1);		/* 2 (1+1) digits */
	max7219_send(0x0C, 0x01);	/* turn on */

	max7219_send(0x01, 0x3E);	/* show U on digit 1 */
	max7219_send(0x02, 2);	/* show 2 on digit 2 */

	while(1)
	{
	}
}

/* The function initializes the SPI module */
void spi1_init()
{
	RCC->APB2ENR |= 0xFC|(1<<12); 	/* enable clocks for GPIO and SPI1 */
	GPIOA->CRL = 0xB4B34444; 	/* MOSI (PA7) and SCK(PA5): alt. func. out, PA4: output for CS */	
	SPI1->CR1 = 0x35C;	/* SPE = 1, BR = 3, FFD = 0, SSI and SSM = 1 */
}

/* The function sends a byte of data through SPI */
/* argument d: the byte to be sent */
/* return value: the received data */
uint8_t spi1_transfer(uint8_t d)
{
	SPI1->DR = d;	/* send the contents of d */
	while((SPI1->SR&(1<<0)) == 0);	/* wait until RXNE is set */
	return SPI1->DR;	/* return the received data */ 
}

void max7219_send(uint8_t cmd, uint8_t data)
{
	GPIOA->BRR = (1<<4);	/* Enable Chip Select */
	spi1_transfer(cmd);
	spi1_transfer(data);
	GPIOA->BSRR = (1<<4);	/* Disable Chip Select */
}
