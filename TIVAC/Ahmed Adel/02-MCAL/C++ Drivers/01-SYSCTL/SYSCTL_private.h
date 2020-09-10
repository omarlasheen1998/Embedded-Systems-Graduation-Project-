/********************************************/
/* Author   : Ahmed Ismail                  */
/* Date     : 30 AUG 2020                   */
/* Version  : V01                           */
/********************************************/
#include "01-LIB/01-STD_TYPES/STD_TYPES.h"

#ifndef SYSCTL_PRIVATE_H
#define SYSCTL_PRIVATE_H



/* Registers definitions  */


// BASE_ADDRESS = 0x400F E000
#define  SYSCTL_DID0           *((volatile uint32 *) 0x400FE000)
#define  SYSCTL_DID1           *((volatile uint32 *) 0x400FE004)
#define  SYSCTL_PBORCTL        *((volatile uint32 *) 0x400FE030)
#define  SYSCTL_RIS            *((volatile uint32 *) 0x400FE050)
#define  SYSCTL_IMC            *((volatile uint32 *) 0x400FE054)
#define  SYSCTL_MISC           *((volatile uint32 *) 0x400FE058)
#define  SYSCTL_RESC           *((volatile uint32 *) 0x400FE05C)
#define  SYSCTL_RCC            *((volatile uint32 *) 0x400FE060)
#define  SYSCTL_GPIOHBCTL      *((volatile uint32 *) 0x400FE06C)
#define  SYSCTL_RCC2           *((volatile uint32 *) 0x400FE070)
#define  SYSCTL_MOSCCTL        *((volatile uint32 *) 0x400FE07C)
#define  SYSCTL_DSLPCLKCFG     *((volatile uint32 *) 0x400FE144)
#define  SYSCTL_SYSPROP        *((volatile uint32 *) 0x400FE14C)
#define  SYSCTL_PIOSCCAL       *((volatile uint32 *) 0x400FE150)
#define  SYSCTL_PIOSCSTAT      *((volatile uint32 *) 0x400FE154)
#define  SYSCTL_PLLFREQ0       *((volatile uint32 *) 0x400FE160)
#define  SYSCTL_PLLFREQ1       *((volatile uint32 *) 0x400FE164)
#define  SYSCTL_PLLSTAT        *((volatile uint32 *) 0x400FE168)
#define  SYSCTL_SLPPWRCFG      *((volatile uint32 *) 0x400FE188)
#define  SYSCTL_DSLPPWRCFG     *((volatile uint32 *) 0x400FE18C)
#define  SYSCTL_LDOSPCTL       *((volatile uint32 *) 0x400FE1B4)
#define  SYSCTL_LDOSPCAL       *((volatile uint32 *) 0x400FE1B8)
#define  SYSCTL_LDODPCTL       *((volatile uint32 *) 0x400FE1BC)
#define  SYSCTL_LDODPCAL       *((volatile uint32 *) 0x400FE1C0)
#define  SYSCTL_SDPMST         *((volatile uint32 *) 0x400FE1CC)
#define  SYSCTL_PPWD           *((volatile uint32 *) 0x400FE300)
#define  SYSCTL_PPTIMER        *((volatile uint32 *) 0x400FE304)
#define  SYSCTL_PPGPIO         *((volatile uint32 *) 0x400FE308)
#define  SYSCTL_PPDMA          *((volatile uint32 *) 0x400FE30C)
#define  SYSCTL_PPHIB          *((volatile uint32 *) 0x400FE314)
#define  SYSCTL_PPUART         *((volatile uint32 *) 0x400FE318)
#define  SYSCTL_PPSSI          *((volatile uint32 *) 0x400FE31C)
#define  SYSCTL_PPI2C          *((volatile uint32 *) 0x400FE320)
#define  SYSCTL_PPUSB          *((volatile uint32 *) 0x400FE328)
#define  SYSCTL_PPCAN          *((volatile uint32 *) 0x400FE334)
#define  SYSCTL_PPADC          *((volatile uint32 *) 0x400FE338)
#define  SYSCTL_PPACMP         *((volatile uint32 *) 0x400FE33C)
#define  SYSCTL_PPPWM          *((volatile uint32 *) 0x400FE340)
#define  SYSCTL_PPQEI          *((volatile uint32 *) 0x400FE344)

#define  SYSCTL_PPEEPROM       *((volatile uint32 *) 0x400FE358)
#define  SYSCTL_PPWTIMER       *((volatile uint32 *) 0x400FE35C)
#define  SYSCTL_SRWD           *((volatile uint32 *) 0x400FE500)
#define  SYSCTL_SRTIMER        *((volatile uint32 *) 0x400FE504)
#define  SYSCTL_SRGPIO         *((volatile uint32 *) 0x400FE508)

#define  SYSCTL_SRDMA          *((volatile uint32 *) 0x400FE50C)
#define  SYSCTL_SRHIB          *((volatile uint32 *) 0x400FE514)
#define  SYSCTL_SRUART         *((volatile uint32 *) 0x400FE518)
#define  SYSCTL_SRSSI          *((volatile uint32 *) 0x400FE51C)
#define  SYSCTL_SRI2C          *((volatile uint32 *) 0x400FE520)
#define  SYSCTL_SRUSB          *((volatile uint32 *) 0x400FE528)
#define  SYSCTL_SRCAN          *((volatile uint32 *) 0x400FE534)
#define  SYSCTL_SRADC          *((volatile uint32 *) 0x400FE538)
#define  SYSCTL_SRACMP         *((volatile uint32 *) 0x400FE53C)
#define  SYSCTL_SRPWM          *((volatile uint32 *) 0x400FE540)
#define  SYSCTL_SRQEI          *((volatile uint32 *) 0x400FE544)
#define  SYSCTL_SREEPROM       *((volatile uint32 *) 0x400FE558)
#define  SYSCTL_SRWTIMER       *((volatile uint32 *) 0x400FE55C)


// RCC2 Register Pins
#define RCC2_OSCSRC2     ((uint8) 4 )   //OSCSRC LSB
#define RCC2_BYPASS2     ((uint8) 11)
#define RCC2_PWRDN2      ((uint8) 13)
#define RCC2_USBPWRDN    ((uint8) 14)
#define RCC2_SYSDIV2LSB  ((uint8) 22)
#define RCC2_SYSDIV2     ((uint8) 23)
#define RCC2_DIV400      ((uint8) 30)
#define RCC2_USERCC2     ((uint8) 31)

// RCC Register Pins
#define RCC_MOSCDIS     (uint8) 0
#define RCC_OSCSRC      (uint8) 4
#define RCC_XTAL        (uint8) 6
#define RCC_BYPASS      (uint8) 11
#define RCC_PWRDN       (uint8) 13
#define RCC_PWMDIV      (uint8) 17
#define RCC_USEPWMDIV   (uint8) 20
#define RCC_USESYSDIV   (uint8) 22
#define RCC_SYSDIV      (uint8) 23
#define RCC_ACG         (uint8) 27


// RIS Register Pins
#define RIS_BOR1RIS     (uint8) 1
#define RIS_MOFRIS      (uint8) 3
#define RIS_PLLRIS      (uint8) 6
#define RIS_USBPLLRIS   (uint8) 7
#define RIS_MOSCPUPRIS  (uint8) 8
#define RIS_VDDARIS     (uint8) 10
#define RIS_BOR0RIS     (uint8) 11




#endif /* SYSCTL_PRIVATE_H */
