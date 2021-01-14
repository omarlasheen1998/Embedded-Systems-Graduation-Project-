#include <stm32f10x.h>

volatile char transmitComplete = 0;

int main()
{
	long source[10]={0x11111111,0x22222222,0x33333333,0x44444444,0x55555555,0x66666666,0x77777777,0x88888888,0x99999999,0xaaaaaaaa};
	long dest[10];
	
	RCC->AHBENR = (1<<0);//RCC_AHBENR_DMA1EN;
	
	DMA1_Channel1->CPAR = (uint32_t) source; /* CPAR = the addr. of source array in the mem. */
	DMA1_Channel1->CMAR = (uint32_t) dest; /* CMAR = the addr. of dest array in the mem. */
	DMA1_Channel1->CNDTR = 10;	/* number of bytes to be copied = 10 */
	DMA1_Channel1->CCR = (1<<14)|(1<<11)|(1<<9)|(1<<7)|(1<<6)|(1<<1);	/* mem2mem=1,MSIZE=10 (32-bit), PSIZE=10 (32-bit), mem inc.=1, per. inc.=1, TCIE=1 */
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

