/* The program shows "Hello World!" on the LCD */

#include <stm32f10x.h>

void lcd_init(void);
void lcd_command(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_gotoxy(unsigned char x, unsigned char y);
void lcd_print(char * str);

void delay_us(uint16_t t);

#define LCD_RS	4
#define LCD_EN	5

int main()
{
	RCC->APB2ENR |= 0xFC; /* Enable clocks for GPIO ports */	
	GPIOA->CRL = 0x44333333; /* PA0-PA5 as outputs */

	lcd_init();

	lcd_print("Hello World!"); /* show "Hello World!" */
	
	while(1)	/* stay here forever */
	{		
	}
}

void lcd_putValue(unsigned char value)
{
	GPIOA->BRR = 0x0F; /* clear PA0-PA3 */
	GPIOA->BSRR = (value>>4)&0x0F; /* put high nibble on PA0-PA3 */	
	
	GPIOA->ODR |= (1<<LCD_EN); /* EN = 1 for H-to-L pulse */
	delay_us(1);			/* make EN pulse wider */
	GPIOA->ODR &= ~ (1<<LCD_EN);	/* EN = 0 for H-to-L pulse */
	delay_us(100);			/* wait	*/

	GPIOA->BRR = 0x0F; /* clear PA0-PA3 */
	GPIOA->BSRR = value&0x0F; /* put low nibble on PA0-PA3 */	
	
	GPIOA->ODR |= (1<<LCD_EN); /* EN = 1 for H-to-L pulse */
	delay_us(1);			/* make EN pulse wider */
  GPIOA->ODR &= ~(1<<LCD_EN);	/* EN = 0 for H-to-L pulse */
  delay_us(100);			/* wait	*/
}

void lcd_command(unsigned char cmd)
{
	GPIOA->ODR &= ~ (1<<LCD_RS);	/* RS = 0 for command */
	lcd_putValue(cmd);
}

void lcd_data(unsigned char data)
{
	GPIOA->ODR |= (1<<LCD_RS);	/* RS = 1 for data */
	lcd_putValue(data); 
}

void lcd_print(char * str)
{
  unsigned char i = 0;

	while(str[i] != 0) /* while it is not end of string */
	{
		lcd_data(str[i]); /* show str[i] on the LCD */
		i++;
	}
}

void lcd_init()
{
	GPIOA->ODR &= ~(1<<LCD_EN);	/* LCD_EN = 0 */
	delay_us(3000); 			/* wait 3ms */
	lcd_command(0x33);		/* send $33 for init. */
	lcd_command(0x32);		/* send $32 for init. */
	lcd_command(0x28);		/* init. LCD 2 line,5´7 matrix */
	lcd_command(0x0e);		/* display on, cursor on */
	lcd_command(0x01);		/* clear LCD */
	delay_us(2000);				/* wait 2ms */
	lcd_command(0x06);		/* shift cursor right */
}

void delay_us(uint16_t t)
{
	volatile unsigned long l = 0;
	for(uint16_t i = 0; i < t; i++)
		for(l = 0; l < 6; l++)
		{
		}
}
