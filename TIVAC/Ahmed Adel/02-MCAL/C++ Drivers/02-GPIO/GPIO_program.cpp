/********************************************/
/* Author   : Ahmed Ismail                  */
/* Date     : 10 SEP 2020                   */
/* Version  : V01                           */
/********************************************/

#include "01-LIB/01-STD_TYPES/STD_TYPES.h"
#include "01-LIB/02-BIT_MATH/BIT_MATH.h"

#include "02-MCAL/C++ Drivers/02-GPIO/GPIO_Class.h"
#include "02-MCAL/C++ Drivers/02-GPIO/GPIO_private.h"
#include "02-MCAL/C++ Drivers/02-GPIO/GPIO_config.h"


void Pin::GPIO_voidEnableClock(uint8 Copy_u8PortID){
    #if OPERATION_MODE == RUN_MODE
        if(Copy_u8PortID >= 0 && Copy_u8PortID < 6){
            if(!portClockFlags[Copy_u8PortID]){
                SYSCTL_RCGCGPIO |= (1 << Copy_u8PortID);
                uint8 clocksDelay = 0;
                portClockFlags[Copy_u8PortID] = 1;
            }
            else {
                return;
            }
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

void Pin::GPIO_voidDisableClock(uint8 Copy_u8PortID){
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

uint8 Pin::GPIO_u8CheckLockedPin(uint8 Copy_u8PortID, uint8 Copy_u8PinID){
    switch(Copy_u8PortID){
    case PORTA :
        switch (Copy_u8PinID) {
            case PIN0:  return 1;
            case PIN1:  return 1;
            default:    return 0;
        }
    case PORTB :
        switch (Copy_u8PinID) {
            case PIN2:  return 1;
            case PIN3:  return 1;
            case PIN4:  return 1;
            case PIN5:  return 1;
            default:    return 0;
        }
    case PORTC :
        switch (Copy_u8PinID) {
            case PIN0:  return 1;
            case PIN1:  return 1;
            case PIN2:  return 1;
            case PIN3:  return 1;
            default:    return 0;
         }
    case PORTD :
        switch (Copy_u8PinID) {
            case PIN7:  return 1;
            default:    return 0;
         }
    case PORTF :
        switch (Copy_u8PinID) {
            case PIN0:  return 1;
            default:    return 0;
         }
    default:    return 0;
    }

}


#if BUS_ID == APB
void Pin::GPIO_voidSetPinDirection(uint8 Copy_u8PortID, uint8 Copy_u8PinID, uint8 Copy_u8Direction){
    if(Copy_u8PortID >= 0 && Copy_u8PortID < 6){
        if(Copy_u8PinID >= 0 && Copy_u8PinID < 8){
            if(Copy_u8Direction == OUTPUT || Copy_u8Direction == INPUT || Copy_u8Direction == INPUT_PULLDOWN || Copy_u8Direction == INPUT_PULLUP){
                this->portID = Copy_u8PortID;
                this->pinID = Copy_u8PinID;
                this->pinMode = Copy_u8Direction;
                switch(Copy_u8PortID){
                    case PORTA:
                        if(GPIO_u8CheckLockedPin(Copy_u8PortID, Copy_u8PinID)){
                            GPIO_APB_PORTA_GPIOLOCK = PORT_LOCK;
                            GPIO_APB_PORTA_GPIOCR       |=   (1 << Copy_u8PinID);
                        }
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
                        this->pinSetFlag = 1;
                        break;
                    case PORTB:
                        if(GPIO_u8CheckLockedPin(Copy_u8PortID, Copy_u8PinID)){
                            GPIO_APB_PORTB_GPIOLOCK = PORT_LOCK;
                            GPIO_APB_PORTB_GPIOCR       |=   (1 << Copy_u8PinID);
                        }
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
                        this->pinSetFlag = 1;
                        break;
                   case PORTC:
                       if(GPIO_u8CheckLockedPin(Copy_u8PortID, Copy_u8PinID)){
                           GPIO_APB_PORTC_GPIOLOCK = PORT_LOCK;
                           GPIO_APB_PORTC_GPIOCR       |=   (1 << Copy_u8PinID);
                       }
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
                       this->pinSetFlag = 1;
                       break;
                   case PORTD:
                       if(GPIO_u8CheckLockedPin(Copy_u8PortID, Copy_u8PinID)){
                           GPIO_APB_PORTD_GPIOLOCK = PORT_LOCK;
                           GPIO_APB_PORTD_GPIOCR       |=   (1 << Copy_u8PinID);
                       }
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
                       this->pinSetFlag = 1;
                       break;
                  case PORTE:
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
                      this->pinSetFlag = 1;
                      break;
                  case PORTF:
                      if(GPIO_u8CheckLockedPin(Copy_u8PortID, Copy_u8PinID)){
                          GPIO_APB_PORTF_GPIOLOCK = PORT_LOCK;
                          GPIO_APB_PORTF_GPIOCR       |=   (1 << Copy_u8PinID);
                      }
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
                      this->pinSetFlag = 1;
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

void Pin::GPIO_voidSetPinValue(uint8 Copy_u8PortID, uint8 Copy_u8PinID, uint8 Copy_u8Value){
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

uint8 Pin::GPIO_u8GetPinValue(uint8 Copy_u8PortID, uint8 Copy_u8PinID){
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




 Pin::Pin(uint8 Copy_u8PinID, uint8 Copy_u8PortID, uint8 Copy_u8Mode){
     if(Copy_u8PortID >= PORTA && Copy_u8PortID <= PORTF){
         GPIO_voidEnableClock(Copy_u8PortID);
         GPIO_voidSetPinDirection(Copy_u8PortID, Copy_u8PinID, Copy_u8Mode);
     }
     else{
         /* Return Error */
     }
 }

 uint8 Pin::pinWrite(uint8 Copy_u8Value){
     if(this->pinSetFlag == 1){
         if(Copy_u8Value == HIGH || Copy_u8Value == LOW){
             GPIO_voidSetPinValue(portID, pinID, Copy_u8Value);
             return 0;
         }
         else{
             /* Return Error */
             return 1;
         }
     }
     else{
         /* Return Error */
         return 1;
     }
 }


 uint8 Pin::pinRead(){
     if(this->pinSetFlag == 1){
         return GPIO_u8GetPinValue(portID, pinID);
     }
     else{
         /* Return Error */
     }
 }




