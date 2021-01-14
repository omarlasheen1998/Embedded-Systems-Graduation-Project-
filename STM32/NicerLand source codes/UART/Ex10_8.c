#include "stm32f10x.h"

void delay_ms(uint16_t t);
void usart2_sendByte(unsigned char c);

int main()
{
	RCC->APB1ENR |= (1<<17); //enable usart2 clock
	RCC->APB2ENR |= 0xFC; //enable GPIO clocks
	
	GPIOB->CRL = 0x44844444;  // enable pull-up resistor
	GPIOB->ODR |= (1<<5); 	 // pull-up PB5
	//USART2 init.
	GPIOA->CRL = 0x44448B44; //RX2=in, TX2=alt. func. Output
	GPIOA->ODR |= (1<<3); // pull-up PA3(RX2)
	USART2->CR1 = 0x200C;
	USART2->BRR = 3750; //36MHz/9600 = 3750	
	
	while(1)
	{		
		if((GPIOB->IDR&(1<<5)) == 0) //is PB5 low?
			usart2_sendByte('L');
		else
			usart2_sendByte('H'); 
	}
}

void usart2_sendByte(unsigned char c)
{
	USART2->DR = c;
	
	while((USART2->SR&(1<<6)) == 0);	//wait until the TC flag is set
	USART2->SR &= ~(1<<6);
}
