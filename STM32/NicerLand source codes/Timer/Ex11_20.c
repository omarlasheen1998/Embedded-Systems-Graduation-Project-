#include <stm32f10x.h>

int main()
{
	RCC->APB2ENR |= 0xFC; 	/* enable GPIO clocks */
	RCC->APB1ENR |= (1<<0); 	/* enable TIM2 clock */
	GPIOA->CRL = 0x44444BB4; 	/* PA2(CH3), PA1(CH2): alternate func. output */

	TIM2->CCR2 = 1000;
	TIM2->CCR3 = 3000;
	TIM2->CCER = (0x1<<8)|(0x1<<4); /*CC3P = 0, CC3E = 1, CC2E = 1 */
	TIM2->CCMR1 = 0x3000;  /* toggle channel 2 */
	TIM2->CCMR2 = 0x0030;  /* toggle channel 3 */
	TIM2->PSC = 7200-1;
	TIM2->ARR = 10000-1;
	TIM2->CR1 = 1;
	
	while(1)
	{
	}
}
