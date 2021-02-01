#include "STD_TYPES.h"
#ifndef SPI_INTERFACE_H
#define SPI_INTERFACE_H




#define SPI_1 1
#define SPI_2 2



/*********************functions prototypes******************/

void SPI_voidInitMaster(uint8 Copy_u8spi);
void SPI_voidInitSlave(uint8 Copy_u8spi);
void SPI_voidSendByte(uint8 Copy_u8spi,const uint8 Copy_u8data);
uint8 SPI_u8RecieveByte(uint8 Copy_u8spi);
void SPI_voidSendString(uint8 Copy_u8spi,const uint8 *Copy_u8str);
void SPI_voidRecieveString(uint8 Copy_u8spi,char*str);
uint8 SPI_u8ReadInterrupt(uint8 Copy_u8spi);
uint8 SPI_u8ReturnData(uint8 Copy_u8spi);
void SPI_voidLoadData(uint8 Copy_u8spi,uint8 Copy_u8data);
void SPI1_voidSetInterrupt(void (*LOCAL_PTR)(void));
void SPI2_voidSetInterrupt(void (*LOCAL_PTR)(void));

#endif
