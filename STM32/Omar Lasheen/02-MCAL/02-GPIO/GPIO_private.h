/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 23 SEP 2020                                                       */
/*********************************************************************************/
#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H


#define GPIOA_Base_Address      0x40010800      //define the boundary address of GPIOA
#define GPIOB_Base_Address      0x40010C00      //define the boundary address of GPIOB
#define GPIOC_Base_Address      0x40011000      //define the boundary address of GPIOC

/***********   REGISTER ADDRESSES FOR GPIOA     ***********************/

#define GPIOA_CRL               *((uint32 *)(GPIOA_Base_Address + 0X00))
#define GPIOA_CRH               *((uint32 *)(GPIOA_Base_Address + 0X04))
#define GPIOA_IDR               *((uint32 *)(GPIOA_Base_Address + 0X08))
#define GPIOA_ODR               *((uint32 *)(GPIOA_Base_Address + 0X0C))
#define GPIOA_BSRR              *((uint32 *)(GPIOA_Base_Address + 0X10))
#define GPIOA_BRR               *((uint32 *)(GPIOA_Base_Address + 0X14))
#define GPIOA_LCKR              *((uint32 *)(GPIOA_Base_Address + 0X18))

/***********   REGISTER ADDRESSES FOR GPIOB     ***********************/

#define GPIOB_CRL               *((uint32 *)(GPIOB_Base_Address + 0X00))
#define GPIOB_CRH               *((uint32 *)(GPIOB_Base_Address + 0X04))
#define GPIOB_IDR               *((uint32 *)(GPIOB_Base_Address + 0X08))
#define GPIOB_ODR               *((uint32 *)(GPIOB_Base_Address + 0X0C))
#define GPIOB_BSRR              *((uint32 *)(GPIOB_Base_Address + 0X10))
#define GPIOB_BRR               *((uint32 *)(GPIOB_Base_Address + 0X14))
#define GPIOB_LCKR              *((uint32 *)(GPIOB_Base_Address + 0X18))

/***********   REGISTER ADDRESSES FOR GPIOC     ***********************/

#define GPIOC_CRL               *((uint32 *)(GPIOC_Base_Address + 0X00))
#define GPIOC_CRH               *((uint32 *)(GPIOC_Base_Address + 0X04))
#define GPIOC_IDR               *((uint32 *)(GPIOC_Base_Address + 0X08))
#define GPIOC_ODR               *((uint32 *)(GPIOC_Base_Address + 0X0C))
#define GPIOC_BSRR              *((uint32 *)(GPIOC_Base_Address + 0X10))
#define GPIOC_BRR               *((uint32 *)(GPIOC_Base_Address + 0X14))
#define GPIOC_LCKR              *((uint32 *)(GPIOC_Base_Address + 0X18))

#endif // GPIO_PRIVATE_H
