#include <stm32f10x.h>

int main()
{
	RCC->APB2ENR |= 0xFC; /* Enable GPIO ports clocks */
	
	GPIOB->CRH = 0x44444444; /* PB8-PB15 as inputs */
	GPIOC->CRH = 0x44344444; /* PC13 as output */

	while(1)
	{		
		if((GPIOB->IDR & (1<<10)) != 0) /* is PB10 high	*/
				GPIOC->ODR |= (1 << 13); /* make PC13 high */
		else
				GPIOC->ODR &= ~(1 << 13); /* make PC13 low */
	}
}
