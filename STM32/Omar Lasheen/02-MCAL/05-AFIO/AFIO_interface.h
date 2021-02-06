/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 11 OCT  2020                                                      */
/*********************************************************************************/
#include "STD_TYPES.h"

#ifndef AFIO_INTERFACE_H
#define AFIO_INTERFACE_H

#define UART1 1
#define CAN 2
#define I2C1 3
#define SPI1 4



/***************   Function definition    ******************/

void AFIO_voidSetEXTIConfiguration (uint8 Copy_uint8EXTI_Line, uint8 Copy_uint8PortMap);
void AFIO_voidRemapPeripheralPins (uint8 Copy_uint8Port);
void AFIO_voidRemap_CAN (void);

#endif // AFIO_INTERFACE_H
