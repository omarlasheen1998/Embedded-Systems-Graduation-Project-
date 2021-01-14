/* This program toggles PC13 using interrupt, every second. */
#include <stm32f10x.h>

void TIM2_IRQHandler()
{
	TIM2->SR = 0;	/* clear UIF flag */
	GPIOC->ODR ^= (1<<13); /* toggle PC13 */
}

int main()
{
	RCC->APB2ENR |= 0xFC; 	/* enable GPIO clocks */
	RCC->APB1ENR |= (1<<0); 	/* enable TIM2 clock */
	GPIOC->CRH = 0x44344444; 	/* PC13 as output */

	TIM2->PSC = 7200-1;		/* PSC = 7199 */
	TIM2->ARR = 10000-1;
	TIM2->SR = 0;		/* clear the UIF flag */
	TIM2->CR1 = 1; 	/* up counting */
	TIM2->DIER = (1<<0);	/* enable UIE interrupt */	
	NVIC_EnableIRQ(TIM2_IRQn);	/* enable TIM2 interrupt */
	
	GPIOB->CRL = 0x44344444;	/* PB5 as output */
	
	while(1)
	{
		GPIOB->ODR ^= (1<<5); /* toggle PB5 */
	}
}
