#include <stm32f10x.h>

void delay(void);

int main()
{
	RCC->APB2ENR |= 0xFC; 	/* enable GPIO clocks */
	RCC->APB1ENR |= (1<<0); 	/* enable TIM2 clock */
	GPIOC->CRH = 0x44344444; 	/* PC13 as output */
	
	while(1)
	{
		GPIOC->ODR ^= (1<<13); /* toggle PC13 */
		delay();
	}
}

void delay()
{
	TIM2->PSC = 7200-1;
	TIM2->ARR = 10000-1;
	TIM2->SR = 0;	
	TIM2->CR1 = 1;
	while((TIM2->SR & 1) == 0);
	TIM2->CR1 = 0;
}
