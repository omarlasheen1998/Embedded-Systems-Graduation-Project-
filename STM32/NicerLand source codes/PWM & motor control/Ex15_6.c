/* The program uses TIM3_CH2 (PA7) */

#include <stm32f10x.h>

int main()
{
	RCC->APB2ENR |= 0xFC; 	/* enable GPIO clocks */
	RCC->APB1ENR |= (1<<1); 	/* enable TIM3 clock */
	GPIOA->CRL = 0xB4444444; 	/* PA7: alternate func. output */

	TIM3->CCER = 0x1 << 4; /* CC2P = 0, CC2E = 1 */
	TIM3->CCMR1 = 0x6800;  /* OC2M=PWM1, OC2PE=1 */
	TIM3->CR1 = 0x80|(1<<5);	/* Auto reload preload enable, up down counting mode */
	
	TIM3->PSC = 0;	/* prescaler = 1 */
	TIM3->ARR = 32000;	/* ARR = 32000 */
	TIM3->CCR2 = 25200;	/* duty cycle = (25200/32000)*100 */
	
	TIM3->EGR = 1; /* UG = 1 (generate update) */
	TIM3->CR1 |= 0x01; /* timer enable (CEN = 1) */
	
	while(1)
	{
	}
}
