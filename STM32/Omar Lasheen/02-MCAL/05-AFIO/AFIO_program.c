/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 11 OCT  2020                                                      */
/*********************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "AFIO_interface.h"
#include "AFIO_config.h"
#include "AFIO_private.h"


/*************	 Function OF Set EXTI Configuration  **************************/

void AFIO_voidSetEXTIConfiguration (uint8 Copy_u8Line, uint8 Copy_u8PortMap)
{
	uint8 Local_u8RegIndex = 0;
	/* Assign to EXTICRx register */
	Local_u8RegIndex = Copy_u8Line / 4;
	Copy_u8Line = Copy_u8Line % 4 ;

	AFIO->EXTICR[Local_u8RegIndex] &= ~((0b1111) 		 << (Copy_u8Line * 4));
	AFIO->EXTICR[Local_u8RegIndex] |=  ((Copy_u8PortMap) << (Copy_u8Line * 4));
}


