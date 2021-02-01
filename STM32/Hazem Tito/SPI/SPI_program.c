#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_config.h"
#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "GPIO_config.h"
#include "SPI_interface.h"
#include "SPI_private.h"
#include "SPI_config.h"

void (*Global_PTR_1)(void)='\0';
void (*Global_PTR_2)(void)='\0';


/* function description :
 * this function used to initialize  the microcontroller as a master
 */

void SPI_voidInitMaster(uint8 Copy_u8spi){
	switch (Copy_u8spi){
	case SPI_1 :
		/******* first enable the GPIO and SPI clock by RCC (RCC CONFIGURATION)************/
		SET_BIT(RCC_APB2ENR,2); // ENABLING THE CLOCK OF GPIOA FOR SPI1
		SET_BIT(RCC_APB2ENR,12); // ENABLING THE CLOCK FOR SPI1
		/*********************** second GPIO CONFIGURATION*********************************/
		GPIOA_CRL=0xB4B44444; /* MAKING MOSI(PA7) AND CLOCK(PA5) OUTPUT AND ALTERNATE AND
		MAKE THE MISO(PA6) INPUT*/
		/*******************************SPI CNFIGURATION***********************************/
		CLR_BIT(SPI1_CR1,0); /* THE DATA WILL BE CAPTURED IN THE FIRST CLOCK TRANSITION*/
		CLR_BIT(SPI1_CR1,1); /* CLK TO 0 IN IDLE*/
		SET_BIT(SPI1_CR1,2); /* ENABLE THE MASTER PIN */
#if Baud_Rate==CLK_2
		CLR_BIT(SPI1_CR1,3);
		CLR_BIT(SPI1_CR1,4);
		CLR_BIT(SPI1_CR1,5);
#elif Baud_Rate==CLK_4
		SET_BIT(SPI1_CR1,3);
		CLR_BIT(SPI1_CR1,4);
		CLR_BIT(SPI1_CR1,5);
#elif Baud_Rate==CLK_8
		CLR_BIT(SPI1_CR1,3);
		SET_BIT(SPI1_CR1,4);
		CLR_BIT(SPI1_CR1,5);
#elif Baud_Rate==CLK_16
		SET_BIT(SPI1_CR1,3);
		SET_BIT(SPI1_CR1,4);
		CLR_BIT(SPI1_CR1,5);
#elif Baud_Rate==CLK_32
		CLR_BIT(SPI1_CR1,3);
		CLR_BIT(SPI1_CR1,4);
		SET_BIT(SPI1_CR1,5);
#elif Baud_Rate==CLK_64
		SET_BIT(SPI1_CR1,3);
		CLR_BIT(SPI1_CR1,4);
		SET_BIT(SPI1_CR1,5);
#elif Baud_Rate==CLK_128
		CLR_BIT(SPI1_CR1,3);
		SET_BIT(SPI1_CR1,4);
		SET_BIT(SPI1_CR1,5);
#elif Baud_Rate==CLK_256
		SET_BIT(SPI1_CR1,3);
		SET_BIT(SPI1_CR1,4);
		SET_BIT(SPI1_CR1,5);
#endif

		CLR_BIT(SPI1_CR1,11); /* 8_BIT DATA FORMAT*/
		CLR_BIT(SPI1_CR1,10); /* FULL DUPLEX MODE IS USED*/
		CLR_BIT(SPI1_CR1,9); /*NSS HARDWARE*/
		//SET_BIT(SPI1_CR2,2);
		SET_BIT(SPI1_CR1,6); 		/* ENABLING THE SPI UNIT*/


		break;
	case SPI_2 :
		/********* first enable the GPIO and SPI clock by RCC(RCC CONFIGURATION)***********/
		SET_BIT(RCC_APB2ENR,3); // ENABLING THE CLOCK OF GPIOB FOR SPI2
		SET_BIT(RCC_APB1ENR,14); // ENABLING THE CLOCK FOR SPI2
		/*********************** second GPIO CONFIGURATION*********************************/
		GPIOB_CRH=0xB4B44444;/* MAKING MOSI(PB15) AND CLOCK(PB13) OUTPUT AND ALTERNATE AND
		MAKE THE MISO(PB14) INPUT*/
		/*******************************SPI CNFIGURATION***********************************/
		CLR_BIT(SPI2_CR1,0); /* THE DATA WILL BE CAPTURED IN THE FIRST CLOCK TRANSITION*/
		CLR_BIT(SPI2_CR1,1); /* CLK TO 0 IN IDLE*/
		SET_BIT(SPI2_CR1,2); /* ENABLE THE MASTER PIN */
#if Baud_Rate==CLK_2
		CLR_BIT(SPI2_CR1,3);
		CLR_BIT(SPI2_CR1,4);
		CLR_BIT(SPI2_CR1,5);
#elif Baud_Rate==CLK_4
		SET_BIT(SPI2_CR1,3);
		CLR_BIT(SPI2_CR1,4);
		CLR_BIT(SPI2_CR1,5);
#elif Baud_Rate==CLK_8
		CLR_BIT(SPI2_CR1,3);
		SET_BIT(SPI2_CR1,4);
		CLR_BIT(SPI2_CR1,5);
#elif Baud_Rate==CLK_16
		SET_BIT(SPI2_CR1,3);
		SET_BIT(SPI2_CR1,4);
		CLR_BIT(SPI2_CR1,5);
#elif Baud_Rate==CLK_32
		CLR_BIT(SPI2_CR1,3);
		CLR_BIT(SPI2_CR1,4);
		SET_BIT(SPI2_CR1,5);
#elif Baud_Rate==CLK_64
		SET_BIT(SPI2_CR1,3);
		CLR_BIT(SPI2_CR1,4);
		SET_BIT(SPI2_CR1,5);
#elif Baud_Rate==CLK_128
		CLR_BIT(SPI2_CR1,3);
		SET_BIT(SPI2_CR1,4);
		SET_BIT(SPI2_CR1,5);
#elif Baud_Rate==CLK_256
		SET_BIT(SPI2_CR1,3);
		SET_BIT(SPI2_CR1,4);
		SET_BIT(SPI2_CR1,5);
#endif

		CLR_BIT(SPI2_CR1,11); /* 8_BIT DATA FORMAT*/
		CLR_BIT(SPI2_CR1,10); /* FULL DUPLEX MODE IS USED*/
		SET_BIT(SPI2_CR1,9);
		CLR_BIT(SPI2_CR1,9); /*NSS HARDWARE*/
		//SET_BIT(SPI2_CR2,2);
		SET_BIT(SPI2_CR1,6); 		/* ENABLING THE SPI UNIT*/

		break;


	}

}
/* function description :
 * this function used to initialize  the microcontroller as a slave
 */

