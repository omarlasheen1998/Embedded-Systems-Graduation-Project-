#include "STD_TYPES.h"
#ifndef TIMER_INTERFACE_H
#define TIMER_INTERFACE_H

void TIMER_voidInit(u8 Copy_u8TIMERID);
void TIMER_start(u8 Copy_u8TIMERID,u32 Copy_reloadvalue,void (*Copy_ptr) (void));
void TIMER_stop(u8 Copy_u8TIMERID);
u32 Get_Elapsedtime(u8 Copy_u8TIMERID,u32  Copy_reloadvalue);
u64 MICROS(u8 Copy_u8TIMERID);
u64 MILLIS(u8 Copy_u8TIMERID);
void START_MICROS(u8 Copy_u8TIMERID);
void START_MILLIS(u8 Copy_u8TIMERID);
void Delay_In_Us(u8 Copy_u8TIMERID,u32 Copy_numberofus);
void Delay_In_Ms(u8 Copy_u8TIMERID,u32 Copy_numberofms);



#endif
