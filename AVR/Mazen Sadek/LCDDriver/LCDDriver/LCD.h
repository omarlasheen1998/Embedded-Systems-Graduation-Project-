

#ifndef LCD_H_
#define LCD_H_
// 8bitmode
#define command portB
#define data    portA
//4bitmode
#define datacomm portC

#define Four_bits 1
#define Eight_bits 2 

#define u8 unsigned char
#define RS  0
#define RW  1
#define E   2


void LCD_initalizaion(u8 states);
void LCD_command(u8 comnd,u8 states );
void LCD_data(u8 statment,u8 states);
void LCD_print(u8 *str,u8 states);
void LCD_goto(u8 x, u8 y,u8 states);

#endif /* LCD_H_ */