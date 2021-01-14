#include <stm32f10x.h>

int main() 
{
	RCC->APB2ENR |= 0xFC; /* Enable GPIO ports clocks */
	
	GPIOA->CRL = 0x33333333; /* PA0-PA7 as outputs */
	GPIOA->CRH = 0x33333333; /* PA8-PA15 as outputs */
	GPIOB->CRL = 0x44444444; /* PB0-PB7 as inputs */
	GPIOB->CRH = 0x44444444; /* PB8-PB15 as inputs */

	while(1)
	{		
		GPIOA->ODR = GPIOB->IDR; /* read from port B and write to port A */
	}
}

