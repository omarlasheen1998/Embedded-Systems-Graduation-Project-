#include "stm32f10x.h"

void delay_ms(uint16_t t);
void usart1_sendByte(unsigned char c);

int main()
{
	RCC->APB2ENR |= 0xFC | (1<<14); //enable GPIO clocks
		
	//USART1 init.
	GPIOA->ODR |= (1<<10);  //pull-up PA10
	GPIOA->CRH = 0x444448B4; // RX1=input with pull-up, TX1=alt. func output
	USART1->CR1 = 0x200C;
	USART1->BRR = 7500;	 // 72MHz/9600bps = 7500
	
	while(1)
	{		
		usart1_sendByte('H');
		usart1_sendByte('i');
		usart1_sendByte('\n'); //go to new line
		usart1_sendByte('\r'); //carrier return
		
		delay_ms(1000);	//wait 1 second
	}
}

void usart1_sendByte(unsigned char c)
{
	USART1->DR = c;
	
	while((USART1->SR&(1<<6)) == 0);  //wait until the TC flag is set 
	USART1->SR &= ~(1<<6);
}

void delay_ms(uint16_t t)
{
	volatile unsigned long l = 0;
	for(uint16_t i = 0; i < t; i++)
		for(l = 0; l < 6000; l++)
		{
		}
}
