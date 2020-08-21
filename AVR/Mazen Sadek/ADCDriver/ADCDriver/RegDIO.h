
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


//ADCRegister
#define  ADMUX_REG      *((volatile u8*)(0x27))
#define  ADCSRA_REG     *((volatile u8*)(0x26))
#define  ADCH_REG       *((volatile u8*)(0x25))
#define  ADCL_REG       *((volatile u8*)(0x24))
#define  SFIOR_REG      *((volatile u8*)(0x50))

#endif /* REGDIO_H_ */