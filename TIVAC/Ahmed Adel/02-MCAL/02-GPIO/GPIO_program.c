/********************************************/
/* Author   : Ahmed Ismail                  */
/* Date     : 3 SEP 2020                   */
/* Version  : V01                           */
/********************************************/

#include "01-LIB/01-STD_TYPES/STD_TYPES.h"
#include "01-LIB/02-BIT_MATH/BIT_MATH.h"

#include "02-MCAL/02-GPIO/GPIO_interface.h"
#include "02-MCAL/02-GPIO/GPIO_private.h"
#include "02-MCAL/02-GPIO/GPIO_config.h"


void GPIO_voidEnableClock(uint8 Copy_u8PortID){
    #if OPERATION_MODE == RUN_MODE
        if(Copy_u8PortID >= 0 && Copy_u8PortID < 6){
            SYSCTL_RCGCGPIO |= (1 << Copy_u8PortID);
            uint8 clocksDelay = 0;
        }
        else{
            /* Return Error */
        }

    #elif OPERATION_MODE == SLEEP_MODE
        if(Copy_u8PortID >= 0 && Copy_u8PortID < 6){
            SYSCTL_SCGCGPIO |= (1 << Copy_u8PortID);
        }
        else{
            /* Return Error */
        }

    #elif OPERATION_MODE == DEEP_SLEEP_MODE
        if(Copy_u8PortID >= 0 && Copy_u8PortID < 6){
            SYSCTL_DCGCGPIO |= (1 << Copy_u8PortID);
        }
        else{
            /* Return Error */
        }

    #else
        #error("Operation Mode is not set")

    #endif
}

void GPIO_voidDisableClock(uint8 Copy_u8PortID){
    #if OPERATION_MODE == RUN_MODE
        if(Copy_u8PortID >= 0 && Copy_u8PortID < 6){
            SYSCTL_RCGCGPIO &= ~(1 << Copy_u8PortID);
        }
        else{
            /* Return Error */
        }

    #elif OPERATION_MODE == SLEEP_MODE
        if(Copy_u8PortID >= 0 && Copy_u8PortID < 6){
            SYSCTL_SCGCGPIO &= ~(1 << Copy_u8PortID);
        }
        else{
            /* Return Error */
        }

    #elif OPERATION_MODE == DEEP_SLEEP_MODE
        if(Copy_u8PortID >= 0 && Copy_u8PortID < 6){
            SYSCTL_DCGCGPIO &= ~(1 << Copy_u8PortID);
        }
        else{
            /* Return Error */
        }

    #else
        #error("Operation Mode is not set")

    #endif
}





