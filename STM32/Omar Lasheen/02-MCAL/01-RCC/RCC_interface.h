/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 22 SEP 2020                                                       */
/*********************************************************************************/
#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H

#define RCC_AHB     0
#define RCC_APB1    1
#define RCC_APB2    2

/***************   Function definition    ******************/

void RCC_voidInitSysClock(void);
void RCC_voidEnableClock(uint8 Copy_u8BusId, uint8 Copy_u8PerId);
void RCC_voidDisableClock(uint8 Copy_u8BusId, uint8 Copy_u8PerId);

#endif // RCC_INTERFACE_H
