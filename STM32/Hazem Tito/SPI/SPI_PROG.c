


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "SPI_INTERFACE.h"
#include "SPI_CONFIG.h"
#include "SPI_PRIVATE.h"
#include "GPIO_interface.h"
#include "NVIC_interface.h"

void (*MSPI1_CallBack) (void);
void (*MSPI2_CallBack) (void);
u8 configure_SPI1,configure_SPI2;

void MSPI_voidInit( u8 SPI_TYPE, u8 SPI_Configuaration)
{

if(SPI_TYPE == SPI1)
{	

#if		MSPI1_CLOCK_MODE == MSPI_MODE0 //CPOL=0 CPHA=0

	CLR_BIT( MSPI1 -> CR1 , 0 ); CLR_BIT( MSPI1 -> CR1 , 1 );

#elif	MSPI1_CLOCK_MODE == MSPI_MODE1 //CPOL=0 CPHA=1

	SET_BIT( MSPI1 -> CR1 , 0 ); CLR_BIT( MSPI1 -> CR1 , 1 );

#elif	MSPI1_CLOCK_MODE == MSPI_MODE2 //CPOL=1 CPHA=0

	CLR_BIT( MSPI1 -> CR1 , 0 ); SET_BIT( MSPI1 -> CR1 , 1 );

#elif	MSPI1_CLOCK_MODE == MSPI_MODE3 //CPOL=1 CPHA=1

	SET_BIT( MSPI1 -> CR1 , 0 ); SET_BIT( MSPI1 -> CR1 , 1 );

#endif


#if   MSPI1_DATA_ORDER == MSPI_MSB_FIRST

	CLR_BIT( MSPI1 -> CR1 , 7 );

#elif MSPI1_DATA_ORDER == MSPI_LSB_FIRST

	SET_BIT( MSPI1 -> CR1 , 7 );

#endif

#if   MSPI1_SS_MANAGE  == HW_SLAVE_MANAGEMENT

	CLR_BIT( MSPI1 -> CR1 , 9 );

#elif MSPI1_SS_MANAGE == SW_SLAVE_MANAGEMENT

	SET_BIT( MSPI1 -> CR1 , 9 );

#endif

#if   MSPI1_DATA_SIZE == MSPI_8BIT_DATA

	CLR_BIT( MSPI1 -> CR1 , 11 );

#elif MSPI1_DATA_SIZE == MSPI_16BIT_DATA

	SET_BIT( MSPI1 -> CR1 , 11 );

#endif


if ( SPI_Configuaration == MSPI_MASTER )
{
	SET_BIT( MSPI1 -> CR1 , 2 );
  configure_SPI1 = SPI_Configuaration;
  
	GPIO_voidSetPinDirection(GPIOA, PIN7, OUTPUT_SPEED_50MHZ_AFPP); //MOSI
	GPIO_voidSetPinDirection(GPIOA, PIN5, OUTPUT_SPEED_50MHZ_AFPP); //SCLK
	GPIO_voidSetPinDirection(GPIOA, PIN6, INPUT_FLOATING); //MISO
	SET_BIT(MSPI1->CR2,2); /* ENABLE SSOE*/
	
}
else if  ( SPI_Configuaration ==  MSPI_SLAVE)
{
	CLR_BIT( MSPI1 -> CR1 , 2 );
  configure_SPI1 = SPI_Configuaration;
  
	GPIO_voidSetPinDirection(GPIOA, PIN7, INPUT_FLOATING); //MOSI
	GPIO_voidSetPinDirection(GPIOA, PIN5, INPUT_FLOATING); //SCLK
	GPIO_voidSetPinDirection(GPIOA, PIN6, OUTPUT_SPEED_50MHZ_AFPP); //MISO
	GPIO_voidSetPinDirection(GPIOA, PIN4, INPUT_FLOATING); // NSS
	
}

	MSPI1 -> CR1 &= 0xFFC7 ;
	MSPI1 -> CR1 |= ( MSPI1_PRESCALLER << 3 ) ;
  CLR_BIT(MSPI1->CR1,10); /* FULL DUPLEX MODE IS USED*/
  CLR_BIT(MSPI2->I2SCFGR, 11);
	SET_BIT( MSPI1 -> CR1 , 6 ); //Enable SPI1

}

else if(SPI_TYPE == SPI2)
{	

#if		MSPI2_CLOCK_MODE == MSPI_MODE0

	CLR_BIT( MSPI2 -> CR1 , 0 ); CLR_BIT( MSPI2 -> CR1 , 1 );

#elif	MSPI2_CLOCK_MODE == MSPI_MODE1

	SET_BIT( MSPI2 -> CR1 , 0 ); CLR_BIT( MSPI2 -> CR1 , 1 );

#elif	MSPI2_CLOCK_MODE == MSPI_MODE2

	CLR_BIT( MSPI2 -> CR1 , 0 ); SET_BIT( MSPI2 -> CR1 , 1 );

#elif	MSPI2_CLOCK_MODE == MSPI_MODE3

	SET_BIT( MSPI2 -> CR1 , 0 ); SET_BIT( MSPI2 -> CR1 , 1 );

#endif


#if   MSPI2_DATA_ORDER == MSPI_MSB_FIRST

	CLR_BIT( MSPI2 -> CR1 , 7 );

#elif MSPI2_DATA_ORDER == MSPI_LSB_FIRST

	SET_BIT( MSPI2 -> CR1 , 7 );

#endif

#if   MSPI2_SS_MANAGE  == HW_SLAVE_MANAGEMENT

	CLR_BIT( MSPI2 -> CR1 , 9 );

#elif MSPI2_SS_MANAGE == SW_SLAVE_MANAGEMENT

	SET_BIT( MSPI2 -> CR1 , 9 );

#endif

#if   MSPI2_DATA_SIZE == MSPI_8BIT_DATA

	CLR_BIT( MSPI2 -> CR1 , 11 );

#elif MSPI2_DATA_SIZE == MSPI_16BIT_DATA

	SET_BIT( MSPI2 -> CR1 , 11 );

#endif


if ( SPI_Configuaration == MSPI_MASTER )
{
	SET_BIT( MSPI2 -> CR1 , 2 );
  configure_SPI2 = SPI_Configuaration;
  
	GPIO_voidSetPinDirection(GPIOB, PIN15, OUTPUT_SPEED_50MHZ_AFPP); //MOSI
	GPIO_voidSetPinDirection(GPIOB, PIN13, OUTPUT_SPEED_50MHZ_AFPP); //SCLK
	GPIO_voidSetPinDirection(GPIOB, PIN14, INPUT_FLOATING); //MISO
}
else if  ( SPI_Configuaration ==  MSPI_SLAVE)
{
	CLR_BIT( MSPI2 -> CR1 , 2 );
  configure_SPI2 = SPI_Configuaration;
  
	GPIO_voidSetPinDirection(GPIOB, PIN14, OUTPUT_SPEED_50MHZ_AFPP); //MISO
	GPIO_voidSetPinDirection(GPIOB, PIN15, INPUT_FLOATING); //MOSI
	GPIO_voidSetPinDirection(GPIOB, PIN13, INPUT_FLOATING); //SCLK
	GPIO_voidSetPinDirection(GPIOB, PIN12, INPUT_FLOATING); //NSS
}
  
	MSPI2 -> CR1 &= 0xFFC7 ;
	MSPI2 -> CR1 |= ( MSPI2_PRESCALLER << 3 ) ;
  CLR_BIT(MSPI2->CR1,10); /* FULL DUPLEX MODE IS USED*/
	SET_BIT(MSPI2->CR2,2); /* ENABLE SSOE*/
	SET_BIT( MSPI2 -> CR1 , 6 );  //Enable SPI2

}


}

