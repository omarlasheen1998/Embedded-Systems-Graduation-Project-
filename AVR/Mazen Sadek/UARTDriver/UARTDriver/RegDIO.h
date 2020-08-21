
#ifndef REGDIO_H_
#define REGDIO_H_

//PORTA
#define DDRA_REG        *((volatile  u8*)(0x3A))
#define PORTA_REG       *((volatile  u8*)(0x3B))
#define PINA_REG        *((volatile  u8*)(0x39))

//PORTB
#define DDRB_REG        *((volatile u8*)(0x37))
#define PORTB_REG       *((volatile u8*)(0x38))
#define PINB_REG        *((volatile u8*)(0x36))

//PORTC
#define DDRC_REG        *((volatile u8*)(0x34))
#define PORTC_REG       *((volatile u8*)(0x35))
#define PINC_REG        *((volatile u8*)(0x33))

//PORTD
#define DDRD_REG        *((volatile u8*)(0x31))
#define PORTD_REG       *((volatile u8*)(0x32))
#define PIND_REG        *((volatile u8*)(0x30))

//UARt Register

#define UDR             *((volatile u8*)(0x2C))
#define UCSRA           *((volatile u8*)(0x2B))  
#define UCSRB           *((volatile u8*)(0x2A))
#define UCSRC           *((volatile u8*)(0x40))
#define UBRRL           *((volatile u8*)(0x29)) 


#endif /* REGDIO_H_ */