#include <stm32f10x.h>

void delay_ms(uint16_t t);

int main()
{
	RCC->APB2ENR |= 0xFC; //Enable GPIO ports clocks 
	
	GPIOC->CRH = 0x44344444; //PC13 as output

	while(1)
	{		
		GPIOC->ODR ^= (1<<13); //toggle PC13
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
