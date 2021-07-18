#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "RCC_interface.h"

#include "USART_INTERFACE.h"
#include "STK_interface.h"
#include "AFIO_interface.h"
#include "NVIC_interface.h"
#include "EXTI_interface.h"

#include "PWM_INTERFACE.h"


void toggle(){

	 

}
int main()
{
	RCC_voidInitSysClock();
	
	RCC_voidEnableClock(RCC_APB2,APB2_AFIO_EN);/*ENABLE AFIO AS IO PINS*/
	
	RCC_voidEnableClock(RCC_APB2,APB2_GPIOA_EN);/*ENABLE PORTA AS IO PINS*/
	RCC_voidEnableClock(RCC_APB2,APB2_GPIOB_EN);/*ENABLE PORTB AS IO PINS*/
	RCC_voidEnableClock(RCC_APB2,APB2_GPIOC_EN);/*ENABLE PORTC AS IO PINS*/
	
	RCC_voidEnableClock(RCC_APB1,APB1_USART3_EN);/*ENABLE USART3 */
  USART_voidInit(UART3,9600);
	GPIO_voidSetPinDirection(GPIOC, PIN13, OUTPUT_SPEED_50MHZ_PP);
	STK_voidInit();
	//STK_voidSetIntervalPeriodic(90000000,toggle);
	STK_voidStartTimer(16000000);
	u32 old_time=0;
	
	while(1)
	{ 
		u32 x= STK_u32GetElapedTime()*1.0/9000; 
		if( x - old_time >= 1000 )
		{
		GPIO_voidTogglePinValue(GPIOC,PIN13);
    old_time = x;
		}
		USART_voidTransmit(UART3,&x,INT);
		USART_voidTransmit(UART3,"\n",STRING);
	}
	
}

