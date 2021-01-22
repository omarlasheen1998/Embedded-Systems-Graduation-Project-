/*
 * ADC_program.c
 *
 *  Created on: Jan 18, 2021
 *      Author: Kimo
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"
#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_config.h"
#include "NVIC_interface.h"
#include "NVIC_private.h"
#include "NVIC_config.h"
#include "STK_interface.h"
#include "GPIO_private.h"
u16 val =0;
static volatile void (*g_callBackPtr)(void) = NULL_PTR;




void ADC_voidInit(void){
	/* enabling the ADC module with single contineous channel */
	SET_BIT(ADC1_CR2,0);
	SET_BIT(ADC1_CR2,1);
	STK_voidDelay_ms(1);

	/**********************choose the prescalar of the module *****************/
#if ADC_PRESC== CLK_DIVIDE_BY_2
	CLR_BIT(RCC_CFGR,14);
	CLR_BIT(RCC_CFGR,15);
#elif  ADC_PRESC== CLK_DIVIDE_BY_4
	SET_BIT(RCC_CFGR,14);
	CLR_BIT(RCC_CFGR,15);
#elif ADC_PRESC== CLK_DIVIDE_BY_6
	CLR_BIT(RCC_CFGR,14);
	SET_BIT(RCC_CFGR,15);
#else
	SET_BIT(RCC_CFGR,14);
	SET_BIT(RCC_CFGR,15);
#endif

	
#if ADC_SAMP_RATE == SAMP_1_CYCLES
		CLR_BIT(ADC1_SMPR2,15);
		CLR_BIT(ADC1_SMPR2,16);
		CLR_BIT(ADC1_SMPR2,17);
#elif ADC_SAMP_RATE == SAMP_7_CYCLES
		SET_BIT(ADC1_SMPR2,15);
		CLR_BIT(ADC1_SMPR2,16);
		CLR_BIT(ADC1_SMPR2,17);
#elif ADC_SAMP_RATE == SAMP_13_CYCLES
		CLR_BIT(ADC1_SMPR2,15);
		SET_BIT(ADC1_SMPR2,16);
		CLR_BIT(ADC1_SMPR2,17);
#elif ADC_SAMP_RATE == SAMP_28_CYCLES
		SET_BIT(ADC1_SMPR2,15);
		SET_BIT(ADC1_SMPR2,16);
		CLR_BIT(ADC1_SMPR2,17);
#elif ADC_SAMP_RATE == SAMP_41_CYCLES
		CLR_BIT(ADC1_SMPR2,15);
		CLR_BIT(ADC1_SMPR2,16);
		SET_BIT(ADC1_SMPR2,17);
#elif ADC_SAMP_RATE == SAMP_55_CYCLES
		SET_BIT(ADC1_SMPR2,15);
		CLR_BIT(ADC1_SMPR2,16);
		SET_BIT(ADC1_SMPR2,17);
#elif ADC_SAMP_RATE == SAMP_71_CYCLES
		CLR_BIT(ADC1_SMPR2,15);
		SET_BIT(ADC1_SMPR2,16);
		SET_BIT(ADC1_SMPR2,17);
#elif ADC_SAMP_RATE == SAMP_239_CYCLES
		SET_BIT(ADC1_SMPR2,15);
		SET_BIT(ADC1_SMPR2,16);
		SET_BIT(ADC1_SMPR2,17);
