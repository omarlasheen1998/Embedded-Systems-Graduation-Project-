#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "RCC_interface.h"

#include "USART_INTERFACE.h"
#include "STK_interface.h"
#include "AFIO_interface.h"
#include "NVIC_interface.h"

#include "I2C_interface.h"


#define SLAVE_ADDRESS 0x40 

 u8 character[20] ="AHMED ADEL#";
 u8 y[20],*z;



void DMA_CallBack(void){

	if( MDMA1_u8GetFlag( CHANNEL7 , DMA_TCIF ) == 1 ){
		USART_voidTransmit(UART3,"Slave receive: ",STRING);
		USART_voidTransmit(UART3,&y,CHAR);
		USART_voidTransmit(UART3,"\n",STRING);
		
		
		STK_voidDelay_ms(1000);
		GPIO_voidSetPinValue(GPIOC,13,HIGH);

		STK_voidDelay_ms(1000);
		GPIO_voidSetPinValue(GPIOC,13,LOW);
		
		MDMA1_VidClearFlag    ( CHANNEL7 , DMA_TCIF );


	}

}


int main(void){
	
	/* first we will operate on the pll mode in rcc with internal clock 8mhz*/
	RCC_voidInitSysClock(); /* INITIALIZE THE SYSTEM CLOCK TO BE 72 MHZ BY CHOOSING AN EXTERNAL CLOCK 16MHZ AND CHOOSE HSE/2
	AND THE MULTIPLIED NUMBER IN PLL IS 9 TO GET THE 72MHZ */
	
	RCC_voidEnableClock(RCC_APB2,0);/*ENABLE AFIO AS IO PINS*/
	
	RCC_voidEnableClock(RCC_APB2,2);/*ENABLE PORTA AS IO PINS*/
	RCC_voidEnableClock(RCC_APB2,3);/*ENABLE PORTB AS IO PINS*/
	RCC_voidEnableClock(RCC_APB2,4);/*ENABLE PORTC AS IO PINS*/
	

	RCC_voidEnableClock(RCC_APB1,18);/*ENABLE USART3 */
	
	RCC_voidEnableClock(RCC_APB1,21);/*ENABLE I2C1 */
	
	RCC_voidEnableClock(RCC_AHB,0);/*ENABLE DMA1 */
	
	USART_voidInit(UART3,9600);
	
	
	GPIO_voidSetPinDirection(GPIOC,13,OUTPUT_SPEED_50MHZ_PP);
	
	//#if 1
	MDMA1_VidSetCallBackChannel7   ( DMA_CallBack );
	MDMA1_VidSetConfiguration      ( CHANNEL7 , PREI_TO_MEM , DMA_DISABLE_CIRCULAR , PERIPHERAL_INCREMENT_DISABLE ,
																																	MEM_INCREMENT_ENABLE , BYTE , BYTE , DMA_MEDIUM );
	//MDMA1_VidSetAddress            ( CHANNEL7 , &( I2C1 -> DR ) , &( y ) , 1 );
	//MDMA1_VidInerruptEnable        ( CHANNEL7 , DMA_TCIE );	
	//MDMA1_VidDMAEnable             ( CHANNEL7);
	#if 0
	NVIC_voidSetPrioity          ( DMA_CHANNEL7_ID , 1 , NO_SUB_PRIORITY );
	NVIC_voidEnableInterrupt     ( DMA_CHANNEL7_ID );
	#endif

I2C_Slave_init(MI2C1,400000,SLAVE_ADDRESS); 

u8 x[10] = "OMAR";
//x='O';
//z=&x;
while(1)
{
GPIO_voidSetPinValue(GPIOC,13,LOW);

	I2C_SlaveReadData(MI2C1,y,7,0);
	
	I2C_SlaveSendData(MI2C1,character,11,1);
	I2C_slave_Check_StopBit();
	
#if 0 
do
{
if(I2C_SlaveListen(MI2C1) == I2C_EVENT_SLAVE_STOP_DETECTED)
	break;
}while(1);	

#endif
		

#if 1
	USART_voidTransmit(UART3,"slave receive: ",STRING);
	USART_voidTransmit(UART3,y,STRING);
USART_voidTransmit(UART3,"\n",STRING);
#if 1
	USART_voidTransmit(UART3,"slave send: ",STRING);
  USART_voidTransmit(UART3,character,STRING);
	USART_voidTransmit(UART3,"\n",STRING);
#endif
	STK_voidDelay_ms(1000);
		GPIO_voidSetPinValue(GPIOC,13,HIGH);

		STK_voidDelay_ms(1000);
		GPIO_voidSetPinValue(GPIOC,13,LOW);
 

#endif

}


}