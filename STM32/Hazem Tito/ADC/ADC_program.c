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

uint16 val =0;
static volatile void (*g_callBackPtr)(void) = NULL_PTR;


void delayMs(uint16 n){
	uint16 i;
	for(;n>0;n--){
		for(i=0;i<14378;i++);
	}
}


void ADC_voidInit(void){
	/* enabling the ADC module with single contineous channel */
	SET_BIT(ADC1_CR2,0);
	SET_BIT(ADC1_CR2,1);
	delayMs(1);

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

}
uint16 ADC_u16ReadChannelPoll(uint16 Channel_u16Number){/* you must enter the channel number from 0 to 9*/
	switch(Channel_u16Number){
	case 0:
#if ADC_SAMP_RATE == SAMP_1_CYCLES
		CLR_BIT(ADC1_SMPR2,0);
		CLR_BIT(ADC1_SMPR2,1);
		CLR_BIT(ADC1_SMPR2,2);
#elif ADC_SAMP_RATE == SAMP_7_CYCLES
		SET_BIT(ADC1_SMPR2,0);
		CLR_BIT(ADC1_SMPR2,1);
		CLR_BIT(ADC1_SMPR2,2);
#elif ADC_SAMP_RATE == SAMP_13_CYCLES
		CLR_BIT(ADC1_SMPR2,0);
		SET_BIT(ADC1_SMPR2,1);
		CLR_BIT(ADC1_SMPR2,2);
#elif ADC_SAMP_RATE == SAMP_28_CYCLES
		SET_BIT(ADC1_SMPR2,0);
		SET_BIT(ADC1_SMPR2,1);
		CLR_BIT(ADC1_SMPR2,2);
#elif ADC_SAMP_RATE == SAMP_41_CYCLES
		CLR_BIT(ADC1_SMPR2,0);
		CLR_BIT(ADC1_SMPR2,1);
		SET_BIT(ADC1_SMPR2,2);
#elif ADC_SAMP_RATE == SAMP_55_CYCLES
		SET_BIT(ADC1_SMPR2,0);
		CLR_BIT(ADC1_SMPR2,1);
		SET_BIT(ADC1_SMPR2,2);
#elif ADC_SAMP_RATE == SAMP_71_CYCLES
		CLR_BIT(ADC1_SMPR2,0);
		SET_BIT(ADC1_SMPR2,1);
		SET_BIT(ADC1_SMPR2,2);
#elif ADC_SAMP_RATE == SAMP_239_CYCLES
		SET_BIT(ADC1_SMPR2,0);
		SET_BIT(ADC1_SMPR2,1);
		SET_BIT(ADC1_SMPR2,2);
#endif
		delayMs(1);
		SET_BIT(ADC1_SQR3,0);
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		delayMs(1);

		while((ADC1_SR&(1<<1)) == 0);
		return ADC1_DR;
		break;
	case 1:
#if ADC_SAMP_RATE == SAMP_1_CYCLES
		CLR_BIT(ADC1_SMPR2,3);
		CLR_BIT(ADC1_SMPR2,4);
		CLR_BIT(ADC1_SMPR2,5);
#elif ADC_SAMP_RATE == SAMP_7_CYCLES
		SET_BIT(ADC1_SMPR2,3);
		CLR_BIT(ADC1_SMPR2,4);
		CLR_BIT(ADC1_SMPR2,5);
#elif ADC_SAMP_RATE == SAMP_13_CYCLES
		CLR_BIT(ADC1_SMPR2,3);
		SET_BIT(ADC1_SMPR2,4);
		CLR_BIT(ADC1_SMPR2,5);
#elif ADC_SAMP_RATE == SAMP_28_CYCLES
		SET_BIT(ADC1_SMPR2,3);
		SET_BIT(ADC1_SMPR2,4);
		CLR_BIT(ADC1_SMPR2,5);
#elif ADC_SAMP_RATE == SAMP_41_CYCLES
		CLR_BIT(ADC1_SMPR2,3);
		CLR_BIT(ADC1_SMPR2,4);
		SET_BIT(ADC1_SMPR2,5);
#elif ADC_SAMP_RATE == SAMP_55_CYCLES
		SET_BIT(ADC1_SMPR2,3);
		CLR_BIT(ADC1_SMPR2,4);
		SET_BIT(ADC1_SMPR2,5);
#elif ADC_SAMP_RATE == SAMP_71_CYCLES
		CLR_BIT(ADC1_SMPR2,3);
		SET_BIT(ADC1_SMPR2,4);
		SET_BIT(ADC1_SMPR2,5);
#elif ADC_SAMP_RATE == SAMP_239_CYCLES
		SET_BIT(ADC1_SMPR2,3);
		SET_BIT(ADC1_SMPR2,4);
		SET_BIT(ADC1_SMPR2,5);
#endif
		delayMs(1);
		SET_BIT(ADC1_SQR3,1);
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		delayMs(1);

		while((ADC1_SR&(1<<1)) == 0);
		return ADC1_DR;


		break;
	case 2:
#if ADC_SAMP_RATE == SAMP_1_CYCLES
		CLR_BIT(ADC1_SMPR2,6);
		CLR_BIT(ADC1_SMPR2,7);
		CLR_BIT(ADC1_SMPR2,8);
#elif ADC_SAMP_RATE == SAMP_7_CYCLES
		SET_BIT(ADC1_SMPR2,6);
		CLR_BIT(ADC1_SMPR2,7);
		CLR_BIT(ADC1_SMPR2,8);
#elif ADC_SAMP_RATE == SAMP_13_CYCLES
		CLR_BIT(ADC1_SMPR2,6);
		SET_BIT(ADC1_SMPR2,7);
		CLR_BIT(ADC1_SMPR2,8);
#elif ADC_SAMP_RATE == SAMP_28_CYCLES
		SET_BIT(ADC1_SMPR2,6);
		SET_BIT(ADC1_SMPR2,7);
		CLR_BIT(ADC1_SMPR2,8);
#elif ADC_SAMP_RATE == SAMP_41_CYCLES
		CLR_BIT(ADC1_SMPR2,6);
		CLR_BIT(ADC1_SMPR2,7);
		SET_BIT(ADC1_SMPR2,8);
#elif ADC_SAMP_RATE == SAMP_55_CYCLES
		SET_BIT(ADC1_SMPR2,6);
		CLR_BIT(ADC1_SMPR2,7);
		SET_BIT(ADC1_SMPR2,8);
#elif ADC_SAMP_RATE == SAMP_71_CYCLES
		CLR_BIT(ADC1_SMPR2,6);
		SET_BIT(ADC1_SMPR2,7);
		SET_BIT(ADC1_SMPR2,8);
#elif ADC_SAMP_RATE == SAMP_239_CYCLES
		SET_BIT(ADC1_SMPR2,6);
		SET_BIT(ADC1_SMPR2,7);
		SET_BIT(ADC1_SMPR2,8);
#endif
		delayMs(1);
		SET_BIT(ADC1_SQR3,0);
		SET_BIT(ADC1_SQR3,1);
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		delayMs(1);

		while((ADC1_SR&(1<<1)) == 0);
		return ADC1_DR;


		break;
	case 3:
#if ADC_SAMP_RATE == SAMP_1_CYCLES
		CLR_BIT(ADC1_SMPR2,9);
		CLR_BIT(ADC1_SMPR2,10);
		CLR_BIT(ADC1_SMPR2,11);
#elif ADC_SAMP_RATE == SAMP_7_CYCLES
		SET_BIT(ADC1_SMPR2,9);
		CLR_BIT(ADC1_SMPR2,10);
		CLR_BIT(ADC1_SMPR2,11);
#elif ADC_SAMP_RATE == SAMP_13_CYCLES
		CLR_BIT(ADC1_SMPR2,9);
		SET_BIT(ADC1_SMPR2,10);
		CLR_BIT(ADC1_SMPR2,11);
#elif ADC_SAMP_RATE == SAMP_28_CYCLES
		SET_BIT(ADC1_SMPR2,9);
		SET_BIT(ADC1_SMPR2,10);
		CLR_BIT(ADC1_SMPR2,11);
#elif ADC_SAMP_RATE == SAMP_41_CYCLES
		CLR_BIT(ADC1_SMPR2,9);
		CLR_BIT(ADC1_SMPR2,10);
		SET_BIT(ADC1_SMPR2,11);
#elif ADC_SAMP_RATE == SAMP_55_CYCLES
		SET_BIT(ADC1_SMPR2,9);
		CLR_BIT(ADC1_SMPR2,10);
		SET_BIT(ADC1_SMPR2,11);
#elif ADC_SAMP_RATE == SAMP_71_CYCLES
		CLR_BIT(ADC1_SMPR2,9);
		SET_BIT(ADC1_SMPR2,10);
		SET_BIT(ADC1_SMPR2,11);
#elif ADC_SAMP_RATE == SAMP_239_CYCLES
		SET_BIT(ADC1_SMPR2,9);
		SET_BIT(ADC1_SMPR2,10);
		SET_BIT(ADC1_SMPR2,11);
#endif
		delayMs(1);
		SET_BIT(ADC1_SQR3,2);
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		delayMs(1);

		while((ADC1_SR&(1<<1)) == 0);
		return ADC1_DR;

		break;
	case 4:
#if ADC_SAMP_RATE == SAMP_1_CYCLES
		CLR_BIT(ADC1_SMPR2,12);
		CLR_BIT(ADC1_SMPR2,13);
		CLR_BIT(ADC1_SMPR2,14);
#elif ADC_SAMP_RATE == SAMP_7_CYCLES
		SET_BIT(ADC1_SMPR2,12);
		CLR_BIT(ADC1_SMPR2,13);
		CLR_BIT(ADC1_SMPR2,14);
#elif ADC_SAMP_RATE == SAMP_13_CYCLES
		CLR_BIT(ADC1_SMPR2,12);
		SET_BIT(ADC1_SMPR2,13);
		CLR_BIT(ADC1_SMPR2,14);
#elif ADC_SAMP_RATE == SAMP_28_CYCLES
		SET_BIT(ADC1_SMPR2,12);
		SET_BIT(ADC1_SMPR2,13);
		CLR_BIT(ADC1_SMPR2,14);
#elif ADC_SAMP_RATE == SAMP_41_CYCLES
		CLR_BIT(ADC1_SMPR2,12);
		CLR_BIT(ADC1_SMPR2,13);
		SET_BIT(ADC1_SMPR2,14);
#elif ADC_SAMP_RATE == SAMP_55_CYCLES
		SET_BIT(ADC1_SMPR2,12);
		CLR_BIT(ADC1_SMPR2,13);
		SET_BIT(ADC1_SMPR2,14);
#elif ADC_SAMP_RATE == SAMP_71_CYCLES
		CLR_BIT(ADC1_SMPR2,12);
		SET_BIT(ADC1_SMPR2,13);
		SET_BIT(ADC1_SMPR2,14);
#elif ADC_SAMP_RATE == SAMP_239_CYCLES
		SET_BIT(ADC1_SMPR2,12);
		SET_BIT(ADC1_SMPR2,13);
		SET_BIT(ADC1_SMPR2,14);
#endif
		delayMs(1);
		SET_BIT(ADC1_SQR3,0);
		SET_BIT(ADC1_SQR3,2);
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		delayMs(1);

		while((ADC1_SR&(1<<1)) == 0);
		return ADC1_DR;


		break;
	case 5:
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
		delayMs(1);
		SET_BIT(ADC1_SQR3,1);
		SET_BIT(ADC1_SQR3,2);
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		delayMs(1);

		while((ADC1_SR&(1<<1)) == 0);
		return ADC1_DR;


		break;
	case 6:
#if ADC_SAMP_RATE == SAMP_1_CYCLES
		CLR_BIT(ADC1_SMPR2,18);
		CLR_BIT(ADC1_SMPR2,19);
		CLR_BIT(ADC1_SMPR2,20);
#elif ADC_SAMP_RATE == SAMP_7_CYCLES
		SET_BIT(ADC1_SMPR2,18);
		CLR_BIT(ADC1_SMPR2,19);
		CLR_BIT(ADC1_SMPR2,20);
#elif ADC_SAMP_RATE == SAMP_13_CYCLES
		CLR_BIT(ADC1_SMPR2,18);
		SET_BIT(ADC1_SMPR2,19);
		CLR_BIT(ADC1_SMPR2,20);
#elif ADC_SAMP_RATE == SAMP_28_CYCLES
		SET_BIT(ADC1_SMPR2,18);
		SET_BIT(ADC1_SMPR2,19);
		CLR_BIT(ADC1_SMPR2,20);
#elif ADC_SAMP_RATE == SAMP_41_CYCLES
		CLR_BIT(ADC1_SMPR2,18);
		CLR_BIT(ADC1_SMPR2,19);
		SET_BIT(ADC1_SMPR2,20);
#elif ADC_SAMP_RATE == SAMP_55_CYCLES
		SET_BIT(ADC1_SMPR2,18);
		CLR_BIT(ADC1_SMPR2,19);
		SET_BIT(ADC1_SMPR2,20);
#elif ADC_SAMP_RATE == SAMP_71_CYCLES
		CLR_BIT(ADC1_SMPR2,18);
		SET_BIT(ADC1_SMPR2,19);
		SET_BIT(ADC1_SMPR2,20);
#elif ADC_SAMP_RATE == SAMP_239_CYCLES
		SET_BIT(ADC1_SMPR2,18);
		SET_BIT(ADC1_SMPR2,19);
		SET_BIT(ADC1_SMPR2,20);
#endif
		delayMs(1);
		SET_BIT(ADC1_SQR3,0);
		SET_BIT(ADC1_SQR3,1);
		SET_BIT(ADC1_SQR3,2);
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		delayMs(1);

		while((ADC1_SR&(1<<1)) == 0);
		return ADC1_DR;


		break;
	case 7:
#if ADC_SAMP_RATE == SAMP_1_CYCLES
		CLR_BIT(ADC1_SMPR2,21);
		CLR_BIT(ADC1_SMPR2,22);
		CLR_BIT(ADC1_SMPR2,23);
#elif ADC_SAMP_RATE == SAMP_7_CYCLES
		SET_BIT(ADC1_SMPR2,21);
		CLR_BIT(ADC1_SMPR2,22);
		CLR_BIT(ADC1_SMPR2,23);
#elif ADC_SAMP_RATE == SAMP_13_CYCLES
		CLR_BIT(ADC1_SMPR2,21);
		SET_BIT(ADC1_SMPR2,22);
		CLR_BIT(ADC1_SMPR2,23);
#elif ADC_SAMP_RATE == SAMP_28_CYCLES
		SET_BIT(ADC1_SMPR2,21);
		SET_BIT(ADC1_SMPR2,22);
		CLR_BIT(ADC1_SMPR2,23);
#elif ADC_SAMP_RATE == SAMP_41_CYCLES
		CLR_BIT(ADC1_SMPR2,21);
		CLR_BIT(ADC1_SMPR2,22);
		SET_BIT(ADC1_SMPR2,23);
#elif ADC_SAMP_RATE == SAMP_55_CYCLES
		SET_BIT(ADC1_SMPR2,21);
		CLR_BIT(ADC1_SMPR2,22);
		SET_BIT(ADC1_SMPR2,23);
#elif ADC_SAMP_RATE == SAMP_71_CYCLES
		CLR_BIT(ADC1_SMPR2,21);
		SET_BIT(ADC1_SMPR2,22);
		SET_BIT(ADC1_SMPR2,23);
#elif ADC_SAMP_RATE == SAMP_239_CYCLES
		SET_BIT(ADC1_SMPR2,21);
		SET_BIT(ADC1_SMPR2,22);
		SET_BIT(ADC1_SMPR2,23);
#endif
		delayMs(1);
		SET_BIT(ADC1_SQR3,3);
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		delayMs(1);

		while((ADC1_SR&(1<<1)) == 0);
		return ADC1_DR;


		break;
	case 8:
#if ADC_SAMP_RATE == SAMP_1_CYCLES
		CLR_BIT(ADC1_SMPR2,24);
		CLR_BIT(ADC1_SMPR2,25);
		CLR_BIT(ADC1_SMPR2,26);
#elif ADC_SAMP_RATE == SAMP_7_CYCLES
		SET_BIT(ADC1_SMPR2,24);
		CLR_BIT(ADC1_SMPR2,25);
		CLR_BIT(ADC1_SMPR2,26);
#elif ADC_SAMP_RATE == SAMP_13_CYCLES
		CLR_BIT(ADC1_SMPR2,24);
		SET_BIT(ADC1_SMPR2,25);
		CLR_BIT(ADC1_SMPR2,26);
#elif ADC_SAMP_RATE == SAMP_28_CYCLES
		SET_BIT(ADC1_SMPR2,24);
		SET_BIT(ADC1_SMPR2,25);
		CLR_BIT(ADC1_SMPR2,26);
#elif ADC_SAMP_RATE == SAMP_41_CYCLES
		CLR_BIT(ADC1_SMPR2,24);
		CLR_BIT(ADC1_SMPR2,25);
		SET_BIT(ADC1_SMPR2,26);
#elif ADC_SAMP_RATE == SAMP_55_CYCLES
		SET_BIT(ADC1_SMPR2,24);
		CLR_BIT(ADC1_SMPR2,25);
		SET_BIT(ADC1_SMPR2,26);
#elif ADC_SAMP_RATE == SAMP_71_CYCLES
		CLR_BIT(ADC1_SMPR2,24);
		SET_BIT(ADC1_SMPR2,25);
		SET_BIT(ADC1_SMPR2,26);
#elif ADC_SAMP_RATE == SAMP_239_CYCLES
		SET_BIT(ADC1_SMPR2,24);
		SET_BIT(ADC1_SMPR2,25);
		SET_BIT(ADC1_SMPR2,26);
#endif
		delayMs(1);
		SET_BIT(ADC1_SQR3,0);
		SET_BIT(ADC1_SQR3,3);
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		delayMs(1);

		while((ADC1_SR&(1<<1)) == 0);
		return ADC1_DR;


		break;
	case 9:
#if ADC_SAMP_RATE == SAMP_1_CYCLES
		CLR_BIT(ADC1_SMPR2,27);
		CLR_BIT(ADC1_SMPR2,28);
		CLR_BIT(ADC1_SMPR2,29);
#elif ADC_SAMP_RATE == SAMP_7_CYCLES
		SET_BIT(ADC1_SMPR2,27);
		CLR_BIT(ADC1_SMPR2,28);
		CLR_BIT(ADC1_SMPR2,29);
#elif ADC_SAMP_RATE == SAMP_13_CYCLES
		CLR_BIT(ADC1_SMPR2,27);
		SET_BIT(ADC1_SMPR2,28);
		CLR_BIT(ADC1_SMPR2,29);
#elif ADC_SAMP_RATE == SAMP_28_CYCLES
		SET_BIT(ADC1_SMPR2,27);
		SET_BIT(ADC1_SMPR2,28);
		CLR_BIT(ADC1_SMPR2,29);
#elif ADC_SAMP_RATE == SAMP_41_CYCLES
		CLR_BIT(ADC1_SMPR2,27);
		CLR_BIT(ADC1_SMPR2,28);
		SET_BIT(ADC1_SMPR2,29);
#elif ADC_SAMP_RATE == SAMP_55_CYCLES
		SET_BIT(ADC1_SMPR2,27);
		CLR_BIT(ADC1_SMPR2,28);
		SET_BIT(ADC1_SMPR2,29);
#elif ADC_SAMP_RATE == SAMP_71_CYCLES
		CLR_BIT(ADC1_SMPR2,27);
		SET_BIT(ADC1_SMPR2,28);
		SET_BIT(ADC1_SMPR2,29);
#elif ADC_SAMP_RATE == SAMP_239_CYCLES
		SET_BIT(ADC1_SMPR2,27);
		SET_BIT(ADC1_SMPR2,28);
		SET_BIT(ADC1_SMPR2,29);
#endif
		delayMs(1);
		SET_BIT(ADC1_SQR3,1);
		SET_BIT(ADC1_SQR3,3);
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		delayMs(1);

		while((ADC1_SR&(1<<1)) == 0);
		return ADC1_DR;

		break;
	default :
		break;

	}
}