u8 MSPI_voidTransferDataU8 ( u8 SPI_TYPE, u8 Copy_u8Data )
{
	u8 rx_val=0;
	
	
 
	if(SPI_TYPE == SPI1)
{
			MSPI1->DR = Copy_u8Data;
     while(MSPI1->SR & 0x80){}
		 while(MSPI1->SR & 0x1){rx_val = MSPI1->DR;}
}


  else if(SPI_TYPE == SPI2)
{

     MSPI2->DR = Copy_u8Data;
     while(MSPI2->SR & 0x80){}
		 while(MSPI2->SR & 0x1){rx_val = MSPI2->DR;}
}

  
return rx_val;  
}


/* function description :
 * this function used to send a byte
 */
void MSPI_voidSendByte(u8 Copy_u8spi,const u8 Copy_u8data){

	switch (Copy_u8spi){
	case SPI1:
		MSPI1->DR=Copy_u8data;
	while(MSPI1->SR & 0x80){}// waiting for BUSY flag is set to indicate that the byte is sent
		break;
	case SPI2:
		MSPI2->DR=Copy_u8data;
		while(MSPI2->SR & 0x80){}// waiting for BUSY flag is set to indicate that the byte is sent
		break;
	}

}

u8 MSPI_u8RecieveByte(u8 Copy_u8spi){
	u8 rx_val=0;
	switch(Copy_u8spi){
	case SPI1:
		while(MSPI1->SR & 0x80){}
		while(MSPI1->SR & 0x1){rx_val = MSPI1->DR;}
		break;
		
	case SPI2:
		while(MSPI2->SR & 0x80){}
		while(MSPI2->SR & 0x1){rx_val = MSPI2->DR;}
		break;
		
	}
	
		return rx_val;
}
/* function description :
 * this function used to send string if it will be received it must send with end of #
 */