void SPI_voidInitSlave(uint8 Copy_u8spi){
	switch (Copy_u8spi){
	case SPI_1 :
		/******* first enable the GPIO and SPI clock by RCC (RCC CONFIGURATION)************/
		SET_BIT(RCC_APB2ENR,2); // ENABLING THE CLOCK OF GPIOA FOR SPI1
		SET_BIT(RCC_APB2ENR,12); // ENABLING THE CLOCK FOR SPI1
		/*********************** second GPIO CONFIGURATION*********************************/
		GPIOA_CRL=0x4B444444; /* MAKING MOSI(PA7) AND CLOCK(PA5) OUTPUT AND ALTERNATE AND
		MAKE THE MISO(PA6) INPUT*/
		/*******************************SPI CNFIGURATION***********************************/
		CLR_BIT(SPI1_CR1,0); /* THE DATA WILL BE CAPTURED IN THE FIRST CLOCK TRANSITION*/
		CLR_BIT(SPI1_CR1,1); /* CLK TO 0 IN IDLE*/
		CLR_BIT(SPI1_CR1,2); /* DISABLE THE MASTER PIN */
#if Baud_Rate==CLK_2
		CLR_BIT(SPI1_CR1,3);
		CLR_BIT(SPI1_CR1,4);
		CLR_BIT(SPI1_CR1,5);
#elif Baud_Rate==CLK_4
		SET_BIT(SPI1_CR1,3);
		CLR_BIT(SPI1_CR1,4);
		CLR_BIT(SPI1_CR1,5);
#elif Baud_Rate==CLK_8
		CLR_BIT(SPI1_CR1,3);
		SET_BIT(SPI1_CR1,4);
		CLR_BIT(SPI1_CR1,5);
#elif Baud_Rate==CLK_16
		SET_BIT(SPI1_CR1,3);
		SET_BIT(SPI1_CR1,4);
		CLR_BIT(SPI1_CR1,5);
#elif Baud_Rate==CLK_32
		CLR_BIT(SPI1_CR1,3);
		CLR_BIT(SPI1_CR1,4);
		SET_BIT(SPI1_CR1,5);
#elif Baud_Rate==CLK_64
		SET_BIT(SPI1_CR1,3);
		CLR_BIT(SPI1_CR1,4);
		SET_BIT(SPI1_CR1,5);
#elif Baud_Rate==CLK_128
		CLR_BIT(SPI1_CR1,3);
		SET_BIT(SPI1_CR1,4);
		SET_BIT(SPI1_CR1,5);
#elif Baud_Rate==CLK_256
		SET_BIT(SPI1_CR1,3);
		SET_BIT(SPI1_CR1,4);
		SET_BIT(SPI1_CR1,5);
#endif

		CLR_BIT(SPI1_CR1,11); /* 8_BIT DATA FORMAT*/
		CLR_BIT(SPI1_CR1,10); /* FULL DUPLEX MODE IS USED*/
		CLR_BIT(SPI1_CR1,9); /*NSS HARDWARE*/
		SET_BIT(SPI1_CR2,2); /* ENABLE SSOE*/
		SET_BIT(SPI1_CR1,6); 		/* ENABLING THE SPI UNIT*/


		break;
	case SPI_2 :
		/********* first enable the GPIO and SPI clock by RCC(RCC CONFIGURATION)***********/
		SET_BIT(RCC_APB2ENR,3); // ENABLING THE CLOCK OF GPIOB FOR SPI2
		SET_BIT(RCC_APB1ENR,14); // ENABLING THE CLOCK FOR SPI2
		/*********************** second GPIO CONFIGURATION*********************************/
		GPIOB_CRH=0x4B444444;/* MAKING MOSI(PB15) AND CLOCK(PB13) OUTPUT AND ALTERNATE AND
		MAKE THE MISO(PB14) INPUT*/
		/*******************************SPI CNFIGURATION***********************************/
		CLR_BIT(SPI2_CR1,0); /* THE DATA WILL BE CAPTURED IN THE FIRST CLOCK TRANSITION*/
		CLR_BIT(SPI2_CR1,1); /* CLK TO 0 IN IDLE*/
		CLR_BIT(SPI2_CR1,2); /* DISABLE THE MASTER PIN */
#if Baud_Rate==CLK_2
		CLR_BIT(SPI2_CR1,3);
		CLR_BIT(SPI2_CR1,4);
		CLR_BIT(SPI2_CR1,5);
#elif Baud_Rate==CLK_4
		SET_BIT(SPI2_CR1,3);
		CLR_BIT(SPI2_CR1,4);
		CLR_BIT(SPI2_CR1,5);
#elif Baud_Rate==CLK_8
		CLR_BIT(SPI2_CR1,3);
		SET_BIT(SPI2_CR1,4);
		CLR_BIT(SPI2_CR1,5);
#elif Baud_Rate==CLK_16
		SET_BIT(SPI2_CR1,3);
		SET_BIT(SPI2_CR1,4);
		CLR_BIT(SPI2_CR1,5);
#elif Baud_Rate==CLK_32
		CLR_BIT(SPI2_CR1,3);
		CLR_BIT(SPI2_CR1,4);
		SET_BIT(SPI2_CR1,5);
#elif Baud_Rate==CLK_64
		SET_BIT(SPI2_CR1,3);
		CLR_BIT(SPI2_CR1,4);
		SET_BIT(SPI2_CR1,5);
#elif Baud_Rate==CLK_128
		CLR_BIT(SPI2_CR1,3);
		SET_BIT(SPI2_CR1,4);
		SET_BIT(SPI2_CR1,5);
#elif Baud_Rate==CLK_256
		SET_BIT(SPI2_CR1,3);
		SET_BIT(SPI2_CR1,4);
		SET_BIT(SPI2_CR1,5);
#endif

		CLR_BIT(SPI2_CR1,11); /* 8_BIT DATA FORMAT*/
		CLR_BIT(SPI2_CR1,10); /* FULL DUPLEX MODE IS USED*/
		SET_BIT(SPI2_CR1,9);
		CLR_BIT(SPI2_CR1,9); /*NSS HARDWARE*/
		SET_BIT(SPI2_CR2,2); /* ENABLE SSOE*/
		SET_BIT(SPI2_CR1,6); 		/* ENABLING THE SPI UNIT*/

		break;


	}

}
/* function description :
 * this function used to send a byte
 */
