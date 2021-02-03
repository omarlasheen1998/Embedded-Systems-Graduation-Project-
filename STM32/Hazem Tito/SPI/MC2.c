#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_config.h"
#include "SPI_interface.h"
#include "SPI_private.h"
#include "SPI_config.h"

int main(void){
uint8 character;
RCC_APB2ENR|=0xFC;
SPI_voidInitSlave(SPI_2); /* SLAVE IS A STM MICROCONTROLLER*/
character=SPI_u8RecieveByte(SPI_2);

}