/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 5 OCT  2020                                                       */
/*********************************************************************************/
#include "STD_TYPES.h"
#ifndef NVIC_INTERFACE_H
#define NVIC_INTERFACE_H

#define NO_SUB_PRIORITY 0


#define GROUP3     0x05FA0300//0 bit for sub & 4 bit For group   << 0


#define DMA_ID 11
#define DMA_CHANNEL7_ID 17


/***************   Function definition    ******************/

void  NVIC_voidEnableInterrupt 	(u8 Copy_u8IntNumber);
void  NVIC_voidDisableInterrupt	(u8 Copy_u8IntNumber);
void  NVIC_voidSetPendingFlag	(u8 Copy_u8IntNumber);
void  NVIC_voidClearPendingFlag	(u8 Copy_u8IntNumber);
u8 NVIC_u8GetActiveFlag		(u8 Copy_u8IntNumber);
void  NVIC_voidSetPrioity		(u8 Copy_PeripheralIdx, u8 Copy_u8GroupPriority, u8 Copy_u8SubPriority);



#endif // NVIC_INTERFACE_H
