#include <stm32f10x.h>

void delay_us(uint16_t t);

int main()
{
	RCC->APB2ENR |= 0xFC;		/* enable clocks for GPIOs */
	GPIOA->CRL = 0x33333333;	/* PA0-PA7 as outputs */
	
	int8_t n = 0;
	while(1)
	{
			GPIOA->ODR = n;	/* copy n into PORTA to be converted */
			n ++;			/* increment n */
			delay_us(10);	
	}	
}

void delay_us(uint16_t t)
{
	for(int i = 0; i < t; i++)
	{
		for(volatile uint16_t a = 0; a < 6; a++)
		{}
	}
}
