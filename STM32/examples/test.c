#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_private.h"
#include "EXTI_interface.h"
#include "RCC_INTERFACE.h"
#include "USART_INTERFACE.h"
#include "NVIC_interface.h"
#include "GPIO_interface.h"
#include "STK_interface.h"
#include "TIMER_INTERFACE.h"
#include "PWM_INTERFACE.h"

u64 x =0;
u64 *ptr=&x;



int main(void){
	
RCC_voidInitSysClock();	
RCC_voidEnableClock(RCC_APB2,APB2_AFIO_EN);
RCC_voidEnableClock(RCC_APB2,APB2_USART1_EN);
RCC_voidEnableClock(RCC_APB1,APB1_TIM2_EN);
RCC_voidEnableClock(RCC_APB2,APB2_GPIOB_EN);
RCC_voidEnableClock(RCC_APB2,APB2_GPIOC_EN);
RCC_voidEnableClock(RCC_APB2,APB2_GPIOA_EN);
USART_voidInit(UART1,9600);
GPIO_voidSetPinDirection(GPIOC,PIN13,OUTPUT_SPEED_50MHZ_PP);	
TIMER_voidInit(TIM2);
STK_voidInit();
STK_voidStartMillis();
u32 y=0;	
while(1){
	GPIO_voidTogglePinValue(GPIOC,PIN13);
  //GPIO_voidSetPinValue(GPIOB,PIN11,HIGH);
  y = Millis();
	Delay_In_Ms(TIM2,1000);
	x= Millis() - y ;	
	USART_voidTransmit(UART1,ptr,INT);
	USART_voidTransmit(UART1,"\n",STRING);
  
}
}