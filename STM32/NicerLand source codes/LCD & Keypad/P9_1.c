/* The program shows "Hello" on the LCD */

#include <stm32f10x.h>

void lcd_init(void);
void lcd_sendCommand(unsigned char cmd);
void lcd_sendData(unsigned char data);

void delay_us(uint16_t t);

#define LCD_RS	7
#define LCD_RW	6
#define LCD_EN	5

int main()
{
	RCC->APB2ENR |= 0xFC; /* Enable clocks for GPIO ports */	
	GPIOA->CRL = 0x33333333; /* PA0-PA7 as outputs */

	GPIOB->CRL = 0x33344444; /* PB7-PB5 as outputs */
	lcd_init();

	lcd_sendData('H');
	lcd_sendData('e');
	lcd_sendData('l');
	lcd_sendData('l');
	lcd_sendData('o');
	
	while(1)	/* stay here forever */
	{	
	}
}

void lcd_putValue(unsigned char value)
{
	GPIOA->BRR = 0xFF; /* clear PA0-PA7 */
	GPIOA->BSRR = value&0xFF; /* put value on PA0-PA7 */	
	
	GPIOB->BSRR = (1<<LCD_EN); // same as GPIOB->ODR |= (1<<LCD_EN); /* EN = 1 for H-to-L pulse */
	delay_us(2);			/* make EN pulse wider */
	GPIOB->BRR = (1<<LCD_EN); // same as GPIOB->ODR &= ~(1<<LCD_EN);	/* EN = 0 for H-to-L pulse */
	delay_us(100);			/* wait	*/
}

void lcd_sendCommand(unsigned char cmd)
{
	GPIOB->BRR = (1<<LCD_RS); //same as GPIOB->ODR &= ~ (1<<LCD_RS);	/* RS = 0 for command */
	lcd_putValue(cmd);
}

void lcd_sendData(unsigned char data)
{
	GPIOB->BSRR = (1<<LCD_RS); //same as GPIOB->ODR |= (1<<LCD_RS);	/* RS = 1 for data */
	lcd_putValue(data); 
}

void lcd_init()
{
	GPIOB->BRR = (1<<LCD_EN); //same as GPIOA->ODR &= ~(1<<LCD_EN);	/* LCD_EN = 0 */
	delay_us(3000); 			/* wait 3ms */
	lcd_sendCommand(0x38);		/* init. LCD 2 line,5´7 matrix */
	lcd_sendCommand(0x0e);		/* display on, cursor on */
	lcd_sendCommand(0x01);		/* clear LCD */
	delay_us(2000);				/* wait 2ms */
	lcd_sendCommand(0x06);		/* shift cursor right */
}

void delay_us(uint16_t t)
{
	volatile unsigned long l = 0;
	for(uint16_t i = 0; i < t; i++)
		for(l = 0; l < 6; l++)
		{
		}
}
