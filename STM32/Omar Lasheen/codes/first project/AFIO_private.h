/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 11 OCT  2020                                                      */
/*********************************************************************************/
#include "STD_TYPES.h"

#ifndef AFIO_PRIVATE_H
#define AFIO_PRIVATE_H


/*******************   Register Definition     ***********************/

typedef struct
{
	volatile u32 EVCR;
	volatile u32 MAPR;
	volatile u32 EXTICR[4];
	volatile u32 MAPR2;
}AFIO_t;

#define AFIO 		((volatile AFIO_t *) 0x40010000)


#endif // AFIO_PRIVATE_H