#endif

}
u16 ADC_u16ReadChannelPoll(u16 Channel_u16Number){/* you must enter the channel number from 0 to 9*/
	switch(Channel_u16Number){
	case 0:
CLR_BIT(GPIOA_CRL,0);
CLR_BIT(GPIOA_CRL,1);
	
		STK_voidDelay_ms(1);
		CLR_BIT(ADC1_SQR3,0);
	  CLR_BIT(ADC1_SQR3,1);
  	CLR_BIT(ADC1_SQR3,2);
		CLR_BIT(ADC1_SQR3,3);
		
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,2);
		STK_voidDelay_ms(2);

		while((ADC1_SR&(1<<1)) == 0);
		return ADC1_DR;
		break;
	case 1:
CLR_BIT(GPIOA_CRL,4);
CLR_BIT(GPIOA_CRL,5);

				STK_voidDelay_ms(1);
		SET_BIT(ADC1_SQR3,0);
	  CLR_BIT(ADC1_SQR3,1);
  	CLR_BIT(ADC1_SQR3,2);
		CLR_BIT(ADC1_SQR3,3);
		
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,2);
		STK_voidDelay_ms(2);

		while((ADC1_SR&(1<<1)) == 0);
		return ADC1_DR;


		break;
	case 2:
		CLR_BIT(GPIOA_CRL,8);
    CLR_BIT(GPIOA_CRL,9);

		STK_voidDelay_ms(1);
		CLR_BIT(ADC1_SQR3,0);
	  SET_BIT(ADC1_SQR3,1);
  	CLR_BIT(ADC1_SQR3,2);
		CLR_BIT(ADC1_SQR3,3);
		
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,2);
		STK_voidDelay_ms(2);

		while((ADC1_SR&(1<<1)) == 0);
		return ADC1_DR;


		break;
	case 3:
		
		CLR_BIT(GPIOA_CRL,12);
    CLR_BIT(GPIOA_CRL,13);

		STK_voidDelay_ms(1);
		SET_BIT(ADC1_SQR3,0);
	  SET_BIT(ADC1_SQR3,1);
  	CLR_BIT(ADC1_SQR3,2);
		CLR_BIT(ADC1_SQR3,3);
		
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,2);
		STK_voidDelay_ms(2);
		
		while((ADC1_SR&(1<<1)) == 0);
		return ADC1_DR;

		break;
	case 4:
		
		CLR_BIT(GPIOA_CRL,16);
    CLR_BIT(GPIOA_CRL,17);

    STK_voidDelay_ms(1);
		CLR_BIT(ADC1_SQR3,0);
	  CLR_BIT(ADC1_SQR3,1);
  	SET_BIT(ADC1_SQR3,2);
		CLR_BIT(ADC1_SQR3,3);
		
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,2);
		STK_voidDelay_ms(2);
		
		
		while((ADC1_SR&(1<<1)) == 0);
		return ADC1_DR;


		break;
	case 5:
		
		CLR_BIT(GPIOA_CRL,20);
    CLR_BIT(GPIOA_CRL,21);


    STK_voidDelay_ms(1);
		SET_BIT(ADC1_SQR3,0);
		CLR_BIT(ADC1_SQR3,1);
		SET_BIT(ADC1_SQR3,2);
		CLR_BIT(ADC1_SQR3,3);
		
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,2);
		STK_voidDelay_ms(2);
		
		while((ADC1_SR&(1<<1)) == 0);
		return ADC1_DR;


		break;
	case 6:
		
		CLR_BIT(GPIOA_CRL,24);
    CLR_BIT(GPIOA_CRL,25);

		STK_voidDelay_ms(1);
		CLR_BIT(ADC1_SQR3,0);
	  SET_BIT(ADC1_SQR3,1);
  	SET_BIT(ADC1_SQR3,2);
		CLR_BIT(ADC1_SQR3,3);
			
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,2);
		STK_voidDelay_ms(2);

		while((ADC1_SR&(1<<1)) == 0);
		return ADC1_DR;


		break;
	case 7:
		
		CLR_BIT(GPIOA_CRL,28);
    CLR_BIT(GPIOA_CRL,29);

		STK_voidDelay_ms(1);
		SET_BIT(ADC1_SQR3,0);
	  SET_BIT(ADC1_SQR3,1);
  	SET_BIT(ADC1_SQR3,2);
		CLR_BIT(ADC1_SQR3,3);
		
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,2);
		STK_voidDelay_ms(2);

		while((ADC1_SR&(1<<1)) == 0);
		return ADC1_DR;


		break;
	case 8:
		
		CLR_BIT(GPIOB_CRL,0);
    CLR_BIT(GPIOB_CRL,1);

		STK_voidDelay_ms(1);
		CLR_BIT(ADC1_SQR3,0);
	  CLR_BIT(ADC1_SQR3,1);
  	CLR_BIT(ADC1_SQR3,2);
		SET_BIT(ADC1_SQR3,3);
		
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,2);
		STK_voidDelay_ms(2);

		while((ADC1_SR&(1<<1)) == 0);
		return ADC1_DR;


		break;
	case 9:
		CLR_BIT(GPIOB_CRL,4);
    CLR_BIT(GPIOB_CRL,5);

		STK_voidDelay_ms(1);
		SET_BIT(ADC1_SQR3,0);
	  CLR_BIT(ADC1_SQR3,1);
  	CLR_BIT(ADC1_SQR3,2);
		SET_BIT(ADC1_SQR3,3);
		
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,2);
		STK_voidDelay_ms(2);

		while((ADC1_SR&(1<<1)) == 0);
		return ADC1_DR;

		break;
	default :
		break;

	}
}

