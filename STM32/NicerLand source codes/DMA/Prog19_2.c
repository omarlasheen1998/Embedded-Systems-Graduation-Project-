#include <stm32f10x.h>

volatile char transmitComplete = 0;

int main()
{
	char source[10]="ABCDEFGHI";
	char dest[10];
	
	RCC->AHBENR = RCC_AHBENR_DMA1EN;
	
	DMA1_Channel1->CPAR = (uint32_t) source; /* CPAR = the addr. of source array in the mem. */
	DMA1_Channel1->CMAR = (uint32_t) dest; /* CMAR = the addr. of dest array in the mem. */
	DMA1_Channel1->CNDTR = 10;	/* number of bytes to be copied = 10 */
	DMA1_Channel1->CCR = (1<<14)|(1<<7)|(1<<6)|(1<<1);	/* mem2mem=1, mem inc.=1, per. inc.=1, TCIE=1 */
	DMA1_Channel1->CCR |= 1; /* enable the channel */
	NVIC_EnableIRQ(DMA1_Channel1_IRQn); /* enable the interrupt for channel 1 */
	
	while(transmitComplete == 0); /* wait until the transmission is complete */
	
	while(1);	
}

void DMA1_Channel1_IRQHandler(void) 
{
	if((DMA1->ISR&(1<<1)) != 0) /* is transmit complete */
	{
		DMA1->IFCR = 1<<1; /* clear the TCIF flag */
		transmitComplete = 1; /* set the flag */
	}
}

