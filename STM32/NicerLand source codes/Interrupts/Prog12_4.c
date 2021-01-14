#include "stm32f10x.h"

/* The program reports the state of PB5 through USART1. */
/* If PB5 is L, it sends L. Otherwise, it sends H. */

void USART1_IRQHandler()	/* USART1 interrupt routine */
{
	USART1->SR &= ~(1<<6); /* clear TC flag */
	if((GPIOB->IDR & (1<<5)) != 0)
		USART1->DR = 'H';	/* send 'H' */
	else
		USART1->DR = 'L';	/* send 'L' */
}

int main()
{
	RCC->APB2ENR |= 0xFC|(1<<14); /* enable GPIO and usart1 clocks */
	
	GPIOB->CRL = 0x44844444; /* PB5 as input */
	GPIOB->ODR |= (1<<5);		/* pull-up PB5 */
	
	/* USART1 init. */
	GPIOA->ODR |= (1<<10);  /* pull-up PA10 */
	GPIOA->CRH = 0x444448B4; /* RX1=input with pull-up, TX1=alt. func output */
	USART1->CR1 = 0x2048;		/* TC int. enable, transmit enable */
	USART1->BRR = 7500;	 /* 72MHz/9600bps = 7500 */

	NVIC_EnableIRQ(USART1_IRQn);	/* USART1 IRQ enable */
	
	while(1)
	{	
	}
}
