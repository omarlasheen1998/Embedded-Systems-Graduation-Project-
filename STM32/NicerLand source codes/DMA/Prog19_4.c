#include <stm32f10x.h>

int main()
{
	char ourMsg[]="ABCDEFGHIJKL";
	
	RCC->AHBENR = (1<<0); /* DMA1 clock enable */
	RCC->APB2ENR |= 0xFC | (1<<14); //enable GPIO clocks

	//USART1 init.
	GPIOA->ODR |= (1<<10);  //pull-up PA10
	GPIOA->CRH = 0x444448B4; /* RX1=input with pull-up, TX1=alt. func output */
	USART1->BRR = 7500;	 /* 72MHz/9600bps = 7500 */
	USART1->CR1 = 0x200C; /* enable usart transmit and receive */
	USART1->CR3 = (1<<7); /* DMA Trans. enable */

	DMA1_Channel4->CPAR = (uint32_t) &USART1->DR; /* to USART1->DR */
	DMA1_Channel4->CMAR = (uint32_t) ourMsg; /* from ourMsg array in mem. */
	DMA1_Channel4->CNDTR = 12;	/* copy 12 bytes */
	DMA1_Channel4->CCR = (1<<7)|(1<<4);	/* mem inc., read from mem */
	DMA1_Channel4->CCR |= 1; /* enable channel 4 */
		
	while(1)
	{		
	}	
}


