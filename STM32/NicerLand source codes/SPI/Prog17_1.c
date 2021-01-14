#include <stm32f10x.h>

void spi1_init(void);
uint8_t spi1_transfer(uint8_t d);

int main()
{
	RCC->APB2ENR |= 0xFC; 	/* enable clocks for GPIO */
	
	spi1_init(); /* initialize the SPI module */
	
	/*--- make the SS pin of the slave low if needed ---*/
	
	for(char c = 'A'; c <= 'Z'; c++)
		spi1_transfer(c); /* send c through SPI */
	
	/*--- make the SS pin high ---*/

	while(1)
	{
	}
}

/* The function initializes the SPI module */
void spi1_init()
{
	RCC->APB2ENR |= 0xFC|(1<<12); 	/* enable clocks for GPIO and SPI1 */
	GPIOA->CRL = 0xB4B44444; 	/* MOSI (PA7) and SCK(PA5): alt. func. out, MISO (PA6): input */	
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
