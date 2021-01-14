/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 5 OCT  2020                                                       */
/*********************************************************************************/
#ifndef NVIC_INTERFACE_H
#define NVIC_INTERFACE_H





/***************   Function definition    ******************/

void  NVIC_voidEnableInterrupt 	(uint8 Copy_u8IntNumber);
void  NVIC_voidDisableInterrupt	(uint8 Copy_u8IntNumber);
void  NVIC_voidSetPendingFlag	(uint8 Copy_u8IntNumber);
void  NVIC_voidClearPendingFlag	(uint8 Copy_u8IntNumber);
uint8 NVIC_u8GetActiveFlag		(uint8 Copy_u8IntNumber);
void  NVIC_voidSetPrioity		(uint8 Copy_PeripheralIdx, uint8 Copy_u8GroupPriority, uint8 Copy_u8SubPriority);



#endif // NVIC_INTERFACE_H
