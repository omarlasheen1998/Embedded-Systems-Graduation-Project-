/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 22 SEP 2020                                                       */
/*********************************************************************************/
#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H


/*******************   Register Definition     ***********************/
#define RCC_CR                *((uint32*)0x40021000)
#define RCC_CFGR              *((uint32*)0x40021004)
#define RCC_CIR               *((uint32*)0x40021008)
#define RCC_APB2RSTR          *((uint32*)0x4002100C)
#define RCC_APB1RSTR          *((uint32*)0x40021010)
#define RCC_AHBENR            *((uint32*)0x40021014)
#define RCC_APB2ENR           *((uint32*)0x40021018)
#define RCC_APB1ENR           *((uint32*)0x4002101C)
#define RCC_BDCR              *((uint32*)0x40021020)
#define RCC_CSR               *((uint32*)0x40021024)

/*******************     Clock Types      *****************************/
#define RCC_HSE_CRYSTAL       0
#define RCC_HSE_RC            1
#define RCC_HSI               2
#define RCC_PLL               3

/*******************   PLL INPUT Options   ****************************/
#define RCC_PLL_IN_HSI_DIV_2  0
#define RCC_PLL_IN_HSE_DIV_2  1
#define RCC_PLL_IN_HSE        2




#endif // RCC_PRIVATE_H
