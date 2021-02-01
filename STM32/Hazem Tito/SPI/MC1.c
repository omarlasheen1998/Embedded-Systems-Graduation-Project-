#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_config.h"
#include "SPI_interface.h"
#include "SPI_private.h"
#include "SPI_config.h"

int main(void){
RCC_APB2ENR|=0xFC;
SPI_voidInitMaster(SPI_1);
SPI_voidSendByte(SPI_1,'C');

}