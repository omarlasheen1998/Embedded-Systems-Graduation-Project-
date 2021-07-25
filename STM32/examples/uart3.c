#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_private.h"
#include "EXTI_interface.h"
#include "RCC_INTERFACE.h"
#include "USART_INTERFACE.h"
#include "NVIC_interface.h"
#include "GPIO_interface.h"
#include "STK_interface.h"

f32 x =0.008;
f32 *ptr=&x;


int main(void){
	
RCC_voidInitSysClock();	
RCC_voidEnableClock(RCC_APB1,APB1_USART3_EN);
RCC_voidEnableClock(RCC_APB2,APB2_GPIOB_EN);
RCC_voidEnableClock(RCC_APB2,APB2_GPIOC_EN);
RCC_voidEnableClock(RCC_APB2,APB2_GPIOA_EN);
USART_voidInit(UART3,9600);
//STK_voidInit();
	
while(1){

  USART_voidTransmit(UART3,ptr,FLOAT);
  USART_voidTransmit(UART3,"\n",STRING);
  STK_voidDelay_ms(1000);  
}

}