void ADC_voidReadChannelInterrupt(u16 Channel_u16Number){
	SET_BIT(ADC1_CR1,5);
	NVIC_voidEnableInterrupt(18);
	switch(Channel_u16Number){
	case 0:
		CLR_BIT(GPIOA_CRL,0);
    CLR_BIT(GPIOA_CRL,1);

		STK_voidDelay_ms(1);
		CLR_BIT(ADC1_SQR3,0);
	  CLR_BIT(ADC1_SQR3,1);
  	CLR_BIT(ADC1_SQR3,2);
		CLR_BIT(ADC1_SQR3,3);
		
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,2);
		STK_voidDelay_ms(2);
    NVIC_voidSetPendingFlag(18);

		break;
	case 1:
		CLR_BIT(GPIOA_CRL,4);
    CLR_BIT(GPIOA_CRL,5);

	  STK_voidDelay_ms(1);
		CLR_BIT(ADC1_SQR3,0);
	  SET_BIT(ADC1_SQR3,1);
  	CLR_BIT(ADC1_SQR3,2);
		CLR_BIT(ADC1_SQR3,3);
		
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,2);
		STK_voidDelay_ms(2);
    NVIC_voidSetPendingFlag(18);



		break;
	case 2:
		CLR_BIT(GPIOA_CRL,8);
    CLR_BIT(GPIOA_CRL,9);
  
   	STK_voidDelay_ms(1);
		CLR_BIT(ADC1_SQR3,0);
	  SET_BIT(ADC1_SQR3,1);
  	CLR_BIT(ADC1_SQR3,2);
		CLR_BIT(ADC1_SQR3,3);
		
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,2);
		STK_voidDelay_ms(2);
    NVIC_voidSetPendingFlag(18);



		break;
	case 3:
		CLR_BIT(GPIOA_CRL,12);
    CLR_BIT(GPIOA_CRL,13);

  	STK_voidDelay_ms(1);
		SET_BIT(ADC1_SQR3,0);
	  SET_BIT(ADC1_SQR3,1);
  	CLR_BIT(ADC1_SQR3,2);
		CLR_BIT(ADC1_SQR3,3);
		
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,2);
		STK_voidDelay_ms(2);
    NVIC_voidSetPendingFlag(18);



		break;
	case 4:
		CLR_BIT(GPIOA_CRL,16);
    CLR_BIT(GPIOA_CRL,17);

  	STK_voidDelay_ms(1);
		CLR_BIT(ADC1_SQR3,0);
	  CLR_BIT(ADC1_SQR3,1);
  	SET_BIT(ADC1_SQR3,2);
		CLR_BIT(ADC1_SQR3,3);
		
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,2);
		STK_voidDelay_ms(2);
    NVIC_voidSetPendingFlag(18);



		break;
	case 5:
		
	  CLR_BIT(GPIOA_CRL,20);
    CLR_BIT(GPIOA_CRL,21);

  	STK_voidDelay_ms(1);
		SET_BIT(ADC1_SQR3,0);
	  CLR_BIT(ADC1_SQR3,1);
  	SET_BIT(ADC1_SQR3,2);
		CLR_BIT(ADC1_SQR3,3);
		
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,2);
		STK_voidDelay_ms(2);
    NVIC_voidSetPendingFlag(18);
		break;
		
	case 6:
		
		CLR_BIT(GPIOA_CRL,24);
    CLR_BIT(GPIOA_CRL,25);

  STK_voidDelay_ms(1);
		CLR_BIT(ADC1_SQR3,0);
	  SET_BIT(ADC1_SQR3,1);
  	SET_BIT(ADC1_SQR3,2);
		CLR_BIT(ADC1_SQR3,3);
		
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,2);
		STK_voidDelay_ms(2);
   	NVIC_voidSetPendingFlag(18);


		break;
	case 7:
		
		CLR_BIT(GPIOA_CRL,28);
	 CLR_BIT(GPIOA_CRL,29);

  	STK_voidDelay_ms(1);
		SET_BIT(ADC1_SQR3,0);
	  SET_BIT(ADC1_SQR3,1);
  	SET_BIT(ADC1_SQR3,2);
		CLR_BIT(ADC1_SQR3,3);
		
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,2);
		STK_voidDelay_ms(2);
    NVIC_voidSetPendingFlag(18);

		break;
	case 8:
		
		CLR_BIT(GPIOB_CRL,0);
    CLR_BIT(GPIOB_CRL,1);

  	STK_voidDelay_ms(1);
		CLR_BIT(ADC1_SQR3,0);
	  CLR_BIT(ADC1_SQR3,1);
  	CLR_BIT(ADC1_SQR3,2);
		SET_BIT(ADC1_SQR3,3);
		
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,2);
		STK_voidDelay_ms(2);
    NVIC_voidSetPendingFlag(18);


		break;
	case 9:
		
	CLR_BIT(GPIOB_CRL,4);
    CLR_BIT(GPIOB_CRL,5);

  	STK_voidDelay_ms(1);
		SET_BIT(ADC1_SQR3,0);
	  CLR_BIT(ADC1_SQR3,1);
  	CLR_BIT(ADC1_SQR3,2);
		SET_BIT(ADC1_SQR3,3);
		
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		STK_voidDelay_ms(1);
		
		SET_BIT(ADC1_CR2,2);
		STK_voidDelay_ms(2);
    NVIC_voidSetPendingFlag(18);
		break;

	}

}

void ADC1_2_IRQHandler(void){
	if(g_callBackPtr!=NULL_PTR){
		(*g_callBackPtr)();
			NVIC_voidDisableInterrupt(18);
	}
}
void ADC1_voidSetCallBack(void(*a_ptr)(void)){
	g_callBackPtr=a_ptr;
}

u16 ADC_u16ReturnValue(void){
	return ADC1_DR;
}