#if BUS_ID == APB
void GPIO_voidSetPinDirection(uint8 Copy_u8PortID, uint8 Copy_u8PinID, uint8 Copy_u8Direction){
    if(Copy_u8PortID >= 0 && Copy_u8PortID < 6){
        if(Copy_u8PinID >= 0 && Copy_u8PinID < 8){
            if(Copy_u8Direction == OUTPUT || Copy_u8Direction == INPUT || Copy_u8Direction == INPUT_PULLDOWN || Copy_u8Direction == INPUT_PULLUP){
                switch(Copy_u8PortID){
                    case PORTA:
                        GPIO_APB_PORTA_GPIOLOCK = PORT_LOCK;
                        GPIO_APB_PORTA_GPIOCR       |=   (1 << Copy_u8PinID);
                        GPIO_APB_PORTA_GPIOAFSEL    &=  ~(1 << Copy_u8PinID);
                        GPIO_APB_PORTA_GPIOODR      &=  ~(1 << Copy_u8PinID);
                        switch(Copy_u8Direction){
                        case INPUT:
                            GPIO_APB_PORTA_GPIODIR   &=  ~(1 << Copy_u8PinID);
                            break;
                        case OUTPUT:
                            GPIO_APB_PORTA_GPIODIR   |=  (1 << Copy_u8PinID);
                            break;
                        case INPUT_PULLUP:
                            GPIO_APB_PORTA_GPIOPUR   |=  (1 << Copy_u8PinID);
                            break;
                        case INPUT_PULLDOWN:
                            GPIO_APB_PORTA_GPIOPDR   |=  (1 << Copy_u8PinID);
                            break;
                        }
                        GPIO_APB_PORTA_GPIODEN      |=   (1 << Copy_u8PinID);
                        break;
                    case PORTB:
                        GPIO_APB_PORTB_GPIOLOCK = PORT_LOCK;
                        GPIO_APB_PORTB_GPIOCR       |=   (1 << Copy_u8PinID);
                        GPIO_APB_PORTB_GPIOAFSEL    &=  ~(1 << Copy_u8PinID);
                        GPIO_APB_PORTB_GPIOODR      &=  ~(1 << Copy_u8PinID);
                        switch(Copy_u8Direction){
                            case INPUT:
                                GPIO_APB_PORTB_GPIODIR   &=  ~(1 << Copy_u8PinID);
                                break;
                            case OUTPUT:
                                GPIO_APB_PORTB_GPIODIR   |=  (1 << Copy_u8PinID);
                                break;
                            case INPUT_PULLUP:
                                GPIO_APB_PORTB_GPIOPUR   |=  (1 << Copy_u8PinID);
                                break;
                            case INPUT_PULLDOWN:
                                GPIO_APB_PORTB_GPIOPDR   |=  (1 << Copy_u8PinID);
                                break;
                        }
                        GPIO_APB_PORTB_GPIODEN      |=   (1 << Copy_u8PinID);
                        break;
                   case PORTC:
                       GPIO_APB_PORTC_GPIOLOCK = PORT_LOCK;
                       GPIO_APB_PORTC_GPIOCR       |=   (1 << Copy_u8PinID);
                       GPIO_APB_PORTC_GPIOAFSEL    &=  ~(1 << Copy_u8PinID);
                       GPIO_APB_PORTC_GPIOODR      &=  ~(1 << Copy_u8PinID);
                       switch(Copy_u8Direction){
                           case INPUT:
                               GPIO_APB_PORTC_GPIODIR   &=  ~(1 << Copy_u8PinID);
                               break;
                           case OUTPUT:
                               GPIO_APB_PORTC_GPIODIR   |=  (1 << Copy_u8PinID);
                               break;
                           case INPUT_PULLUP:
                               GPIO_APB_PORTC_GPIOPUR   |=  (1 << Copy_u8PinID);
                               break;
                           case INPUT_PULLDOWN:
                               GPIO_APB_PORTC_GPIOPDR   |=  (1 << Copy_u8PinID);
                               break;
                       }
                       GPIO_APB_PORTC_GPIODEN      |=   (1 << Copy_u8PinID);
                       break;
                   case PORTD:
                       GPIO_APB_PORTD_GPIOLOCK = PORT_LOCK;
                       GPIO_APB_PORTD_GPIOCR       |=   (1 << Copy_u8PinID);
                       GPIO_APB_PORTD_GPIOAFSEL    &=  ~(1 << Copy_u8PinID);
                       GPIO_APB_PORTD_GPIOODR      &=  ~(1 << Copy_u8PinID);
                       switch(Copy_u8Direction){
                           case INPUT:
                               GPIO_APB_PORTD_GPIODIR   &=  ~(1 << Copy_u8PinID);
                               break;
                           case OUTPUT:
                               GPIO_APB_PORTD_GPIODIR   |=  (1 << Copy_u8PinID);
                               break;
                           case INPUT_PULLUP:
                               GPIO_APB_PORTD_GPIOPUR   |=  (1 << Copy_u8PinID);
                               break;
                           case INPUT_PULLDOWN:
                               GPIO_APB_PORTD_GPIOPDR   |=  (1 << Copy_u8PinID);
                               break;
                       }
                       GPIO_APB_PORTD_GPIODEN      |=   (1 << Copy_u8PinID);
                       break;
                  case PORTE:
                      GPIO_APB_PORTE_GPIOLOCK = PORT_LOCK;
                      GPIO_APB_PORTE_GPIOCR       |=   (1 << Copy_u8PinID);
                      GPIO_APB_PORTE_GPIOAFSEL    &=  ~(1 << Copy_u8PinID);
                      GPIO_APB_PORTE_GPIOODR      &=  ~(1 << Copy_u8PinID);
                      switch(Copy_u8Direction){
                          case INPUT:
                              GPIO_APB_PORTE_GPIODIR   &=  ~(1 << Copy_u8PinID);
                              break;
                          case OUTPUT:
                              GPIO_APB_PORTE_GPIODIR   |=  (1 << Copy_u8PinID);
                              break;
                          case INPUT_PULLUP:
                              GPIO_APB_PORTE_GPIOPUR   |=  (1 << Copy_u8PinID);
                              break;
                          case INPUT_PULLDOWN:
                              GPIO_APB_PORTE_GPIOPDR   |=  (1 << Copy_u8PinID);
                              break;
                      }
                      GPIO_APB_PORTE_GPIODEN      |=   (1 << Copy_u8PinID);
                      break;
                  case PORTF:
                      GPIO_APB_PORTF_GPIOLOCK = PORT_LOCK;
                      GPIO_APB_PORTF_GPIOCR       |=   (1 << Copy_u8PinID);
                      GPIO_APB_PORTF_GPIOAFSEL    &=  ~(1 << Copy_u8PinID);
                      GPIO_APB_PORTF_GPIOODR      &=  ~(1 << Copy_u8PinID);
                      switch(Copy_u8Direction){
                          case INPUT:
                              GPIO_APB_PORTF_GPIODIR   &=  ~(1 << Copy_u8PinID);
                              break;
                          case OUTPUT:
                              GPIO_APB_PORTF_GPIODIR   |=  (1 << Copy_u8PinID);
                              break;
                          case INPUT_PULLUP:
                              GPIO_APB_PORTF_GPIOPUR   |=  (1 << Copy_u8PinID);
                              break;
                          case INPUT_PULLDOWN:
                              GPIO_APB_PORTF_GPIOPDR   |=  (1 << Copy_u8PinID);
                              break;
                      }
                      GPIO_APB_PORTF_GPIODEN      |=   (1 << Copy_u8PinID);
                      break;
                }
            }
            else{
                /* Return Error */
            }
        }
        else{
            /* Return Error */
        }
    }
    else{
        /* Return Error */
    }
}

