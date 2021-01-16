/*********************************************************************************/
/* Author    : Omar Lasheen                                                        */
/* Version   : V01                                                               */
/* Date      : 14 Jan 2021                                                       */
/*********************************************************************************/
#include "STD_TYPES.h"

#ifndef PWM_PRIVATE_H
#define PWM_PRIVATE_H


#define TIM1_Base_Address      (u32)(0x40012C00)      //define the boundary address of TIM1
#define TIM2_Base_Address      (u32)(0x40000000)      //define the boundary address of TIM2
#define TIM3_Base_Address      (u32)(0x40000400)      //define the boundary address of TIM3
#define TIM4_Base_Address      (u32)(0x40000800)      //define the boundary address of TIM4

/***********   REGISTER ADDRESSES FOR TIM1     ***********************/

#define TIM1_CR1  *((u32 *)(TIM1_Base_Address + 0X00))
#define TIM1_CR2  *((u32 *)(TIM1_Base_Address + 0X04))
#define TIM1_SMCR  *((u32 *)(TIM1_Base_Address + 0X08))
#define TIM1_DIER  *((u32 *)(TIM1_Base_Address + 0X0C))
#define TIM1_SR  *((u32 *)(TIM1_Base_Address + 0X10))
#define TIM1_EGR  *((u32 *)(TIM1_Base_Address + 0x14))
#define TIM1_CCMR1  *((u32 *)(TIM1_Base_Address + 0X18))
#define TIM1_CCMR2  *((u32 *)(TIM1_Base_Address + 0X1C))
#define TIM1_CCER  *((u32 *)(TIM1_Base_Address + 0X20))
#define TIM1_CNT  *((u32 *)(TIM1_Base_Address + 0X24))
#define TIM1_PSC  *((u32 *)(TIM1_Base_Address + 0X28))
#define TIM1_ARR  *((u32 *)(TIM1_Base_Address + 0X2C))
#define TIM1_RCR  *((u32 *)(TIM1_Base_Address + 0X30))
#define TIM1_CCR1  *((u32 *)(TIM1_Base_Address + 0X34))
#define TIM1_CCR2  *((u32 *)(TIM1_Base_Address + 0X38))
#define TIM1_CCR3  *((u32 *)(TIM1_Base_Address + 0X3C))
#define TIM1_CCR4  *((u32 *)(TIM1_Base_Address + 0X40))
#define TIM1_BDTR  *((u32 *)(TIM1_Base_Address + 0X44))
#define TIM1_DCR  *((u32 *)(TIM1_Base_Address + 0X48))
#define TIM1_DMAR  *((u32 *)(TIM1_Base_Address + 0X4C))

/***********   REGISTER ADDRESSES FOR TIM2     ***********************/

#define TIM2_CR1  *((u32 *)(TIM2_Base_Address + 0X00))
#define TIM2_CR2  *((u32 *)(TIM2_Base_Address + 0X04))
#define TIM2_SMCR  *((u32 *)(TIM2_Base_Address + 0X08))
#define TIM2_DIER  *((u32 *)(TIM2_Base_Address + 0X0C))
#define TIM2_SR  *((u32 *)(TIM2_Base_Address + 0X10))
#define TIM2_EGR  *((u32 *)(TIM2_Base_Address + 0x14))
#define TIM2_CCMR1  *((u32 *)(TIM2_Base_Address + 0X18))
#define TIM2_CCMR2  *((u32 *)(TIM2_Base_Address + 0X1C))
#define TIM2_CCER  *((u32 *)(TIM2_Base_Address + 0X20))
#define TIM2_CNT  *((u32 *)(TIM2_Base_Address + 0X24))
#define TIM2_PSC  *((u32 *)(TIM2_Base_Address + 0X28))
#define TIM2_ARR  *((u32 *)(TIM2_Base_Address + 0X2C))
#define TIM2_CCR1  *((u32 *)(TIM2_Base_Address + 0X34))
#define TIM2_CCR2  *((u32 *)(TIM2_Base_Address + 0X38))
#define TIM2_CCR3  *((u32 *)(TIM2_Base_Address + 0X3C))
#define TIM2_CCR4  *((u32 *)(TIM2_Base_Address + 0X40))
#define TIM2_DCR  *((u32 *)(TIM2_Base_Address + 0X48))
#define TIM2_DMAR  *((u32 *)(TIM2_Base_Address + 0X4C))

