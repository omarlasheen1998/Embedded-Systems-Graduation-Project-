/* The program shows HELLO on the PCD8544 (Nokia5110) LCD */
#include <stm32f10x.h>

#define GLCD_CS			4
#define GLCD_RESET	3
#define GLCD_DC			2

void delay_ms(uint16_t t);

uint8_t spi1_transfer(uint8_t d);
void glcd_init(void);
void glcd_setCursor(uint8_t x, uint8_t y);
void glcd_putchar(char c);
void glcd_clear(void);

int main()
{	
	glcd_init(); /* initialize the lcd */
	glcd_clear();

	glcd_setCursor(20, 2); /* move cursor to 20, 2 */

	glcd_putchar('H');
	glcd_putchar('E');
	glcd_putchar('L');
	glcd_putchar('L');
	glcd_putchar('O');
	

	while(1)
	{
	}
}

/* The function sends a byte of data through SPI */
/* argument d: the byte to be sent */
/* return value: the received data */
uint8_t spi1_transfer(uint8_t d)
{
	GPIOA->BRR = (1 << GLCD_CS);
	
	SPI1->DR = d;	/* send the contents of d */
	while((SPI1->SR&(1<<0)) == 0);	/* wait until RXNE is set */
	
	GPIOA->BSRR = (1 << GLCD_CS);	
	return SPI1->DR;	/* return the received data */ 
}

void glcd_cmd(uint8_t cmd)
{
	GPIOA->BRR = (1 << GLCD_DC);	/* DC = 0 (command) */
	spi1_transfer(cmd);
}

void glcd_data(uint8_t data)
{
	GPIOA->BSRR = (1 << GLCD_DC);	/* DC = 1 (data) */
	spi1_transfer(data);
}

void glcd_init()
{
	RCC->APB2ENR |= 0xFC|(1<<12); 	/* enable clocks for GPIO and SPI1 */
	GPIOA->CRL = 0xB4B33344; 	/* MOSI (PA7) and SCK(PA5): alt. func. out, PA4: output for CS */	
	SPI1->CR1 = 0x35C;	/* SPE = 1, BR = 3, FFD = 0, SSI and SSM = 1 */	
	GPIOA->BSRR = (1<<GLCD_CS)|(1<<GLCD_RESET);	/* make CS and RESET pins high */
	
	delay_ms(10);
	GPIOA->BRR = (1<<GLCD_RESET);	/* reset the LCD (RESET = 0) */
	delay_ms(70);
	GPIOA->BSRR = (1<<GLCD_RESET); /* release the RESET pin */
	
	glcd_cmd(0x21);	/* switch to extended command mode */
	glcd_cmd(0x06);	/* set temp. coefficient 2 */
	glcd_cmd(0x13);	/* set LCD bias mode 1:48 */
	glcd_cmd(0xC2); /* set VOP to 7V (VOP = 66) */
	glcd_cmd(0x20); /* switch to basic mode */
	glcd_cmd(0x0C);	/* set lcd display to normal mode */
}

void glcd_setCursor(uint8_t x, uint8_t y) 
{
	glcd_cmd(0x80 | x);	/* set x */
	glcd_cmd(0x40 | y);	/* set y (bank) */
}

void glcd_clear(void) 
{
	uint16_t i;

	glcd_setCursor(0, 0);
	
	for (i = 0 ; i < 504 ; i++)
		glcd_data(0x00);		
}

/* sample font table */
const char font_table[][5] = {
	{ 0x7e, 0x11, 0x11, 0x11, 0x7e }, /* A */
	{ 0x7f, 0x49, 0x49, 0x49, 0x36 }, /* B */
	{ 0x3e, 0x41, 0x41, 0x41, 0x22 }, /* C */
	{ 0x7f, 0x41, 0x41, 0x22, 0x1c }, /* D */
	{ 0x7f, 0x49, 0x49, 0x49, 0x41 }, /* E */
	{ 0x7f, 0x09, 0x09, 0x09, 0x01 }, /* F */
	{ 0x3e, 0x41, 0x49, 0x49, 0x7a }, /* G */
	{ 0x7f, 0x08, 0x08, 0x08, 0x7f }, /* H */
	{ 0x00, 0x41, 0x7f, 0x41, 0x00 }, /* I */
	{ 0x20, 0x40, 0x41, 0x3f, 0x01 }, /* J */
	{ 0x7f, 0x08, 0x14, 0x22, 0x41 }, /* K */
	{ 0x7f, 0x40, 0x40, 0x40, 0x40 }, /* L */
	{ 0x7f, 0x02, 0x0c, 0x02, 0x7f }, /* M */
	{ 0x7f, 0x04, 0x08, 0x10, 0x7f }, /* N */
	{ 0x3e, 0x41, 0x41, 0x41, 0x3e }, /* O */
	{ 0x7f, 0x09, 0x09, 0x09, 0x06 }, /* P */
	{ 0x3e, 0x41, 0x51, 0x21, 0x5e }, /* Q */
	{ 0x7f, 0x09, 0x19, 0x29, 0x46 }, /* R */
	{ 0x46, 0x49, 0x49, 0x49, 0x31 }, /* S */
	{ 0x01, 0x01, 0x7f, 0x01, 0x01 }, /* T */
	{ 0x3f, 0x40, 0x40, 0x40, 0x3f }, /* U */
	{ 0x1f, 0x20, 0x40, 0x20, 0x1f }, /* V */
	{ 0x3f, 0x40, 0x38, 0x40, 0x3f }, /* W */
	{ 0x63, 0x14, 0x08, 0x14, 0x63 }, /* X */
	{ 0x07, 0x08, 0x70, 0x08, 0x07 }, /* Y */
	{ 0x61, 0x51, 0x49, 0x45, 0x43 }, /* Z */
};

void glcd_putchar(char c) 
{
	uint8_t i;
	
	if((c < 'A')||(c > 'Z'))
		return;
	
	for (i = 0; i < 5; i++)
		glcd_data(font_table[c-'A'][i]);
	
	glcd_data(0); /* an empty column between chars */
}

void delay_ms(uint16_t t)
{
	volatile unsigned long l = 0;
	for(uint16_t i = 0; i < t; i++)
		for(l = 0; l < 6000; l++)
		{
		}
}
