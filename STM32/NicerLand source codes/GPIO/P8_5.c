#include <stm32f10x.h>

void delay_ms(uint16_t t);

int main() 
{
	RCC->APB2ENR |= 0xFC;		/* Enable clocks for GPIOs */
	GPIOC->CRH = 0x44344444;	/* PC13 as output */
	while(1) 
	{
		GPIOC->BRR = 1<<13;		/* make the pin low */
		delay_ms(500);			/* wait 0.5 sec. */
		GPIOC->BSRR = 1<<13;		/* make the pin high */
		delay_ms(500);			/* wait 0.5 sec. */
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
