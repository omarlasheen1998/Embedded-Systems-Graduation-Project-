

#ifndef KEYPAD_H_
#define KEYPAD_H_

#define  u8 unsigned char

#define R0 0
#define R1 1
#define R2 2
#define R3 3

#define C0 4
#define C1 5
#define C2 6
#define C3 7

#define  keypad_port portC

void keypad_initilaization();
u8 keypad_getpress();



#endif /* KEYPAD_H_ */