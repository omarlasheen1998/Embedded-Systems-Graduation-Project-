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

void AFIO_voidSetEXTIConfiguration (uint8 Copy_uint8Line, uint8 Copy_uint8PortMap)
{
	uint8 Local_uint8RegIndex = 0;
	/* Assign to EXTICRx register */
	Local_uint8RegIndex = Copy_uint8Line / 4;
	Copy_uint8Line = Copy_uint8Line % 4 ;

	AFIO->EXTICR[Local_uint8RegIndex] &= ~((0b1111) 		 << (Copy_uint8Line * 4));
	AFIO->EXTICR[Local_uint8RegIndex] |=  ((Copy_uint8PortMap) << (Copy_uint8Line * 4));
}

/*************	 Function OF remapping pins   **************************/

void AFIO_voidRemapPeripheralPins (uint8 Copy_uint8Port){

switch(Copy_uint8Port){

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


void AFIO_voidRemap_CAN (void)
{
    /* BIT (14:13)=10;
                        CAN_RX mapped to PB8,
                        CAN_TX mapped to PB9  */
//    SET_BIT(AFIO->MAPR,14);
//    CLR_BIT(AFIO->MAPR,13);
    SET_BIT(AFIO->MAPR,14);
    CLR_BIT(AFIO->MAPR,13);
}
