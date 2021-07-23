#include "STD_TYPES.h"
#ifndef TIMER_INTERFACE_H
#define TIMER_INTERFACE_H

void TIMER_voidInit(uint8 Copy_u8TIMERID);
void TIMER_start(uint8 Copy_u8TIMERID,Copy_reloadvalue,void (*Copy_ptr) (void));
void TIMER_stop(uint8 Copy_u8TIMERID);
uint32 Get_Elapsedtime(uint8 Copy_u8TIMERID);
uint64 MICROS();
uint64 MILLIS();
void START_MICROS(uint8 Copy_u8TIMERID);
void START_MILLIS(uint8 Copy_u8TIMERID);



#endif
