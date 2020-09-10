/********************************************/
/* Author   : Ahmed Ismail                  */
/* Date     : 10 SEP 2020                   */
/* Version  : V01                           */
/********************************************/

#include "01-LIB/01-STD_TYPES/STD_TYPES.h"


#ifndef GPIO_CLASS_H_
#define GPIO_CLASS_H_

/* Pin Digital Output Values */
#define HIGH    1
#define LOW     0

/* Pin Mode */
#define OUTPUT  1
#define INPUT   0
#define INPUT_PULLUP    2
#define INPUT_PULLDOWN  3

enum PIN_IDs{
    PIN0 = 0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7,
};

enum PORT_IDs{
    PORTA = 0,
    PORTB,
    PORTC,
    PORTD,
    PORTE,
    PORTF
};


class Pin{

public:
    Pin(uint8 Copy_u8PinID, uint8 Copy_u8PortID, uint8 Copy_u8Mode);
    uint8 pinWrite(uint8 Copy_u8Value);
    uint8 pinRead(void);
    //uint16 pinAnalogRead(void);
    //uint8_t attachInterrupt(uint8_t state, void (*Local_ISR)(void));


private:
    void GPIO_voidEnableClock(uint8 Copy_u8PortID);
    void GPIO_voidDisableClock(uint8 Copy_u8PortID);
    uint8 GPIO_u8CheckLockedPin(uint8 Copy_u8PortID, uint8 Copy_u8PinID);
    void GPIO_voidSetPinDirection(uint8 Copy_u8PortID, uint8 Copy_u8PinID, uint8 Copy_u8Direction);
    void GPIO_voidSetPinValue(uint8 Copy_u8PortID, uint8 Copy_u8PinID, uint8 Copy_u8Value);
    uint8 GPIO_u8GetPinValue(uint8 Copy_u8PortID, uint8 Copy_u8PinID);


    uint8 pinID = 0;
    uint8 pinMode = 0;
    uint8 portID = 0;

    uint8 pinSetFlag = 0;
    uint8 portSetFlag = 0;
    uint8 typeSetFlag = 0;


};



#endif /* GPIO_CLASS_H_ */
