#include <stm32f10x.h>

int main()
{
	RCC->APB2ENR |= 0xFC; 	/* enable GPIO clocks */
	RCC->APB1ENR |= (1<<0); 	/* enable TIM2 clock */
	GPIOA->CRL = 0x44444B44; 	/* PA2: alternate func. output */

	TIM2->CCR3 = 200;
	TIM2->CCER = 0x1 << 8; /*CC3P = 0, CC3E = 1 */
	TIM2->CCMR2 = 0x0030;  /* toggle channel 3 */
	TIM2->ARR = 10000-1;
	TIM2->CR1 = 1;
	
	while(1)
	{
	}
}