void MSPI_voidSendString(u8 Copy_u8spi,const u8 *Copy_u8str){
	u8 i=0;
	switch (Copy_u8spi){
	case SPI1:
		while(Copy_u8str[i]!='\0'){
			MSPI_voidSendByte(SPI1,Copy_u8str[i]);
			i++;
		}
		break;
	case SPI2:
		while(Copy_u8str[i]!='\0'){
			MSPI_voidSendByte(SPI2,Copy_u8str[i]);
			i++;
		}
		break;

	}
}

void MSPI_voidRecieveString(u8 Copy_u8spi,char*str){
	u8 i=0;
	switch(Copy_u8spi){
	case SPI1:
		str[i]=MSPI_u8RecieveByte(SPI1);
		while(str[i]!= '#'){
			i++;
			str[i]=MSPI_u8RecieveByte(SPI1);
		}
		str[i]='\0';
		break;
	case SPI2:
		str[i]=MSPI_u8RecieveByte(SPI2);
		while(str[i]!= '#'){
			i++;
			str[i]=MSPI_u8RecieveByte(SPI2);
		}
		str[i]='\0';
		break;
	}
}


void MSPI_voidLoadData(u8 Copy_u8spi,u8 Copy_u8data){
	switch(Copy_u8spi){
	case SPI1:
		MSPI1->DR=Copy_u8data;
		break;
	case SPI2 :
		MSPI2->DR=Copy_u8data;
		break;
	}
}
u8 MSPI_u8ReturnData(u8 Copy_u8spi){
	switch(Copy_u8spi){
	case SPI1:
		return MSPI1->DR;
		break;
	case SPI2:
		return MSPI2->DR;
		break;
	}
}

void MSPI_voidInterruptInit(u8 SPI_TYPE)
{

if(SPI_TYPE == SPI1)
{

SET_BIT( MSPI1 -> CR2 , 7 ); //SPI1_TXE_INT_ENABLE 
SET_BIT( MSPI1 -> CR2 , 6 ); //SPI1_RXNE_INT_ENABLE

//set SPI1 Global Interrupt
NVIC_voidEnableInterrupt(35);
NVIC_voidSetPendingFlag(35);


}

else if(SPI_TYPE == SPI2)
{
  SET_BIT( MSPI2 -> CR2 , 7 ); //SPI2_TXE_INT_ENABLE
	SET_BIT( MSPI2 -> CR2 , 6 ); //SPI2_RXNE_INT_ENABLE

//set SPI2 Global Interrupt
	NVIC_voidEnableInterrupt(36);
  NVIC_voidSetPendingFlag(36);


}

}
void MSPI1_voidSetCallBack( void (*ptr) (void) ){

	MSPI1_CallBack = ptr;

}


void MSPI2_voidSetCallBack( void (*ptr) (void) ){

	MSPI2_CallBack = ptr;

}

void SPI1_IRQHandler(void){

	MSPI1_CallBack();

}

void SPI2_IRQHandler(void){

	MSPI2_CallBack();

}