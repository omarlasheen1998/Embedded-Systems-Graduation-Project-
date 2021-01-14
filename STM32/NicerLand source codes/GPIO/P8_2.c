#include <stm32f10x.h>

void delay_ms(uint16_t t);

int main()
{
	RCC->APB2ENR |= 0xFC; /* Enable clocks forGPIO ports */
	GPIOA->CRL = 0x44444344; /* PA2 as output */
	while(1)
	{		
		GPIOA->ODR ^= (1<<2); /* toggle PA2 */
		delay_ms(1000);
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
