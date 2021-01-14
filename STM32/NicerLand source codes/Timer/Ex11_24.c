/* this program toggles PC13 every 100 pulses */

#include <stm32f10x.h>
#include <stdio.h>

int main()
{
	RCC->APB2ENR |= 0xFC; 	/* enable GPIO clocks and USART1 clock */
	RCC->APB1ENR |= (1<<0); 	/* enable TIM2 clock */
	
	GPIOA->CRL = 0x44444448; 	/* PA0(CH1): input pull-up */
	GPIOA->ODR |= (1<<0);
	
	GPIOC->CRH = 0x44344444; 	/* PC13 as output */

	TIM2->CCMR1 = 0x0000;  /* no filter */
	TIM2->CCER = 0x1 << 1; /*CC0P = 1 (falling) */
	TIM2->SMCR = 0x57;		/* TIM2_CH1 as clock source */
	TIM2->ARR = 100-1;
	TIM2->CR1 = 1;	

	while(1)
	{
		if((TIM2->SR&1) != 0)
		{
			TIM2->SR = 0;
			GPIOC->ODR ^= (1<<13);
		}
	}
}