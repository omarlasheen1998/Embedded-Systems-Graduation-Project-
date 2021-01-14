/* The program checks if any key is pressed or not */
/* It turns on the green led (PC13=0) if a key is pressed. */
/* PB15-PB12 as rows (outputs) */
/* PB6-PB9 as columns (inputs) */

#include <stm32f10x.h>

void delay_us(uint16_t t);

uint8_t keypad_kbhit(void);

int main()
{
	RCC->APB2ENR |= 0xFC; /* Enable clocks for GPIO ports */	
	/* init keypad pins */
	GPIOB->CRL = 0x88444444; /* PB6 and PB7 as inputs */
	GPIOB->CRH = 0x33334488; /* PB15-PB12 as outputs, PB8 and PB9 as inputs */
	GPIOB->ODR |= (0xF<<6); /* pull-up PB9-PB6 */
	
	GPIOC->CRH = 0x44344444; /* PC13 as output */
	
	while(1)
	{
		if(keypad_kbhit())
			GPIOC->BRR = (1<<13); /* PC13 = low (LED on) */
		else
			GPIOC->BSRR = (1<<13); /* PC13 = high (LED off) */			
	}
}

/* The function checks if a key is pressed or not */
/* Returns: 0: Not pressed, 1: Pressed */
uint8_t keypad_kbhit()
{
	GPIOB->BRR = (0x0F<<12); /* make all rows zeros */
	delay_us(1);
	if(((GPIOB->IDR>>6)&0xF) == 0xF) /* if all cols are high */
		return 0;
	else
		return 1;
}

void delay_us(uint16_t t)
{
	volatile unsigned long l = 0;
	for(uint16_t i = 0; i < t; i++)
		for(l = 0; l < 6; l++)
		{
		}
}