void SPI_voidSendByte(uint8 Copy_u8spi,const uint8 Copy_u8data){

	switch (Copy_u8spi){
	case SPI_1:
		SPI1_DR=Copy_u8data;
		while((SPI1_SR & (1<<1))==0);// waiting for TXE flag is set to indicate that the byte is sent
		break;
	case SPI_2:
		SPI2_DR=Copy_u8data;
		while((SPI2_SR & (1<<1))==0);// waiting for TXE flag is set to indicate that the byte is sent
		break;
	}

}
/* function description :
 * this function used to receive a byte
 */
uint8 SPI_u8RecieveByte(uint8 Copy_u8spi){
	switch(Copy_u8spi){
	case SPI_1:
		while((SPI1_SR & (1<<0))==0); // waiting for RXNE flag is set to indicate that the byte is received
		return SPI1_DR;

		break;
	case SPI_2:
		while((SPI2_SR & (1<<0))==0);// waiting for RXNE flag is set to indicate that the byte is received
		return SPI2_DR;
		break;
	}
}
/* function description :
 * this function used to send string if it will be received it must send with end of #
 */
void SPI_voidSendString(uint8 Copy_u8spi,const uint8 *Copy_u8str){
	uint8 i=0;
	switch (Copy_u8spi){
	case SPI_1:
		while(Copy_u8str[i]!='\0'){
			SPI_voidSendByte(SPI_1,Copy_u8str[i]);
			i++;
		}
		break;
	case SPI_2:
		while(Copy_u8str[i]!='\0'){
			SPI_voidSendByte(SPI_2,Copy_u8str[i]);
			i++;
		}
		break;

	}
}
/* function description :
 * this function used to recieve string but the string should be transmitted with end of #
 */