/***********   REGISTER ADDRESSES FOR TIM3     ***********************/

#define TIM3_CR1  *((u32 *)(TIM3_Base_Address + 0X00))
#define TIM3_CR2  *((u32 *)(TIM3_Base_Address + 0X04))
#define TIM3_SMCR  *((u32 *)(TIM3_Base_Address + 0X08))
#define TIM3_DIER  *((u32 *)(TIM3_Base_Address + 0X0C))
#define TIM3_SR  *((u32 *)(TIM3_Base_Address + 0X10))
#define TIM3_EGR  *((u32 *)(TIM3_Base_Address + 0x14))
#define TIM3_CCMR1  *((u32 *)(TIM3_Base_Address + 0X18))
#define TIM3_CCMR2  *((u32 *)(TIM3_Base_Address + 0X1C))
#define TIM3_CCER  *((u32 *)(TIM3_Base_Address + 0X20))
#define TIM3_CNT  *((u32 *)(TIM3_Base_Address + 0X24))
#define TIM3_PSC  *((u32 *)(TIM3_Base_Address + 0X28))
#define TIM3_ARR  *((u32 *)(TIM3_Base_Address + 0X2C))
#define TIM3_CCR1  *((u32 *)(TIM3_Base_Address + 0X34))
#define TIM3_CCR2  *((u32 *)(TIM3_Base_Address + 0X38))
#define TIM3_CCR3  *((u32 *)(TIM3_Base_Address + 0X3C))
#define TIM3_CCR4  *((u32 *)(TIM3_Base_Address + 0X40))
#define TIM3_DCR  *((u32 *)(TIM3_Base_Address + 0X48))
#define TIM3_DMAR  *((u32 *)(TIM3_Base_Address + 0X4C))

/***********   REGISTER ADDRESSES FOR TIM4     ***********************/

#define TIM4_CR1  *((u32 *)(TIM4_Base_Address + 0X00))
#define TIM4_CR2  *((u32 *)(TIM4_Base_Address + 0X04))
#define TIM4_SMCR  *((u32 *)(TIM4_Base_Address + 0X08))
#define TIM4_DIER  *((u32 *)(TIM4_Base_Address + 0X0C))
#define TIM4_SR  *((u32 *)(TIM4_Base_Address + 0X10))
#define TIM4_EGR  *((u32 *)(TIM4_Base_Address + 0x14))
#define TIM4_CCMR1  *((u32 *)(TIM4_Base_Address + 0X18))
#define TIM4_CCMR2  *((u32 *)(TIM4_Base_Address + 0X1C))
#define TIM4_CCER  *((u32 *)(TIM4_Base_Address + 0X20))
#define TIM4_CNT  *((u32 *)(TIM4_Base_Address + 0X24))
#define TIM4_PSC  *((u32 *)(TIM4_Base_Address + 0X28))
#define TIM4_ARR  *((u32 *)(TIM4_Base_Address + 0X2C))
#define TIM4_CCR1  *((u32 *)(TIM4_Base_Address + 0X34))
#define TIM4_CCR2  *((u32 *)(TIM4_Base_Address + 0X38))
#define TIM4_CCR3  *((u32 *)(TIM4_Base_Address + 0X3C))
#define TIM4_CCR4  *((u32 *)(TIM4_Base_Address + 0X40))
#define TIM4_DCR  *((u32 *)(TIM4_Base_Address + 0X48))
#define TIM4_DMAR  *((u32 *)(TIM4_Base_Address + 0X4C))

#endif // PWM_PRIVATE_H