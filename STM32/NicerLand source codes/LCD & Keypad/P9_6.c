/* The program shows the pressed key on the LCD */
/* keypad rows: PB15-PB12 cols: PB9-PB6 */

#include <stm32f10x.h>
#include <stdio.h>

void lcd_init(void);
void lcd_command(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_gotoxy(unsigned char x, unsigned char y);
void lcd_print(char * str);

void delay_ms(uint16_t t);
void delay_us(uint16_t t);

#define LCD_RS	4
#define LCD_EN	5

uint8_t keypad_kbhit(void);
uint8_t keypad_getkey(void);


int main()
{
	RCC->APB2ENR |= 0xFC; /* Enable clocks for GPIO ports */	
	GPIOA->CRL = 0x44333333; /* PA0-PA5 as outputs */

	lcd_init();

	lcd_gotoxy(1,1);	/* move cursor to 1,1 */
	lcd_print("The pressed key is: "); /* show the message */
	
	/* init keypad pins */
	GPIOB->CRL = 0x88444444; /* PB6 and PB7 as inputs */
	GPIOB->CRH = 0x33334488; /* PB15-PB12 as outputs, PB8 and PB9 as inputs */
	GPIOB->ODR |= (0xF<<6); /* pull-up PB9-PB6 */
	
	GPIOC->CRH = 0x44344444; /* PC13 as output */
	
	while(1)
	{
		lcd_gotoxy(1,2);	/* move cursor to 1,2 */
		if(keypad_kbhit() == 0)
			lcd_print(" ");
		else
			lcd_data(keypad_getkey()); /* show the pressed key */		
	}
}

/* The function checks if a key is pressed or not */
/* Returns: 0: Not pressed, 1: Pressed */
uint8_t keypad_kbhit()
{
	GPIOB->ODR &= ~(0x0F<<12); /* make all rows ones */
	delay_us(1);
	if(((GPIOB->IDR>>6)&0xF) == 0xF)
		return 0;
	else
		return 1;
}

/* The function returns the pressed key. */
/* It returns 0 if no key is pressed. */

uint8_t keypad_getkey()
{
	uint8_t keypadLookup[16]={'1','2','3','A','4','5','6','B','7','8','9','C','*','0','#','D'};
	const uint32_t rowSelect[4]={
		0x1000E000, /* Row3-Row0 = 1110 */
		0x2000D000, /* Row3-Row0 = 1101 */
		0x4000B000, /* Row3-Row0 = 1011 */
		0x80007000};/* Row3-Row0 = 1011 */	
				
	if(keypad_kbhit() == 0)	/* if no key is pressed */
		return 0;
	
	for(int r = 0; r <= 3; r++) /* rows 0 to 3 */
	{
		GPIOB->BSRR = rowSelect[r]; /* ground row r and make the others high */
		delay_us(1);	/* wait for the columns to beupdated */
		uint8_t cols = (GPIOB->IDR>>6)&0xF;
		
		switch(cols) 
		{
			case 0x0E: return keypadLookup[r*4+0]; /* col0 is low */
			case 0x0D: return keypadLookup[r*4+1]; /* col1 is low */
			case 0x0B: return keypadLookup[r*4+2]; /* col2 is low */
			case 0x07: return keypadLookup[r*4+3]; /* col3 is low */
		}
	}
	
	return 0;
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

void lcd_gotoxy(unsigned char x, unsigned char y)
{
	const unsigned char firstCharAdr[]={0x80,0xC0,0x94,0xD4};
	lcd_command(firstCharAdr[y-1] + x - 1);
	delay_us(100);	
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

void delay_ms(uint16_t t)
{
	volatile unsigned long l = 0;
	for(uint16_t i = 0; i < t; i++)
		for(l = 0; l < 6000; l++)
		{
		}
}

void delay_us(uint16_t t)
{
	volatile unsigned long l = 0;
	for(uint16_t i = 0; i < t; i++)
		for(l = 0; l < 6; l++)
		{
		}
}
