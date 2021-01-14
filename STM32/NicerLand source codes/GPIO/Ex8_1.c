#include <stm32f10x.h>

void delay_ms(uint16_t t);

int main()
{
	RCC->APB2ENR |= 0xFC;		//ENABLE clocks for GPIOs
	GPIOA->CRL = 0x33333333;	//PA0-PA7 as outputs
	
	while(1)
	{
		int8_t n;
		for(n = 0; n <= 7; n++)	//from 0 to 7
		{
			GPIOA->ODR |= (1<<n);	//make PAn high
			delay_ms(500);
		}
	
		for(n = 7; n >= 0; n --)	//from 7 to 0
		{
			GPIOA->ODR &= ~(1<<n);	//make PAn low
			delay_ms(500);
		}
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
