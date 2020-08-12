

#ifndef DIO_H_
#define DIO_H_

#define u8  unsigned char 

//typedef unsigned char  u8 ;

#define  OUTPUT            1
#define  INPUT             0
#define INPUT_PULLUP       2

#define  HIGH   1
#define   LOW   0

#define portA 1
#define portB 2
#define portC 3
#define portD 4

// function for determind  pin states "output" or "input"
void pinModepin(u8 port,u8 pin ,u8 states);
void pinModeport(u8 port,u8 states);
//funtion to wight on pin or ports
void digitalWrightpin(u8 port,u8 pin ,u8 states);
void digitalWrightport(u8 port,u8 states);
//function to read from pin 
u8 digitalRead(u8 port,u8 pin);


#endif /* DIO_H_ */