void ADC_voidReadChannelInterrupt(uint16 Channel_u16Number){
	SET_BIT(ADC1_CR1,5);
	NVIC_voidEnableInterrupt(18);
	switch(Channel_u16Number){
	case 0:
#if ADC_SAMP_RATE == SAMP_1_CYCLES
		CLR_BIT(ADC1_SMPR2,0);
		CLR_BIT(ADC1_SMPR2,1);
		CLR_BIT(ADC1_SMPR2,2);
#elif ADC_SAMP_RATE == SAMP_7_CYCLES
		SET_BIT(ADC1_SMPR2,0);
		CLR_BIT(ADC1_SMPR2,1);
		CLR_BIT(ADC1_SMPR2,2);
#elif ADC_SAMP_RATE == SAMP_13_CYCLES
		CLR_BIT(ADC1_SMPR2,0);
		SET_BIT(ADC1_SMPR2,1);
		CLR_BIT(ADC1_SMPR2,2);
#elif ADC_SAMP_RATE == SAMP_28_CYCLES
		SET_BIT(ADC1_SMPR2,0);
		SET_BIT(ADC1_SMPR2,1);
		CLR_BIT(ADC1_SMPR2,2);
#elif ADC_SAMP_RATE == SAMP_41_CYCLES
		CLR_BIT(ADC1_SMPR2,0);
		CLR_BIT(ADC1_SMPR2,1);
		SET_BIT(ADC1_SMPR2,2);
#elif ADC_SAMP_RATE == SAMP_55_CYCLES
		SET_BIT(ADC1_SMPR2,0);
		CLR_BIT(ADC1_SMPR2,1);
		SET_BIT(ADC1_SMPR2,2);
#elif ADC_SAMP_RATE == SAMP_71_CYCLES
		CLR_BIT(ADC1_SMPR2,0);
		SET_BIT(ADC1_SMPR2,1);
		SET_BIT(ADC1_SMPR2,2);
#elif ADC_SAMP_RATE == SAMP_239_CYCLES
		SET_BIT(ADC1_SMPR2,0);
		SET_BIT(ADC1_SMPR2,1);
		SET_BIT(ADC1_SMPR2,2);
#endif
		delayMs(1);
		SET_BIT(ADC1_SQR3,0);
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		delayMs(1);
		NVIC_voidSetPendingFlag(18);

		break;
	case 1:
#if ADC_SAMP_RATE == SAMP_1_CYCLES
		CLR_BIT(ADC1_SMPR2,3);
		CLR_BIT(ADC1_SMPR2,4);
		CLR_BIT(ADC1_SMPR2,5);
#elif ADC_SAMP_RATE == SAMP_7_CYCLES
		SET_BIT(ADC1_SMPR2,3);
		CLR_BIT(ADC1_SMPR2,4);
		CLR_BIT(ADC1_SMPR2,5);
#elif ADC_SAMP_RATE == SAMP_13_CYCLES
		CLR_BIT(ADC1_SMPR2,3);
		SET_BIT(ADC1_SMPR2,4);
		CLR_BIT(ADC1_SMPR2,5);
#elif ADC_SAMP_RATE == SAMP_28_CYCLES
		SET_BIT(ADC1_SMPR2,3);
		SET_BIT(ADC1_SMPR2,4);
		CLR_BIT(ADC1_SMPR2,5);
#elif ADC_SAMP_RATE == SAMP_41_CYCLES
		CLR_BIT(ADC1_SMPR2,3);
		CLR_BIT(ADC1_SMPR2,4);
		SET_BIT(ADC1_SMPR2,5);
#elif ADC_SAMP_RATE == SAMP_55_CYCLES
		SET_BIT(ADC1_SMPR2,3);
		CLR_BIT(ADC1_SMPR2,4);
		SET_BIT(ADC1_SMPR2,5);
#elif ADC_SAMP_RATE == SAMP_71_CYCLES
		CLR_BIT(ADC1_SMPR2,3);
		SET_BIT(ADC1_SMPR2,4);
		SET_BIT(ADC1_SMPR2,5);
#elif ADC_SAMP_RATE == SAMP_239_CYCLES
		SET_BIT(ADC1_SMPR2,3);
		SET_BIT(ADC1_SMPR2,4);
		SET_BIT(ADC1_SMPR2,5);
#endif
		delayMs(1);
		SET_BIT(ADC1_SQR3,1);
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		delayMs(1);
		NVIC_voidSetPendingFlag(18);



		break;
	case 2:
#if ADC_SAMP_RATE == SAMP_1_CYCLES
		CLR_BIT(ADC1_SMPR2,6);
		CLR_BIT(ADC1_SMPR2,7);
		CLR_BIT(ADC1_SMPR2,8);
#elif ADC_SAMP_RATE == SAMP_7_CYCLES
		SET_BIT(ADC1_SMPR2,6);
		CLR_BIT(ADC1_SMPR2,7);
		CLR_BIT(ADC1_SMPR2,8);
#elif ADC_SAMP_RATE == SAMP_13_CYCLES
		CLR_BIT(ADC1_SMPR2,6);
		SET_BIT(ADC1_SMPR2,7);
		CLR_BIT(ADC1_SMPR2,8);
#elif ADC_SAMP_RATE == SAMP_28_CYCLES
		SET_BIT(ADC1_SMPR2,6);
		SET_BIT(ADC1_SMPR2,7);
		CLR_BIT(ADC1_SMPR2,8);
#elif ADC_SAMP_RATE == SAMP_41_CYCLES
		CLR_BIT(ADC1_SMPR2,6);
		CLR_BIT(ADC1_SMPR2,7);
		SET_BIT(ADC1_SMPR2,8);
#elif ADC_SAMP_RATE == SAMP_55_CYCLES
		SET_BIT(ADC1_SMPR2,6);
		CLR_BIT(ADC1_SMPR2,7);
		SET_BIT(ADC1_SMPR2,8);
#elif ADC_SAMP_RATE == SAMP_71_CYCLES
		CLR_BIT(ADC1_SMPR2,6);
		SET_BIT(ADC1_SMPR2,7);
		SET_BIT(ADC1_SMPR2,8);
#elif ADC_SAMP_RATE == SAMP_239_CYCLES
		SET_BIT(ADC1_SMPR2,6);
		SET_BIT(ADC1_SMPR2,7);
		SET_BIT(ADC1_SMPR2,8);
#endif
		delayMs(1);
		SET_BIT(ADC1_SQR3,0);
		SET_BIT(ADC1_SQR3,1);
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		delayMs(1);
		NVIC_voidSetPendingFlag(18);



		break;
	case 3:
#if ADC_SAMP_RATE == SAMP_1_CYCLES
		CLR_BIT(ADC1_SMPR2,9);
		CLR_BIT(ADC1_SMPR2,10);
		CLR_BIT(ADC1_SMPR2,11);
#elif ADC_SAMP_RATE == SAMP_7_CYCLES
		SET_BIT(ADC1_SMPR2,9);
		CLR_BIT(ADC1_SMPR2,10);
		CLR_BIT(ADC1_SMPR2,11);
#elif ADC_SAMP_RATE == SAMP_13_CYCLES
		CLR_BIT(ADC1_SMPR2,9);
		SET_BIT(ADC1_SMPR2,10);
		CLR_BIT(ADC1_SMPR2,11);
#elif ADC_SAMP_RATE == SAMP_28_CYCLES
		SET_BIT(ADC1_SMPR2,9);
		SET_BIT(ADC1_SMPR2,10);
		CLR_BIT(ADC1_SMPR2,11);
#elif ADC_SAMP_RATE == SAMP_41_CYCLES
		CLR_BIT(ADC1_SMPR2,9);
		CLR_BIT(ADC1_SMPR2,10);
		SET_BIT(ADC1_SMPR2,11);
#elif ADC_SAMP_RATE == SAMP_55_CYCLES
		SET_BIT(ADC1_SMPR2,9);
		CLR_BIT(ADC1_SMPR2,10);
		SET_BIT(ADC1_SMPR2,11);
#elif ADC_SAMP_RATE == SAMP_71_CYCLES
		CLR_BIT(ADC1_SMPR2,9);
		SET_BIT(ADC1_SMPR2,10);
		SET_BIT(ADC1_SMPR2,11);
#elif ADC_SAMP_RATE == SAMP_239_CYCLES
		SET_BIT(ADC1_SMPR2,9);
		SET_BIT(ADC1_SMPR2,10);
		SET_BIT(ADC1_SMPR2,11);
#endif
		delayMs(1);
		SET_BIT(ADC1_SQR3,2);
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		delayMs(1);
		NVIC_voidSetPendingFlag(18);



		break;
	case 4:
#if ADC_SAMP_RATE == SAMP_1_CYCLES
		CLR_BIT(ADC1_SMPR2,12);
		CLR_BIT(ADC1_SMPR2,13);
		CLR_BIT(ADC1_SMPR2,14);
#elif ADC_SAMP_RATE == SAMP_7_CYCLES
		SET_BIT(ADC1_SMPR2,12);
		CLR_BIT(ADC1_SMPR2,13);
		CLR_BIT(ADC1_SMPR2,14);
#elif ADC_SAMP_RATE == SAMP_13_CYCLES
		CLR_BIT(ADC1_SMPR2,12);
		SET_BIT(ADC1_SMPR2,13);
		CLR_BIT(ADC1_SMPR2,14);
#elif ADC_SAMP_RATE == SAMP_28_CYCLES
		SET_BIT(ADC1_SMPR2,12);
		SET_BIT(ADC1_SMPR2,13);
		CLR_BIT(ADC1_SMPR2,14);
#elif ADC_SAMP_RATE == SAMP_41_CYCLES
		CLR_BIT(ADC1_SMPR2,12);
		CLR_BIT(ADC1_SMPR2,13);
		SET_BIT(ADC1_SMPR2,14);
#elif ADC_SAMP_RATE == SAMP_55_CYCLES
		SET_BIT(ADC1_SMPR2,12);
		CLR_BIT(ADC1_SMPR2,13);
		SET_BIT(ADC1_SMPR2,14);
#elif ADC_SAMP_RATE == SAMP_71_CYCLES
		CLR_BIT(ADC1_SMPR2,12);
		SET_BIT(ADC1_SMPR2,13);
		SET_BIT(ADC1_SMPR2,14);
#elif ADC_SAMP_RATE == SAMP_239_CYCLES
		SET_BIT(ADC1_SMPR2,12);
		SET_BIT(ADC1_SMPR2,13);
		SET_BIT(ADC1_SMPR2,14);
#endif
		delayMs(1);
		SET_BIT(ADC1_SQR3,0);
		SET_BIT(ADC1_SQR3,2);
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		delayMs(1);
		NVIC_voidSetPendingFlag(18);



		break;
	case 5:
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
		delayMs(1);
		SET_BIT(ADC1_SQR3,1);
		SET_BIT(ADC1_SQR3,2);
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		delayMs(1);
		NVIC_voidSetPendingFlag(18);




		break;
	case 6:
#if ADC_SAMP_RATE == SAMP_1_CYCLES
		CLR_BIT(ADC1_SMPR2,18);
		CLR_BIT(ADC1_SMPR2,19);
		CLR_BIT(ADC1_SMPR2,20);
#elif ADC_SAMP_RATE == SAMP_7_CYCLES
		SET_BIT(ADC1_SMPR2,18);
		CLR_BIT(ADC1_SMPR2,19);
		CLR_BIT(ADC1_SMPR2,20);
#elif ADC_SAMP_RATE == SAMP_13_CYCLES
		CLR_BIT(ADC1_SMPR2,18);
		SET_BIT(ADC1_SMPR2,19);
		CLR_BIT(ADC1_SMPR2,20);
#elif ADC_SAMP_RATE == SAMP_28_CYCLES
		SET_BIT(ADC1_SMPR2,18);
		SET_BIT(ADC1_SMPR2,19);
		CLR_BIT(ADC1_SMPR2,20);
#elif ADC_SAMP_RATE == SAMP_41_CYCLES
		CLR_BIT(ADC1_SMPR2,18);
		CLR_BIT(ADC1_SMPR2,19);
		SET_BIT(ADC1_SMPR2,20);
#elif ADC_SAMP_RATE == SAMP_55_CYCLES
		SET_BIT(ADC1_SMPR2,18);
		CLR_BIT(ADC1_SMPR2,19);
		SET_BIT(ADC1_SMPR2,20);
#elif ADC_SAMP_RATE == SAMP_71_CYCLES
		CLR_BIT(ADC1_SMPR2,18);
		SET_BIT(ADC1_SMPR2,19);
		SET_BIT(ADC1_SMPR2,20);
#elif ADC_SAMP_RATE == SAMP_239_CYCLES
		SET_BIT(ADC1_SMPR2,18);
		SET_BIT(ADC1_SMPR2,19);
		SET_BIT(ADC1_SMPR2,20);
#endif
		delayMs(1);
		SET_BIT(ADC1_SQR3,0);
		SET_BIT(ADC1_SQR3,1);
		SET_BIT(ADC1_SQR3,2);
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		delayMs(1);
		NVIC_voidSetPendingFlag(18);


		break;
	case 7:
#if ADC_SAMP_RATE == SAMP_1_CYCLES
		CLR_BIT(ADC1_SMPR2,21);
		CLR_BIT(ADC1_SMPR2,22);
		CLR_BIT(ADC1_SMPR2,23);
#elif ADC_SAMP_RATE == SAMP_7_CYCLES
		SET_BIT(ADC1_SMPR2,21);
		CLR_BIT(ADC1_SMPR2,22);
		CLR_BIT(ADC1_SMPR2,23);
#elif ADC_SAMP_RATE == SAMP_13_CYCLES
		CLR_BIT(ADC1_SMPR2,21);
		SET_BIT(ADC1_SMPR2,22);
		CLR_BIT(ADC1_SMPR2,23);
#elif ADC_SAMP_RATE == SAMP_28_CYCLES
		SET_BIT(ADC1_SMPR2,21);
		SET_BIT(ADC1_SMPR2,22);
		CLR_BIT(ADC1_SMPR2,23);
#elif ADC_SAMP_RATE == SAMP_41_CYCLES
		CLR_BIT(ADC1_SMPR2,21);
		CLR_BIT(ADC1_SMPR2,22);
		SET_BIT(ADC1_SMPR2,23);
#elif ADC_SAMP_RATE == SAMP_55_CYCLES
		SET_BIT(ADC1_SMPR2,21);
		CLR_BIT(ADC1_SMPR2,22);
		SET_BIT(ADC1_SMPR2,23);
#elif ADC_SAMP_RATE == SAMP_71_CYCLES
		CLR_BIT(ADC1_SMPR2,21);
		SET_BIT(ADC1_SMPR2,22);
		SET_BIT(ADC1_SMPR2,23);
#elif ADC_SAMP_RATE == SAMP_239_CYCLES
		SET_BIT(ADC1_SMPR2,21);
		SET_BIT(ADC1_SMPR2,22);
		SET_BIT(ADC1_SMPR2,23);
#endif
		delayMs(1);
		SET_BIT(ADC1_SQR3,3);
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		delayMs(1);
		NVIC_voidSetPendingFlag(18);

		break;
	case 8:
#if ADC_SAMP_RATE == SAMP_1_CYCLES
		CLR_BIT(ADC1_SMPR2,24);
		CLR_BIT(ADC1_SMPR2,25);
		CLR_BIT(ADC1_SMPR2,26);
#elif ADC_SAMP_RATE == SAMP_7_CYCLES
		SET_BIT(ADC1_SMPR2,24);
		CLR_BIT(ADC1_SMPR2,25);
		CLR_BIT(ADC1_SMPR2,26);
#elif ADC_SAMP_RATE == SAMP_13_CYCLES
		CLR_BIT(ADC1_SMPR2,24);
		SET_BIT(ADC1_SMPR2,25);
		CLR_BIT(ADC1_SMPR2,26);
#elif ADC_SAMP_RATE == SAMP_28_CYCLES
		SET_BIT(ADC1_SMPR2,24);
		SET_BIT(ADC1_SMPR2,25);
		CLR_BIT(ADC1_SMPR2,26);
#elif ADC_SAMP_RATE == SAMP_41_CYCLES
		CLR_BIT(ADC1_SMPR2,24);
		CLR_BIT(ADC1_SMPR2,25);
		SET_BIT(ADC1_SMPR2,26);
#elif ADC_SAMP_RATE == SAMP_55_CYCLES
		SET_BIT(ADC1_SMPR2,24);
		CLR_BIT(ADC1_SMPR2,25);
		SET_BIT(ADC1_SMPR2,26);
#elif ADC_SAMP_RATE == SAMP_71_CYCLES
		CLR_BIT(ADC1_SMPR2,24);
		SET_BIT(ADC1_SMPR2,25);
		SET_BIT(ADC1_SMPR2,26);
#elif ADC_SAMP_RATE == SAMP_239_CYCLES
		SET_BIT(ADC1_SMPR2,24);
		SET_BIT(ADC1_SMPR2,25);
		SET_BIT(ADC1_SMPR2,26);
#endif
		delayMs(1);
		SET_BIT(ADC1_SQR3,0);
		SET_BIT(ADC1_SQR3,3);
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		delayMs(1);
		NVIC_voidSetPendingFlag(18);


		break;
	case 9:
#if ADC_SAMP_RATE == SAMP_1_CYCLES
		CLR_BIT(ADC1_SMPR2,27);
		CLR_BIT(ADC1_SMPR2,28);
		CLR_BIT(ADC1_SMPR2,29);
#elif ADC_SAMP_RATE == SAMP_7_CYCLES
		SET_BIT(ADC1_SMPR2,27);
		CLR_BIT(ADC1_SMPR2,28);
		CLR_BIT(ADC1_SMPR2,29);
#elif ADC_SAMP_RATE == SAMP_13_CYCLES
		CLR_BIT(ADC1_SMPR2,27);
		SET_BIT(ADC1_SMPR2,28);
		CLR_BIT(ADC1_SMPR2,29);
#elif ADC_SAMP_RATE == SAMP_28_CYCLES
		SET_BIT(ADC1_SMPR2,27);
		SET_BIT(ADC1_SMPR2,28);
		CLR_BIT(ADC1_SMPR2,29);
#elif ADC_SAMP_RATE == SAMP_41_CYCLES
		CLR_BIT(ADC1_SMPR2,27);
		CLR_BIT(ADC1_SMPR2,28);
		SET_BIT(ADC1_SMPR2,29);
#elif ADC_SAMP_RATE == SAMP_55_CYCLES
		SET_BIT(ADC1_SMPR2,27);
		CLR_BIT(ADC1_SMPR2,28);
		SET_BIT(ADC1_SMPR2,29);
#elif ADC_SAMP_RATE == SAMP_71_CYCLES
		CLR_BIT(ADC1_SMPR2,27);
		SET_BIT(ADC1_SMPR2,28);
		SET_BIT(ADC1_SMPR2,29);
#elif ADC_SAMP_RATE == SAMP_239_CYCLES
		SET_BIT(ADC1_SMPR2,27);
		SET_BIT(ADC1_SMPR2,28);
		SET_BIT(ADC1_SMPR2,29);
#endif
		delayMs(1);
		SET_BIT(ADC1_SQR3,1);
		SET_BIT(ADC1_SQR3,3);
		SET_BIT(ADC1_CR2,0);
		SET_BIT(ADC1_CR2,1);
		delayMs(1);
		NVIC_voidSetPendingFlag(18);


		break;

	}

}

void ADC1_2_IRQHandler(void){
	val=ADC1_DR;
	if(g_callBackPtr!=NULL_PTR){
		(*g_callBackPtr)();
	}
}
void ADC1_voidSetCallBack(void(*a_ptr)(void)){
	g_callBackPtr=a_ptr;
}



