#include "GPIO.h"

void noInterrupts(void)
{

	cli();

}

void Interrupts(void)
{
	
	sei();
}

void (*INT0_PTR)(void);
void (*INT1_PTR)(void);
void (*INT2_PTR)(void);


Pin::Pin(uint8_t pinNum, uint8_t portNum, uint8_t type){
	
	if (pinNum < 8 && pinNum >= 0)
	{
		pinNumber = pinNum;
		pinSetFlag = 1;
	}
	if (portNum < 4 && portNum >= 0)
	{
		portSelector = portNum;
		portSetFlag = 1;
	}
	if (type == OUTPUT || type == INPUT || type == INPUT_PULLUP)
	{
		pinType = type;
		typeSetFlag = 1;
	}
	
	if (pinSetFlag && portSetFlag && typeSetFlag)
	{
		setPin(pinNumber, portSelector, pinType);
	}
	
}


void Pin::setPin(uint8_t pinNum, uint8_t portNum, uint8_t type){
	if(type == OUTPUT){
		switch(portNum){
			case 0:
				DDRA |= (1 << pinNum);
				break;
			case 1:
				DDRB |= (1 << pinNum);
				break;
			case 2:
				DDRC |= (1 << pinNum);
				break;
			case 3:
				DDRD |= (1 << pinNum);
				break;
		}
	}
	else if(type == INPUT){
		switch(portNum){
			case 0:
				DDRA &= ~(1 << pinNum);
				break;
			case 1:
				DDRB &= ~(1 << pinNum);
				break;
			case 2:
				DDRC &= ~(1 << pinNum);
				break;
			case 3:
				DDRD &= ~(1 << pinNum);
				break;
		}
	}
	else if(type == INPUT_PULLUP){
		switch(portNum){
			case 0:
				DDRA &= ~(1 << pinNum);
				PORTA |= (1 << pinNum);
				break;
			case 1:
				DDRB &= ~(1 << pinNum);
				PORTB |= (1 << pinNum);
				break;
			case 2:
				DDRC &= ~(1 << pinNum);
				PORTC |= (1 << pinNum);
				break;
			case 3:
				DDRD &= ~(1 << pinNum);
				PORTD |= (1 << pinNum);
				break;
		}
	}
}



uint8_t Pin::pinWrite(uint8_t value){
	if (value == HIGH)
	{
		switch(portSelector){
			case 0:
			PORTA |= (1 << pinNumber);
			break;
			case 1:
			PORTB |= (1 << pinNumber);
			break;
			case 2:
			PORTC |= (1 << pinNumber);
			break;
			case 3:
			PORTD |= (1 << pinNumber);
			break;
		}
		return 0;
	}
	else if (value == LOW)
	{
		switch(portSelector){
			case 0:
			PORTA &= ~(1 << pinNumber);
			break;
			case 1:
			PORTB &= ~(1 << pinNumber);
			break;
			case 2:
			PORTC &= ~(1 << pinNumber);
			break;
			case 3:
			PORTD &= ~(1 << pinNumber);
			break;
		}
		return 0;
	}
	else{
		return 1;
	}
}



uint8_t Pin::pinRead(){
	
	switch(portSelector){
		case 0:
		return PINA & (1 << pinNumber);
		case 1:
		return PINB & (1 << pinNumber);
		case 2:
		return PINC & (1 << pinNumber);
		case 3:
		return PIND & (1 << pinNumber);
	}
	
	return 1;
}

uint16_t Pin::pinAnalogRead(void){
	if (portSelector == 0 && pinType == INPUT)
	{
		ADC_Init(DIV_FACTOR_8, CONVERSION_10_BIT, REF_DEFAULT);
		uint16_t adcValue = analogRead(pinNumber);
		disableADC();
		_delay_us(20);
		return adcValue;
	}
	else{
		return 0;
	}
}

uint8_t Pin::attachInterrupt(uint8_t state, void (*Local_ISR)(void)){
	if (portSelector == 3)
	{
		if (pinNumber == PD2)  // INT0
		{
			if (state == INT_LOW)
			{
				MCUCR &= ~(1 << ISC00);
				MCUCR &= ~(1 << ISC01);
			}
			else if (state == INT_CHANGE)
			{
				MCUCR |= (1 << ISC00);
				MCUCR &= ~(1 << ISC01);
			}
			else if (state == INT_FALLING)
			{
				MCUCR &= ~(1 << ISC00);
				MCUCR |= (1 << ISC01);
			}
			else if (state == INT_RISING)
			{
				MCUCR |= (1 << ISC00);
				MCUCR |= (1 << ISC01);
			}
			GICR |= (1 << INT0);
			INT0_PTR = Local_ISR;
			Interrupts();
			return 0;
		}
		else if (pinNumber == PD3) //INT1
		{
			if (state == INT_LOW)
			{
				MCUCR &= ~(1 << ISC10);
				MCUCR &= ~(1 << ISC11);
			}
			else if (state == INT_CHANGE)
			{
				MCUCR |= (1 << ISC10);
				MCUCR &= ~(1 << ISC11);
			}
			else if (state == INT_FALLING)
			{
				MCUCR &= ~(1 << ISC10);
				MCUCR |= (1 << ISC11);
			}
			else if (state == INT_RISING)
			{
				MCUCR |= (1 << ISC10);
				MCUCR |= (1 << ISC11);
			}
			
			GICR |= (1 << INT1);
			INT1_PTR = Local_ISR;
			Interrupts();
			return 0;
		}
		else{
			return 1;
		}
		
	}
	else if (portSelector == 1)
	{
		if (pinNumber == PB2)
		{
			if (state == INT_RISING)
			{
				GICR &= ~(1 << INT2);
				MCUCSR |= (1 << ISC2);
			}
			else if (state == INT_FALLING)
			{
				GICR &= ~(1 << INT2);
				MCUCSR &= ~(1 << ISC2);
			}
			else{
				return 1;
			}
			
			GIFR |= (1 << INTF2);
			GICR |= (1 << INT2);
			INT2_PTR = Local_ISR;
			Interrupts();
			return 0;
		}
		else{
			return 1;
		}
	}
	else{
		return 1;
	}
	
}


ISR(INT0_vect){
	INT0_PTR();
}
ISR(INT1_vect){
	INT1_PTR();
}
ISR(INT2_vect){
	INT2_PTR();
}
