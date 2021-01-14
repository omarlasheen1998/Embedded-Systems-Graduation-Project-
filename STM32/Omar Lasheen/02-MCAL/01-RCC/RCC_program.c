/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 22 SEP 2020                                                       */
/*********************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_config.h"

void RCC_voidInitSysClock(void)
{
    #if      RCC_CLOCK_TYPE == RCC_HSE_CRYSTAL
        RCC_CR   = 0x00010000;     /* Enable HSE with no bypass */
        RCC_CFGR = 0x00000001;     /* HSE selected as system clock */
    #elif    RCC_CLOCK_TYPE == RCC_HSE_RC
        RCC_CR   = 0x00050000;     /* Enable HSE with bypass */
        RCC_CFGR = 0x00000001;     /* HSE selected as system clock */
    #elif    RCC_CLOCK_TYPE == RCC_HSI
        RCC_CR   = 0x00000081;     /* Enable HSI + Trimming = 0 */
        RCC_CFGR = 0x00000000;     /* HSI selected as system clock */
    #elif    RCC_CLOCK_TYPE == RCC_PLL
        #if   RCC_PLL_INPUT == RCC_PLL_IN_HSI_DIV_2
            RCC_CR   = 0x01000081; /* Enable HSI + Trimming = 0 + ENABLE PLL*/
            RCC_CFGR = 0x00000000; /* HSI/2 selected as system clock */
        #elif RCC_PLL_INPUT == RCC_PLL_IN_HSE_DIV_2
            RCC_CR   = 0x01010000;     /* Enable HSE with no bypass */
            RCC_CFGR = 0x00010001;     /* HSE/2 selected as system clock */

        #elif RCC_PLL_INPUT == RCC_PLL_IN_HSE
            RCC_CR   = 0x01010000;     /* Enable HSE with no bypass */
            RCC_CFGR = 0x00030001;     /* HSE/2 selected as system clock */

        #endif // RCC_PLL_INPUT


    #else
        #error("You chosed Wrong Clock type")

    #endif
}

void RCC_voidEnableClock(uint8 Copy_u8BusId, uint8 Copy_u8PerId)
{
    if (Copy_u8PerId <= 31)
    {
        switch (Copy_u8BusId)
        {
            case RCC_AHB  : SET_BIT(RCC_AHBENR  ,Copy_u8PerId);    break;
            case RCC_APB1 : SET_BIT(RCC_APB1ENR ,Copy_u8PerId);    break;
            case RCC_APB2 : SET_BIT(RCC_APB2ENR ,Copy_u8PerId);    break;
            //default       : /* Return Error */          break;
        }
    }

    else
    {
        /* Return Error */
    }
}


void RCC_voidDisableClock(uint8 Copy_u8BusId, uint8 Copy_u8PerId)
{
    if (Copy_u8PerId <= 31)
    {
        switch (Copy_u8BusId)
        {
            case RCC_AHB  : CLR_BIT(RCC_AHBENR  ,Copy_u8PerId);    break;
            case RCC_APB1 : CLR_BIT(RCC_APB1ENR ,Copy_u8PerId);    break;
            case RCC_APB2 : CLR_BIT(RCC_APB2ENR ,Copy_u8PerId);    break;
            //default       : /* Return Error */          break;
        }
    }

    else
    {
        /* Return Error */
    }
}

