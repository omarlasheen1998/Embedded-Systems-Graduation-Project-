
#include "01-LIB/01-STD_TYPES/STD_TYPES.h"
#include "01-LIB/02-BIT_MATH/BIT_MATH.h"

#include "02-MCAL/C Drivers/01-SYSCTL/SYSCTL_interface.h"
#include "02-MCAL/C Drivers/01-SYSCTL/SYSCTL_private.h"
#include "02-MCAL/C Drivers/01-SYSCTL/SYSCTL_config.h"


void SYSCTL_voidSetClockSpeed(uint8 Copy_u8ClockSpeed){
    if(Copy_u8ClockSpeed > 3 && Copy_u8ClockSpeed < 128){
        SYSCTL_RCC2 |= (1 << RCC2_USERCC2);
        SYSCTL_RCC2 |= (1 << RCC2_BYPASS2);

        SYSCTL_RCC = (SYSCTL_RCC & ~(0x000007C0)) + 0x00000540;

        SYSCTL_RCC2 &= ~(7 << RCC2_OSCSRC2);
        SYSCTL_RCC2 &= ~(1 << RCC2_PWRDN2);

        SYSCTL_RCC2 |= (1 << RCC2_DIV400);
        SYSCTL_RCC2 &= ~(0x7F << RCC2_SYSDIV2LSB);
        SYSCTL_RCC2 |= (Copy_u8ClockSpeed << RCC2_SYSDIV2LSB);

        while(!(SYSCTL_RIS & (1 << RIS_PLLRIS)));
        SYSCTL_RCC2 &= ~(1 << RCC2_BYPASS2);

    }
    else {
        /* Return error */
    }
}

