#include <stm32f10x.h>

void delay_ms(uint16_t t);

void EXTI4_IRQHandler()	/* interrupt handler for EXTI4 */
{
	EXTI->PR = (1<<4);		/* clear the Pending flag */
	GPIOC->ODR ^= 1<<13;	/* toggle PC13 */
}

int main()
{
	RCC->APB2ENR |= (0xFC | 1); /* Enable clocks for GPIO ports and AFIO */
	
	GPIOB->CRL = 0x44484444; /* PB4 as input */
	GPIOB->ODR |= (1<<4);			/* pull-up PB4 */
	GPIOC->CRH = 0x44344444; /* PC13 as output */
	
	AFIO->EXTICR[1] = 1<<0; /* EXTI2 = 1 (selects PB4 for line 4) */
	
	EXTI->FTSR = (1<<4);	/* int. on falling edge */
	
	EXTI->IMR = (1<<4); /* enable interrupt EXTI4 */
	NVIC_EnableIRQ(EXTI4_IRQn);	/* enable the EXTI4 interrupt */
	
	GPIOA->CRL = 0x44444344; /* PA2 as output */
	
	while(1)
	{
		GPIOA->ODR ^= (1<<2);	/* toggle PA2 */
		delay_ms(1000);		/* wait 1 second */
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
