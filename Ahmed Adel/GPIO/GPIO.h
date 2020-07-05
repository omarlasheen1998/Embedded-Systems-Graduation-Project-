
#ifndef GPIO_H_
#define GPIO_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

/* 
	GPIO Driver consists of the following:
	1 - Pin Class which makes a constructor for the pin taking ( Pin number, Port , Pin type ) as its argument.
		*Pin number :	PA0 - PA7 
						PB0 - PB7 
						PC0 - PC7
						PD0 - PD7
		*Port : PORT_A , PORT_B , PORT_C , PORT_D
		*Type : OUTPUT , INPUT , INPUT_PULLUP
		
	2- Methods available for Pin Class:
		- pinWrite( value ) : This method is responsible for setting and clearing the Pin with HIGH or LOW value  
							* value : HIGH , LOW
		- pinRead() : This method is responsible for reading the Pin input and return the value available.
		- attachInterrupt(state, ISR_function) : This method is responsible for setting the Interrupt for that Pin.
			**Constrains: The pin must be PB2, PD2, PD3 ONLY.
			* state : INT_LOW , INT_CHANGE , INT_FALLING, INT_RISING  --> For PB2 , the only states available is : INT_FALLING , INT_RISING.
			* ISR_function : A pointer to the function must be passed as an argument.
*/

#define OUTPUT 1
#define INPUT 0
#define INPUT_PULLUP 2

#define HIGH 1
#define LOW 0

#define INT_LOW 0
#define INT_CHANGE 1
#define INT_FALLING 2
#define INT_RISING 3


void noInterrupts(void);
void Interrupts(void);

enum ports{
	PORT_A = 0,
	PORT_B,
	PORT_C,
	PORT_D
};


class Pin{
	
public:
	Pin(uint8_t pinNum, uint8_t portNum, uint8_t type);
	uint8_t pinWrite(uint8_t out);
	uint8_t pinRead(void);
	uint8_t attachInterrupt(uint8_t state, void (*Local_ISR)(void));

	
private:

	void setPin(uint8_t pinNum, uint8_t portNum, uint8_t type);
	uint8_t pinNumber = 0;
	uint8_t pinType = 0;
	uint8_t portSelector = 0;
	
	uint8_t pinSetFlag = 0;
	uint8_t portSetFlag = 0;
	uint8_t typeSetFlag = 0;

};



#endif /* GPIO_H_ */