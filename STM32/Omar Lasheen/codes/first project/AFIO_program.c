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
	   #if SPI1_MODE == SPI1_MASTER
	GPIOB_CRL  &= ~(0xFFF00000);
	GPIOB_CRL  |= (0xB4B00000);			
     #elif SPI1_MODE == SPI1_SLAVE
	GPIOB_CRL  &= ~(0xFFFF0000);
	GPIOB_CRL  |= (0x44B40000);			
		#endif
	break;
	
}

}


void	MAFIO_voidSetEXTIConfiguration(uint8 Copy_u8Line ,uint8 Copy_u8PortMap)
{
	uint8 Local_u8RegIndex = 0 ;
	/* Assign to EXTICRX register									*/
	if(Copy_u8Line <= 3 )
	{
			Local_u8RegIndex = 0;
	}
	else if(Copy_u8Line<=7)
	{
			/*	another	solution									*/
			/*	line 7 => 1.... 									*/
			/*	Local_u8RegIndex = copy_u8Line/4					*/
			/*	copy_u8Line = copy_u8Line%4 => (3 in the EXTICR2)	*/
		Local_u8RegIndex = 1;
		Copy_u8Line -= 4;
	}
	else if(Copy_u8Line<=11)
	{
		Local_u8RegIndex = 2;
		Copy_u8Line -= 8;

	}
	else if(Copy_u8Line<=15)
	{
		Local_u8RegIndex = 3;
		Copy_u8Line -= 12;
	}
	AFIO->EXTICR[Local_u8RegIndex] &= ~((0b1111) << (Copy_u8Line * 4));
	AFIO->EXTICR[Local_u8RegIndex]  |= ((Copy_u8PortMap) << (Copy_u8Line * 4));
}
