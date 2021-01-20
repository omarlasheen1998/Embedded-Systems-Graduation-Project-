/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 17 OCT  2020                                                      */
/*********************************************************************************/
#ifndef STK_INTERFACE_H
#define STK_INTERFACE_H



/***************   Function definition    ******************/

void   STK_voidInit					(void);
void   STK_voidSetBusyWait			(uint32 Copy_u32Ticks);
void   STK_voidSetIntervalSingle	(uint32 Copy_u32Ticks, void (*Copy_ptr) (void));
void   STK_voidSetIntervalPeriodic	(uint32 Copy_u32Ticks, void (*Copy_ptr) (void));
void   STK_voidStopInterval			(void);
uint32 STK_u32GetElapedTime			(void);
uint32 STK_u32GetRemainingTime		(void);

void   STK_voidDelay_ms				(uint32 Copy_u32Ticks);

#endif /* STK_INTERFACE_H */