void GPIO_voidSetPinValue(uint8 Copy_u8PortID, uint8 Copy_u8PinID, uint8 Copy_u8Value){
    if(Copy_u8PortID >= 0 && Copy_u8PortID < 6){
        if(Copy_u8PinID >= 0 && Copy_u8PinID < 8){
            if(Copy_u8Value == HIGH || Copy_u8Value == LOW){
                switch(Copy_u8PortID){
                case PORTA:
                    switch(Copy_u8Value){
                    case LOW:   CLR_BIT(GPIO_APB_PORTF_GPIODATA, Copy_u8PinID);  break;
                    case HIGH:  SET_BIT(GPIO_APB_PORTF_GPIODATA, Copy_u8PinID);  break;
                    }
                    break;
                case PORTB:
                    switch(Copy_u8Value){
                    case LOW:   CLR_BIT(GPIO_APB_PORTF_GPIODATA, Copy_u8PinID);  break;
                    case HIGH:  SET_BIT(GPIO_APB_PORTF_GPIODATA, Copy_u8PinID);  break;
                    }
                    break;
                case PORTC:
                    switch(Copy_u8Value){
                    case LOW:   CLR_BIT(GPIO_APB_PORTF_GPIODATA, Copy_u8PinID);  break;
                    case HIGH:  SET_BIT(GPIO_APB_PORTF_GPIODATA, Copy_u8PinID);  break;
                    }
                    break;
                case PORTD:
                    switch(Copy_u8Value){
                    case LOW:   CLR_BIT(GPIO_APB_PORTF_GPIODATA, Copy_u8PinID);  break;
                    case HIGH:  SET_BIT(GPIO_APB_PORTF_GPIODATA, Copy_u8PinID);  break;
                    }
                    break;
                case PORTE:
                    switch(Copy_u8Value){
                    case LOW:   CLR_BIT(GPIO_APB_PORTF_GPIODATA, Copy_u8PinID);  break;
                    case HIGH:  SET_BIT(GPIO_APB_PORTF_GPIODATA, Copy_u8PinID);  break;
                    }
                    break;
                case PORTF:
                    switch(Copy_u8Value){
                    case LOW:   CLR_BIT(GPIO_APB_PORTF_GPIODATA, Copy_u8PinID);  break;
                    case HIGH:  SET_BIT(GPIO_APB_PORTF_GPIODATA, Copy_u8PinID);  break;
                    }
                    break;
                }
            }
            else{
                /* Return Error */
            }
        }
        else{
            /* Return Error */
        }
    }
    else{
        /* Return Error */
    }
}

uint8 GPIO_u8GetPinValue(uint8 Copy_u8PortID, uint8 Copy_u8PinID){
    if(Copy_u8PortID >= 0 && Copy_u8PortID < 6){
            if(Copy_u8PinID >= 0 && Copy_u8PinID < 8){
                    switch(Copy_u8PortID){
                    case PORTA: return GET_BIT(GPIO_APB_PORTA_GPIODATA, Copy_u8PinID);
                    case PORTB: return GET_BIT(GPIO_APB_PORTB_GPIODATA, Copy_u8PinID);
                    case PORTC: return GET_BIT(GPIO_APB_PORTC_GPIODATA, Copy_u8PinID);
                    case PORTD: return GET_BIT(GPIO_APB_PORTD_GPIODATA, Copy_u8PinID);
                    case PORTE: return GET_BIT(GPIO_APB_PORTE_GPIODATA, Copy_u8PinID);
                    case PORTF: return GET_BIT(GPIO_APB_PORTF_GPIODATA, Copy_u8PinID);
                    }
            }
            else{
                /* Return Error */
            }
        }
        else{
            /* Return Error */
        }
}

#elif BUS_ID == AHB


#else
    #error("Bus ID is out of range")

#endif


