/* Using sysTick, it toggles PC13 every second */
#include <stm32f10x.h>

void SysTick_Handler()
{
		GPIOC->ODR ^= (1<<13); /* toggle PC13 */	
}

int main()
{
	RCC->APB2ENR = 0xFC; /* enable GPIO clocks */
	GPIOC->CRH = 0x44344444; /* PC13 as output */

	SysTick->LOAD = 9000000-1;		/* STRELOAD = (72,000,000/8)-1 */
	SysTick->CTRL = 0x03;		    /* Clock = AHB clock/8, int. enable, Enable = 1 */
	
	while(1)
	{
	}
}