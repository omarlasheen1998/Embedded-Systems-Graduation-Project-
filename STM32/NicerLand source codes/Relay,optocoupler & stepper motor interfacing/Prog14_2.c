#include <stm32f10x.h>

void delay_ms(uint16_t t);

int main()
{
	const uint8_t steps[4] ={0x09, 0x0C, 0x06, 0x03};
	RCC->APB2ENR |= 0xFC; /* Enable GPIO ports clocks */
	
	GPIOA->CRL = 0x44443333; /* PA0-PA3 as outputs */
	
	GPIOB->CRL = 0x44444448; /* PB0 as input with pull-up */
	GPIOB->ODR |= (1<<0); 	 /* pull-up PB0 */
	
	uint8_t n = 0;
	while(1)
	{
		GPIOA->ODR = steps[n];	/* go to next step */

		if((GPIOB->IDR&(1<<0)) != 0) /* is PB0 high */
		{
			if(n >= 3)
				n = 0;
			else
				n++;		/* clockwise */
		}
		else
		{
			if(n == 0)
				n = 3;
			else
				n--;	/* counter clockwise */
		}	
			
		delay_ms(100);				/* wait 100 ms */
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
