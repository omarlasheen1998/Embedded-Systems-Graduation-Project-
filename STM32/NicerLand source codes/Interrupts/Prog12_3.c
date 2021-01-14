#include "stm32f10x.h"

/* The program receives a character through USART1. */
/* If the character is L, it makes the PC13 Low. If it is H, PC13 becomes High. */

void USART1_IRQHandler()	/* USART1 interrupt routine */
{
	uint8_t c = USART1->DR;	/* get received data */
	
	if((c == 'H')||(c == 'h'))
		GPIOC->ODR |= (1<<13);	/* make PC13 high */
	else
		if((c == 'L')||(c == 'l'))
			GPIOC->ODR &= ~(1<<13);	/* make PC13 low */
}

int main()
{
	RCC->APB2ENR |= 0xFC|(1<<14); /* enable GPIO and usart1 clocks */
	
	GPIOC->CRH = 0x44344444; /* PC13 as output */
	
	/* USART1 init. */
	GPIOA->ODR |= (1<<10);  /* pull-up PA10 */
	GPIOA->CRH = 0x444448B4; /* RX1=input with pull-up, TX1=alt. func output */
	USART1->CR1 = 0x2024;		/* receive int. enable, receive enable */
	USART1->BRR = 7500;	 /* 72MHz/9600bps = 7500 */

	NVIC_EnableIRQ(USART1_IRQn);	/* USART1 IRQ enable */
	
	while(1)
	{			

	}
}
