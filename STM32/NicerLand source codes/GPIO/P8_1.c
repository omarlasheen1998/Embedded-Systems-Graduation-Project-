#include "stm32f10x.h"

void delay_ms(uint16_t t);

int main()
{
	RCC->APB2ENR |= 0xFC; //Enable the clocks for GPIO ports 
	
	GPIOA->CRL = 0x33333333; //PA0 to PA7 as outputs
	GPIOA->CRH = 0x33333333; //PA8 to PA15 as outputs

	while(1)
	{		
		GPIOA->ODR = 0x0000; //make all the pins of Port A low
		delay_ms(1000);	//wait 1000ms
		GPIOA->ODR = 0xFFFF; //make all the pins of Port A high
		delay_ms(1000);	//wait 1000ms
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
