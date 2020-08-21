


 

#include <avr/io.h>
#include "LCD.h"

int main(void)
{
	LCD_initalizaion(Eight_bits);
	
	LCD_goto(1,1,Eight_bits);
	LCD_print("Mazen",Eight_bits);
   LCD_goto(1,2,Eight_bits);

   LCD_print("Sadek",Eight_bits);
	
	LCD_initalizaion(Four_bits);
	
	LCD_goto(1,1,Four_bits);
	LCD_print("Mazen",Four_bits);
	LCD_goto(1,2,Four_bits);

	LCD_print("Sadek",Four_bits);
	
	
    while (1) 
    {
    }
} 