void SPI_voidRecieveString(uint8 Copy_u8spi,char*str){
	uint8 i=0;
	switch(Copy_u8spi){
	case SPI_1:
		str[i]=SPI_u8RecieveByte(SPI_1);
		while(str[i]!= '#'){
			i++;
			str[i]=SPI_u8RecieveByte(SPI_1);
		}
		str[i]='\0';
		break;
	case SPI_2:
		str[i]=SPI_u8RecieveByte(SPI_2);
		while(str[i]!= '#'){
			i++;
			str[i]=SPI_u8RecieveByte(SPI_2);
		}
		str[i]='\0';
		break;
	}
}

void SPI_voidLoadData(uint8 Copy_u8spi,uint8 Copy_u8data){
	switch(Copy_u8spi){
	case SPI_1:
		SPI1_DR=Copy_u8data;
		break;
	case SPI_2 :
		SPI2_DR=Copy_u8data;
		break;
	}
}
uint8 SPI_u8ReturnData(uint8 Copy_u8spi){
	switch(Copy_u8spi){
	case SPI_1:
		return SPI1_DR;
		break;
	case SPI_2:
		return SPI2_DR;
		break;
	}
}
uint8 SPI_u8ReadInterrupt(uint8 Copy_u8spi){
	switch(Copy_u8spi){
	case SPI_1:
		SPI1_DR=0xFF;
		while((SPI1_SR & (1<<0))==0);
		return SPI1_DR;
		break;
	case SPI_2:
		SPI2_DR=0xFF;
		while((SPI2_SR & (1<<0))==0);
		return SPI2_DR;
		break;
	}
}
void SPI1_voidSetInterrupt(void (*LOCAL_PTR)(void)){
	SET_BIT(SPI1_CR2,6);
	SET_BIT(SPI1_CR2,7);
	LOCAL_PTR=Global_PTR_1;
	NVIC_voidEnableInterrupt(35);
    NVIC_voidSetPendingFlag(35);

}
void SPI2_voidSetInterrupt(void (*LOCAL_PTR)(void)){
	SET_BIT(SPI2_CR2,6);
	SET_BIT(SPI2_CR2,7);
	LOCAL_PTR=Global_PTR_2;
	NVIC_voidEnableInterrupt(36);
    NVIC_voidSetPendingFlag(36);

}
void SPI1_IRQHandler(void){
if(Global_PTR_1!='\0'){
	(*Global_PTR_1)();
	NVIC_voidDisableInterrupt(35);
}
}
void SPI2_IRQHandler(void){
if(Global_PTR_2!='\0'){
	(*Global_PTR_2)();
	NVIC_voidDisableInterrupt(36);
}
}


