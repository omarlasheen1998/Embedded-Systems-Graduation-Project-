#include <stm32f10x.h>

void delay(void);

int main()
{
	RCC->APB2ENR = 0xFC; 	/* enable GPIO clocks */
	GPIOC->CRH = 0x44344444; 	/* PC13 as output */
	
	while(1)
	{
		GPIOC->ODR ^= (1<<13); /* toggle PC13 */
		delay();
	}
}

void delay()
{
	SysTick->LOAD = 7199999;		/* STRELOAD = 7,199,999 */
	SysTick->CTRL = 0x05;		    /* Clock source = AHB clock, Enable = 1 */
	while((SysTick->CTRL&(1<<16)) == 0); /* wait until the COUNT flag is set */
	SysTick->CTRL = 0x00;		    /* stop the SysTick timer */
}
