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
#include "GPIO_private.h"


/*************	 Function OF Set EXTI Configuration  **************************/

void AFIO_voidSetEXTIConfiguration (u8 Copy_u8Line, u8 Copy_u8PortMap)
{
	u8 Local_u8RegIndex = 0;
	/* Assign to EXTICRx register */
	Local_u8RegIndex = Copy_u8Line / 4;
	Copy_u8Line = Copy_u8Line % 4 ;

	AFIO->EXTICR[Local_u8RegIndex] &= ~((0b1111) 		 << (Copy_u8Line * 4));
	AFIO->EXTICR[Local_u8RegIndex] |=  ((Copy_u8PortMap) << (Copy_u8Line * 4));
}


void AFIO_voidRemapPeripheralPins (u8 Copy_u8Port){

switch(Copy_u8Port){

	 case UART1:
		AFIO->MAPR|=1<<2;
    GPIOA_CRH&=~0x00000FF0;
    GPIOA_CRH|= 0x00000440; 	// RX1=input with pull-up, TX1=alt. func output	
	 GPIOB_CRL   &= ~(0xFF000000UL);
	 GPIOB_CRL   |= 0x8B000000UL;			// Configure PB6 and PB7
	 GPIOB_ODR |= 0x1UL << 7;
	 break;
	case CAN:
	AFIO->MAPR   &= 0xFFFF9FFF;   	// reset CAN remap
	AFIO->MAPR   |= 0x00004000;   	//  et CAN remap, use PB8, PB9	
	
	GPIOB_CRH   &= ~(0xFFUL);
	GPIOB_CRH   |= 0xB8UL;			// Configure PB8 and PB9
	GPIOB_ODR |= 0x1UL << 8;
	break;
	case I2C1:
		AFIO->MAPR|=1<<1;
	 break;
	case SPI1:
		AFIO->MAPR|=1<<0;
	 break;
	




}




}
