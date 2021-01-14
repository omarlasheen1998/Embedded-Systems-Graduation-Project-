#include <stm32f10x.h>

void delay_ms(uint16_t t);

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
	
	TIM2->EGR = 1; /* UG = 1 (generate update) */
	TIM2->CR1 |= 0x01; /* timer enable (CEN = 1) */
		
	while(1)
	{
		/* change the dc from 0 to 100.0% */
		for(uint16_t d = 0; d <= 1000; d+= 20) 
		{
			TIM2->CCR1 = d; 
			delay_ms(50);
		}
	}
}

void delay_ms(uint16_t t)
{
	for(int i = 0; i < t; i++)
	{
		for(volatile uint16_t a = 0; a < 6000; a++)
		{}
	}
}
