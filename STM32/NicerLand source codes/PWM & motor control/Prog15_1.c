#include <stm32f10x.h>

int main()
{
	RCC->APB2ENR |= 0xFC; 	/* enable GPIO clocks */
	RCC->APB1ENR |= (1<<0); 	/* enable TIM2 clock */
	GPIOA->CRL = 0x4444444B; 	/* PA0: alternate func. output */

	TIM2->CCER = 0x1 << 0; /* CC1P = 0, CC1E = 1 */
	TIM2->CCMR1 = 0x0068;  /* OC1M=PWM1, OC1PE=1 */
	TIM2->CR1 = 0x80;	/* Auto reload preload enable */
	
	TIM2->PSC = 720-1;	/* prescaler = 720 */
	TIM2->ARR = 1000-1;	/* ARR = 999 */
	TIM2->CCR1 = 1000;	/* duty cycle = (300/1000)*100 */
	
	TIM2->EGR = 1; /* UG = 1 (generate update) */
	TIM2->CR1 |= 0x01; /* timer enable (CEN = 1) */
	
	while(1)
	{
	}
}
