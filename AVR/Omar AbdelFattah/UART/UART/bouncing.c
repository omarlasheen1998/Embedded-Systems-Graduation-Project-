 /*
 * _16_8Newtrialfromzero.c
 *
 * Created: 16/08/2020 10:16:42 ص
 *  Author: omar
 */ 

#include <avr/io.h>
#include <util/delay.h>

void debouncing (int* pressed,int* released_level,int* pressed_level,void (*f)(int),int data)
{
	
	if (bit_is_clear(PINB,1))
	{
	
	
			
	(*pressed_level)++;
			*released_level=0;
			if (*pressed_level>300)
			{
				
				*pressed_level=0;
				if (*pressed==0){
				*pressed=1;
				f(data);
			
			
			
				}						
				
			}		
		}	
		else{
			(*released_level)++;
			*pressed_level=0;
			if (*released_level>100)
			{
				*pressed=0;
				*released_level=0;
				
				
			}
			
		}
		
						
}