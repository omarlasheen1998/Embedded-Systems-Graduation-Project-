/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 11 OCT  2020                                                      */
/*********************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_config.h"
#include "EXTI_private.h"


/* define Callback Global variable (pointer to function) */
static void (*EXTI_CallBack) (void);



/*************	 Function OF Initialize EXTI  **************************/

void EXTI_voidInit ()
{
	#if 		EXTI_MODE == RISING_EDGE
		SET_BIT(EXTI -> RTSR, EXTI_LINE);
	#elif 		EXTI_MODE == FALLING_EDGE
		SET_BIT(EXTI -> FTSR, EXTI_LINE);
	#elif 		EXTI_MODE == ON_CHANGE
		SET_BIT(EXTI -> RTSR, EXTI_LINE);
		SET_BIT(EXTI -> FTSR, EXTI_LINE);
	#else
		#error "Wrong Mode and Line choice"
	#endif
	/* Disable interrupt */
	CLR_BIT(EXTI->IMR , EXTI_LINE);
}

/*************	 Function OF Set Signal Latch  **********************/

void EXTI_voidSetSignalLatch (uint8 Copy_u8EXTILine, uint8 Copy_u8EXTISenseMode)
{
	switch(Copy_u8EXTISenseMode)
	{
		case RISING_EDGE	:	 SET_BIT(EXTI -> RTSR, EXTI_LINE);	 	break;
		case FALLING_EDGE	:	 SET_BIT(EXTI -> FTSR, EXTI_LINE);	 	break;
		case ON_CHANGE  	:	 SET_BIT(EXTI -> RTSR, EXTI_LINE);
								 SET_BIT(EXTI -> FTSR, EXTI_LINE);	 	break;
	}
	SET_BIT(EXTI->IMR , Copy_u8EXTILine);
}

/*************	 Function OF Enable EXTI  ***************************/

void EXTI_voidEnableEXTI(uint8 Copy_u8EXTILine)
{
	SET_BIT(EXTI->IMR , Copy_u8EXTILine);
}

/*************	 Function OF Disable EXTI  **************************/

void EXTI_voidDisableEXTI(uint8 Copy_u8EXTILine)
{
	CLR_BIT(EXTI->IMR , Copy_u8EXTILine);
}

/*************	 Function OF SoftWare Trigger  **********************/

void EXTI_voidSoftWareTrigger(uint8 Copy_u8EXTILine)
{
	SET_BIT(EXTI->SWIER , Copy_u8EXTILine);
}

/*************	 Function OF Set CallBack  **********************/

void EXTI_voidSetCallBack (void (*ptr) (void))
{
	EXTI_CallBack = ptr;
}

/*************	 Function OF EXTI0 Interrupt  **************************/
/* This is function call a EXTI_CallBack() function to do when interrupt */

void EXTI0_IRQHandler (void)
{
	EXTI_CallBack();
	/*	Clear pending Bit		*/
	SET_BIT(EXTI->PR , EXTI_LINE0);

}
