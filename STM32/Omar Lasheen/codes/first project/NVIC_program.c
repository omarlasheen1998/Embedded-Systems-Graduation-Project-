/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 5 OCT  2020                                                       */
/*********************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "NVIC_interface.h"
#include "NVIC_config.h"
#include "NVIC_private.h"


/*************	 Function OF Enable Interrupt  **************************/

void NVIC_voidEnableInterrupt(u8 Copy_u8IntNumber)
{
	if (Copy_u8IntNumber <= 31 )
	{
		NVIC_ISER0 = (1 << Copy_u8IntNumber);
	}
	else if (Copy_u8IntNumber <= 59)
	{
		Copy_u8IntNumber -= 32;
		NVIC_ISER1 = (1 << Copy_u8IntNumber);
	}
	else
	{
		/* Return error */
	}
}

/*************	 Function OF Disable Interrupt  *************************/

void NVIC_voidDisableInterrupt(u8 Copy_u8IntNumber)
{
	if (Copy_u8IntNumber <= 31 )
	{
		NVIC_ICER0 = (1 << Copy_u8IntNumber);
	}
	else if (Copy_u8IntNumber <= 59)
	{
		Copy_u8IntNumber -= 32;
		NVIC_ICER1 = (1 << Copy_u8IntNumber);
	}
	else
	{
		/* Return error */
	}
}

/*************	 Function OF Set Pending Flag  **************************/

void NVIC_voidSetPendingFlag(u8 Copy_u8IntNumber)
{
	if (Copy_u8IntNumber <= 31 )
	{
		NVIC_ISPR0 = (1 << Copy_u8IntNumber);
	}
	else if (Copy_u8IntNumber <= 59)
	{
		Copy_u8IntNumber -= 32;
		NVIC_ISPR1 = (1 << Copy_u8IntNumber);
	}
	else
	{
		/* Return error */
	}
}

/*************	 Function OF Clear Pending Flag  *************************/

void NVIC_voidClearPendingFlag(u8 Copy_u8IntNumber)
{
	if (Copy_u8IntNumber <= 31 )
	{
		NVIC_ICPR0 = (1 << Copy_u8IntNumber);
	}
	else if (Copy_u8IntNumber <= 59)
	{
		Copy_u8IntNumber -= 32;
		NVIC_ICPR1 = (1 << Copy_u8IntNumber);
	}
	else
	{
		/* Return error */
	}
}

/*************	 Function OF Get Active Flag  *************************/

u8 NVIC_u8GetActiveFlag(u8 Copy_u8IntNumber)
{
	u8 Local_u8Result;
	if (Copy_u8IntNumber <= 31 )
	{
		Local_u8Result = GET_BIT(NVIC_IABR0, Copy_u8IntNumber);
	}
	else if (Copy_u8IntNumber <= 59)
	{
		Copy_u8IntNumber -= 32;
		Local_u8Result = GET_BIT(NVIC_IABR1, Copy_u8IntNumber);
	}
	else
	{
		/* Return error */
	}
	return Local_u8Result;
}

/*************	 Function OF Set Priority  *************************/

void  NVIC_voidSetPrioity(u8 Copy_PeripheralIdx, u8 Copy_u8GroupPriority, u8 Copy_u8SubPriority)
{
					  /* EX: 0x05FA0400 3 Group & 1 sub priority */
	u8 Local_u8Priority = Copy_u8SubPriority | (Copy_u8GroupPriority << ((NVIC_GROUP_SUB_DISTRIBUTION - 0x05FA0300)/256));

	/* external peripheral		*/ /*EXTI0 = 6*/
	if (Copy_PeripheralIdx < 60 )
	{
		NVIC_IPR[Copy_PeripheralIdx] = Local_u8Priority << 4;
	}
	else
	{
		/* Report Error */
	}
	SCB_AIRCR = NVIC_GROUP_SUB_DISTRIBUTION;
}


