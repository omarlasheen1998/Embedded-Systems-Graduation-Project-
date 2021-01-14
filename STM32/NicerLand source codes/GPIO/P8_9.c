#include <stm32f10x.h>

void delay_ms(uint16_t t);

int main()
{
	RCC->APB2ENR |= 0xFC; /* Enable GPIO ports clocks */
	GPIOC->CRH = 0x44344444; /* PC13 as output */

	GPIOA->CRL = 0x44444844; /* PA2 as input with pull-up */
	GPIOA->ODR |= (1<<2);	/* pull-up PA2 */

	while(1)
	{	
		if((GPIOA->IDR&(1<<2)) == 0) /* is PA2 low? */
			GPIOC->ODR ^= (1<<13); /* toggle PC13 */
		else
			GPIOC->ODR &= ~(1<<13); 
		delay_ms(500);
	}
}

//The following delay is tested with Keil and 72MHz
void delay_ms(uint16_t t)
{
	volatile unsigned long l = 0;
	for(uint16_t i = 0; i < t; i++)
		for(l = 0; l < 6000; l++)
		{
		}
}
