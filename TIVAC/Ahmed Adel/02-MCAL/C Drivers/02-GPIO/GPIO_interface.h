/********************************************/
/* Author   : Ahmed Ismail                  */
/* Date     : 3 SEP 2020                   */
/* Version  : V01                           */
/********************************************/



#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

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


void GPIO_voidEnableClock(uint8 Copy_u8PortID);
void GPIO_voidDisableClock(uint8 Copy_u8PortID);
uint8 GPIO_u8CheckLockedPin(uint8 Copy_u8PortID, uint8 Copy_u8PinID);
void GPIO_voidSetPinDirection(uint8 Copy_u8PortID, uint8 Copy_u8PinID, uint8 Copy_u8Direction);
void GPIO_voidSetPinValue(uint8 Copy_u8PortID, uint8 Copy_u8PinID, uint8 Copy_u8Value);
uint8 GPIO_u8GetPinValue(uint8 Copy_u8PortID, uint8 Copy_u8PinID);



#endif /* GPIO_INTERFACE_H */
