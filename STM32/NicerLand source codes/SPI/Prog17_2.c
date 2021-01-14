#include <stm32f10x.h>
#include <stdio.h>

void usart1_init(void);
void usart1_sendByte(unsigned char c);
void usart1_sendInt(unsigned int i);

void spi1_init(void);
uint8_t spi1_transfer(uint8_t d);

int main()
{
	RCC->APB2ENR |= 0xFC; 	/* enable clocks for GPIO */
	RCC->APB2ENR |= (1<<14); 	/* enable clock for usart1 */
	
	spi1_init();
	usart1_init();

	/*--- make the SS pin of the slave low if needed ---*/
	
	for(char c = 'A'; c <= 'Z'; c++)
		usart1_sendByte(spi1_transfer(c));
	
	/*--- make the SS pin high ---*/

	while(1)
	{
	}
}

void spi1_init()
{
	RCC->APB2ENR |= 0xFC|(1<<12); 	/* enable clocks for GPIO and SPI1 */
	GPIOA->CRL = 0xB4B44444; 	/* MOSI (PA7) and SCK(PA5): alt. func. out, MISO (PA6): input */	
	SPI1->CR1 = 0x35C;	/* SPE = 1, BR = 3, FFD = 0, SSI and SSM = 1 */
}

uint8_t spi1_transfer(uint8_t d)
{
	SPI1->DR = d;	/* send the contents of d */
	while((SPI1->SR&(1<<0)) == 0);	/* wait until RXNE is set */
	return SPI1->DR;	/* return the received data */ 
}

void usart1_init()
{
	//USART1 init.
	GPIOA->ODR |= (1<<10);  //pull-up PA10
	GPIOA->CRH = 0x444448B4; // RX1=input with pull-up, TX1=alt. func output
	USART1->CR1 = 0x200C;
	USART1->BRR = 7500;	 // 72MHz/9600bps = 7500	
}

void usart1_sendByte(unsigned char c)
{	
	while((USART1->SR&(1<<6)) == 0);  //wait until the TC flag is set 
	USART1->DR = c;
}

/* the function sends a zero ending string through USART1 */
void usart1_sendStr(char *str)
{
	while(*str != 0)
	{
		usart1_sendByte(*str);
		str++;
	}
}

/* The function sends a number through USART1 */
void usart1_sendInt(unsigned int i)
{
	char str[10];
	sprintf(str,"%d",i);
	
	usart1_sendStr(str);	
}
