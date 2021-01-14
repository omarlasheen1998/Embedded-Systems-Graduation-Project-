#include <stm32f10x.h>

void delay_ms(uint16_t t);

int main()
{
	RCC->APB2ENR |= 0xFC; /* Enable GPIO ports clocks */
	
	GPIOA->CRH = 0x44444443; /* PA8 as output */

	while(1)
	{		
		GPIOA->ODR ^= (1<<8);	/* toggle PA8 */
		delay_ms(1000);				/* wait 1 second */
	}
}

void delay_ms(uint16_t t)
{
	volatile unsigned long l = 0;
	for(uint16_t i = 0; i < t; i++)
		for(l = 0; l < 6000; l++)
		{
		}
}

