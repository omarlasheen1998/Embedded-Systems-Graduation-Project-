#include "stm32f10x.h"

void usart3_sendByte(unsigned char c);
uint8_t usart3_recByte(void);

int main()
{
	RCC->APB1ENR |= (1<<18); //enable usart3 clock
	RCC->APB2ENR |= 0xFC; //enable GPIO clocks
	
	//USART3 init.
	GPIOB->CRH = 0x44448B44; //RX2=in, TX2=alt. func. Output
	GPIOB->ODR |= (1<<11); // pull-up PB11(RX3)
	USART3->CR1 = 0x200C;
	USART3->BRR = 3750; //36MHz/9600 = 3750	
	
	while(1)
	{	
		uint8_t c = usart3_recByte();
		
		if((c >= 'a')&&(c <= 'z')) //is a small letter?
			c = c - 32; // to capital letters
		
		usart3_sendByte(c);
	}
}

uint8_t usart3_recByte()
{
	while((USART3->SR&(1<<5)) == 0);	//wait until the RXNE flag is set
	
	return USART3->DR;	
}

void usart3_sendByte(unsigned char c)
{
	USART3->DR = c;
	
	while((USART3->SR&(1<<6)) == 0);	//wait until the TC flag is set
	USART3->SR &= ~(1<<6);
}
