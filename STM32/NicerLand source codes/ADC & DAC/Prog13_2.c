/* This program configures PA1(ADC_IN1) as the ADC input and sends the result through usart1 */

#include <stm32f10x.h>
#include <stdio.h>

void usart1_init(void);
void usart1_sendByte(unsigned char c);
void usart1_sendStr(char *str);
void usart1_sendInt(unsigned int i);

void delay_ms(uint16_t t);
void delay_us(uint16_t t);

volatile uint16_t adcResult;

void ADC1_2_IRQHandler()
{
	adcResult = ADC1->DR; /* read conversion result */
}

int main()
{
	RCC->APB2ENR |= 0xFC|(1<<9)|(1<<14); 	/* enable clocks for GPIO, ADC1 clock, and usart1 */

	GPIOA->CRL = 0x44444404; 	/* PA1(ADC_IN1) as analog input */
	ADC1->CR2 = 1;	/* ADON = 1 (power-up) */
	
	ADC1->SMPR2 = 7<<3; /* SMP1 = 111 (239.5 ADC clock cycles) */
		
	delay_us(1);	/* wait 1us to make sure the adc module is stable */
	
	usart1_init(); /* initialize the usart1 */

	ADC1->CR1 = (1<<5); /* EOCIE = 1 */

	ADC1->SQR3 = 1;	/* choose channel 1 as the input */
	ADC1->CR2 |= 1<<1;	/* CONT = 1 (Convert continuously) */
	ADC1->CR2 |= 1<<0;	/* ADCON = 1 (start conversion) */
	
	NVIC_EnableIRQ(ADC1_2_IRQn); /* enable ADC1_2 interrupt */
	
	while(1)
	{	
		usart1_sendInt(adcResult);	/* send the adc result through serial */
		usart1_sendStr("\n\r");		/* go to new line */

		delay_ms(10);		/* wait 10ms */
	}
}

void usart1_init()
{
	//USART1 init.
	GPIOA->ODR |= (1<<10);  //pull-up PA10
	GPIOA->CRH = 0x444448B4; // RX1=input with pull-up, TX1=alt. func output
	USART1->CR1 = 0x200C;
	USART1->BRR = 7500;	 // 72MHz/9600bps = 7500	
}

void usart1_sendByte(unsigned char c)
{	
	while((USART1->SR&(1<<6)) == 0);  //wait until the TC flag is set 
	USART1->DR = c;
}

/* the function sends a zero ending string through USART1 */
void usart1_sendStr(char *str)
{
	while(*str != 0)
	{
		usart1_sendByte(*str);
		str++;
	}
}

/* The function sends a number through USART1 */
void usart1_sendInt(unsigned int i)
{
	char str[10];
	sprintf(str,"%d",i);
	
	usart1_sendStr(str);	
}

void delay_ms(uint16_t t)
{
	for(int i = 0; i < t; i++)
	{
		for(volatile uint16_t a = 0; a < 6000; a++)
		{}
	}
}

void delay_us(uint16_t t)
{
	for(int i = 0; i < t; i++)
	{
		for(volatile uint16_t a = 0; a < 6; a++)
		{}
	}
}
