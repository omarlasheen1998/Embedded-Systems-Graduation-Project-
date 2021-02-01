/*********************************************************************************/
/* Author    : Hazem Magdy                                                       */
/* Version   : V01                                                               */
/* Date      : 29 Jan 2021                                                       */
/*********************************************************************************/
#include "STD_TYPES.h"

#ifndef SPI_PRIVATE_H
#define SPI_PRIVATE_H
/************register declaration for SPI1*******************/

#define SPI1_CR1      *((uint32*)0x40013000)
#define SPI1_CR2      *((uint32*)0x40013004)
#define SPI1_SR       *((uint32*)0x40013008)
#define SPI1_DR       *((uint32*)0x4001300C)
#define SPI1_CRCPR    *((uint32*)0x40013010)
#define SPI1_RXCRCR   *((uint32*)0x40013014)
#define SPI1_TXCRCR   *((uint32*)0x40013018)
#define SPI1_I2SCFGR  *((uint32*)0x4001301C)
#define SPI1_I2SPR    *((uint32*)0x40013020)
/************register declaration for SPI2*******************/



#define SPI2_CR1          *((uint32*)0x40003800)
#define SPI2_CR2          *((uint32*)0x40003804)
#define SPI2_SR           *((uint32*)0x40003808)
#define SPI2_DR           *((uint32*)0x4000380C)
#define SPI2_CRCPR        *((uint32*)0x40003810)
#define SPI2_RXCRCR       *((uint32*)0x40003814)
#define SPI2_TXCRCR       *((uint32*)0x40003818)
#define SPI2_I2SCFGR      *((uint32*)0x4000381C)
#define SPI2_I2SPR        *((uint32*)0x40003820)

/*******************BAUD RATE CONFIGURATION **********************/
#define CLK_2   0
#define CLK_4   1
#define CLK_8   2
#define CLK_16  3
#define CLK_32  4
#define CLK_64  5
#define CLK_128 6
#define CLK_256 7


#endif
