/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 11 OCT  2020                                                      */
/*********************************************************************************/
#include "STD_TYPES.h"

#ifndef AFIO_PRIVATE_H
#define AFIO_PRIVATE_H

/*******************   BASE Address Definition    *********************/

#define AFIO_BASE_ADDRESS	0x40010000 		//define the boundary address of AFIO

/*******************   Register Definition     ***********************/

typedef struct
{
	volatile uint32 EVCR;
	volatile uint32 MAPR;
	volatile uint32 EXTICR[4];
	volatile uint32 MAPR2;
}AFIO_t;

#define AFIO 		((volatile AFIO_t *) AFIO_BASE_ADDRESS)


#endif // AFIO_PRIVATE_H
