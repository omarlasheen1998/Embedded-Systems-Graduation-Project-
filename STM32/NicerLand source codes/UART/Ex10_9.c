#include "stm32f10x.h"

void usart2_sendByte(unsigned char c);
uint8_t usart2_recByte(void);

int main()
{
	RCC->APB1ENR |= (1<<17); //enable usart2 clock
	RCC->APB2ENR |= 0xFC; //enable GPIO clocks
	
	//USART2 init.
	GPIOA->CRL = 0x44448B44; //RX2=in, TX2=alt. func. Output
	GPIOA->ODR |= (1<<3); // pull-up PA3(RX2)
	USART2->CR1 = 0x200C;
	USART2->BRR = 3750; //36MHz/9600 = 3750	
	
	while(1)
	{	
		uint8_t receivedByte = usart2_recByte();
		usart2_sendByte(receivedByte);
	}
}

uint8_t usart2_recByte()
{
	while((USART2->SR&(1<<5)) == 0);	//wait until the RXNE flag is set
	
	return USART2->DR;	
}

void usart2_sendByte(unsigned char c)
{
	USART2->DR = c;
	
	while((USART2->SR&(1<<6)) == 0);	//wait until the TC flag is set
	USART2->SR &= ~(1<<6);
}
