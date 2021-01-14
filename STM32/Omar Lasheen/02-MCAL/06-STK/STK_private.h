/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 17 OCT  2020                                                      */
/*********************************************************************************/
#ifndef STK_PRIVATE_H
#define STK_PRIVATE_H

/*******************   BASE Address Definition    *********************/

#define STK_BASE_ADDRESS	0xE000E010 		//define the boundary address of STK

/*******************   Register Definition     ***********************/

typedef struct
{
	volatile uint32 CTRL;
	volatile uint32 LOAD;
	volatile uint32 VAL;
	volatile uint32 CALIB;
}STK_t;

#define STK			((volatile STK_t *) STK_BASE_ADDRESS)

/******************   STK Clock Source Definition   ******************/

#define STK_SRC_AHB_8				0
#define STK_SRC_AHB					1

/******************   STK interval mode Definition   ******************/

#define STK_SINGLE_INTERVAL			0
#define STK_PERIOD_INTERVAL			1

#endif /* STK_PRIVATE_H */
