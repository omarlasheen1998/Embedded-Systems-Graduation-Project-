#include "stm32f10x.h"

void usart1_sendByte(unsigned char c);
uint8_t usart1_recByte(void);

int main()
{
	RCC->APB2ENR |= 0xFC | (1<<14); //enable GPIO clocks
		
	//USART1 init.
	GPIOA->ODR |= (1<<10);  //pull-up PA10
	GPIOA->CRH = 0x444448B4; // RX1=input with pull-up, TX1=alt. func output
	USART1->CR1 = 0x200C;
	USART1->BRR = 7500;	 // 72MHz/9600bps = 7500
	
	GPIOC->CRH = 0x44344444;
	
	while(1)
	{		
		uint8_t c = usart1_recByte();
		switch(c)
		{
			case 'H':
			case 'h':
				GPIOC->ODR |= (1<<13); //PC13 = high
				break;

			case 'L':
			case 'l':
				GPIOC->ODR &= ~(1<<13); //PC13 = low
				break;
			
		}
	}
}

void usart1_sendByte(unsigned char c)
{
	USART1->DR = c;
	
	while((USART1->SR&(1<<6)) == 0);  //wait until the TC flag is set 
	USART1->SR &= ~(1<<6);
}

uint8_t usart1_recByte()
{
	while((USART1->SR&(1<<5)) == 0);	//wait until the RXNE flag is set
	
	return USART1->DR;	
}
