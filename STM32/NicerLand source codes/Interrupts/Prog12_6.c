/* In the program, Timer2 and Timer3 are used to generate interrupts. */
/* Timer2 interrupt is generated every second. Its interrupt vector takes around 0.5 second to be executed and during its execution PC13 is low. */
/* Timer3 interrupt is generated every 0.2 second. Its interrupt vector takes around 50ms to be executed and during its execution PB5 is low. */
/* Timer2 and Timer3 have the priority level of 2 and 3, respectively. */

#include <stm32f10x.h>

void delay_ms(uint16_t t);

void TIM2_IRQHandler()
{
	TIM2->SR = 0;	/* clear UIF flag */
	GPIOC->ODR &= ~(1<<13); /* PC13 = low */
	delay_ms(500);	/* wait 0.5 sec */
	GPIOC->ODR |= (1<<13); /* PC13 = high */
}

void TIM3_IRQHandler()
{
	TIM3->SR = 0;	/* clear UIF flag */
	GPIOB->ODR &= ~(1<<5); /* PB3 = low */
	delay_ms(50);	/* wait 50 ms */
	GPIOB->ODR |= (1<<5); /* PB3 = high */
}

int main()
{
	RCC->APB2ENR |= 0xFC; 	/* enable GPIO clocks */
	RCC->APB1ENR |= (1<<0)|(1<<1); 	/* enable TIM2 and TIM3 clocks */
	GPIOB->CRL = 0x44344444;	/* PB3 as output */
	GPIOC->CRH = 0x44344444; 	/* PC13 as output */

	TIM2->PSC = 7200-1;		/* PSC = 7199 */
	TIM2->ARR = 10000-1;
	TIM2->SR = 0;		/* clear the UIF flag */
	TIM2->CR1 = 1; 	/* up counting */
	TIM2->DIER = (1<<0);	/* enable UIE interrupt */	
	NVIC_EnableIRQ(TIM2_IRQn);	/* enable TIM2 interrupt */
	NVIC_SetPriority(TIM2_IRQn,2);	/* Priority level = 2 */
	
	TIM3->PSC = 7200-1;		/* PSC = 7199 */
	TIM3->ARR = 2000-1;
	TIM3->CR1 = 1; 	/* up counting */
	TIM3->DIER = (1<<0);	/* enable UIE interrupt */	
	NVIC_EnableIRQ(TIM3_IRQn);	/* enable TIM3 interrupt */
	NVIC_SetPriority(TIM3_IRQn,3); /* Priority level = 3 */
	
	while(1)
	{	
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
