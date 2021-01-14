#include "stm32f10x.h"

/* The program receives a character through USART2. */
/* If the character is L, it makes the PC13 Low. If it is H, PC13 becomes High. */

void USART2_IRQHandler()	/* USART2 interrupt routine */
{
	uint8_t c = USART2->DR;	/* get received data */
	
	if((c == 'H')||(c == 'h'))
		GPIOC->ODR |= (1<<13);	/* make PC13 high */
	else
		if((c == 'L')||(c == 'l'))
			GPIOC->ODR &= ~(1<<13);	/* make PC13 low */
}

int main()
{
	RCC->APB1ENR |= (1<<17); /* enable usart2 clock */
	RCC->APB2ENR |= 0xFC; /* enable GPIO clocks */
	
	GPIOC->CRH = 0x44344444; /* PC13 as output */
	
	/* USART2 init. */
	GPIOA->CRL = 0x44448B44; /* RX2=in, TX2=alt. func. Output */
	GPIOA->ODR |= (1<<3); /* pull-up PA3(RX2) */
	USART2->CR1 = 0x2024;
	USART2->BRR = 3750; /* 36MHz/9600 = 3750 */

	NVIC_EnableIRQ(USART2_IRQn);	/* USART2 IRQ enable */
	
	while(1)
	{			
	}
}

