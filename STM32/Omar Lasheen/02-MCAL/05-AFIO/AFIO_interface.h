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

#define SPI1_MASTER 0
#define SPI1_SLAVE 1

#define SPI1_MODE SPI1_MASTER

/***************   Function definition    ******************/
void	MAFIO_voidSetEXTIConfiguration(u8 Copy_u8Line ,u8 Copy_u8PortMap);
void AFIO_voidSetEXTIConfiguration (u8 Copy_u8EXTI_Line, u8 Copy_u8PortMap);
void AFIO_voidRemapPeripheralPins (u8 Copy_u8Port);

#endif // AFIO_INTERFACE_H
