#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "RCC_interface.h"

#include "USART_INTERFACE.h"
#include "STK_interface.h"
#include "AFIO_interface.h"
#include "NVIC_interface.h"
#include "EXTI_interface.h"

void rcc_init  (void);
void Forward_1 (void);
void Forward_2 (void);
void Backward_1(void);
void Backward_2(void);

void CalculateAngle(void);


s64 encoder_counter_1 = 0, encoder_counter_2 = 0;

int main()
{
	rcc_init();
	EXTI_voidInit();
	
	STK_voidInit();
	
	USART_voidInit(UART3,9600);
	
	GPIO_voidSetPinDirection(GPIOA, PIN4, INPUT_PULL_UP_DOWN);
	GPIO_voidSetPinDirection(GPIOA, PIN5, INPUT_PULL_UP_DOWN);
	
	GPIO_voidSetPinPull		(GPIOA, PIN4, PULL_UP);
	GPIO_voidSetPinPull		(GPIOA, PIN5, PULL_UP);
	
	EXTI_voidSetCallBack(EXTI_LINE4,Forward_1);
	EXTI_voidSetCallBack(EXTI_LINE5,Backward_1);
	
	EXTI_voidSetSignalLatch(EXTI_LINE4, ON_CHANGE);
	EXTI_voidSetSignalLatch(EXTI_LINE5, ON_CHANGE);
	
	
	NVIC_voidEnableInterrupt(10);//4
	NVIC_voidEnableInterrupt(23);//5-9
	//NVIC_voidEnableInterrupt(40);//10-15
	
	STK_voidSetIntervalPeriodic(900000,CalculateAngle); /* 900000 = 100 mS*/
	
	while(1)
	{
   //CalculateAngle();		
	}
	
}

void rcc_init(void)
{
	/* first we will operate on the pll mode in rcc with internal clock 8mhz*/
 /* INITIALIZE THE SYSTEM CLOCK TO BE 72 MHZ BY CHOOSING AN EXTERNAL CLOCK 16MHZ AND CHOOSE HSE/2
	AND THE MULTIPLIED NUMBER IN PLL IS 9 TO GET THE 72MHZ */
	RCC_voidInitSysClock();
	
	RCC_voidEnableClock(RCC_APB2,APB2_AFIO_EN);/*ENABLE AFIO AS IO PINS*/
	
	RCC_voidEnableClock(RCC_APB2,APB2_GPIOA_EN);/*ENABLE PORTA AS IO PINS*/
	RCC_voidEnableClock(RCC_APB2,APB2_GPIOB_EN);/*ENABLE PORTB AS IO PINS*/
//	RCC_voidEnableClock(RCC_APB2,APB2_GPIOC_EN);/*ENABLE PORTC AS IO PINS*/
	
	RCC_voidEnableClock(RCC_APB1,APB1_USART3_EN);/*ENABLE USART3 */
	
//	RCC_voidEnableClock(RCC_APB2,APB2_USART1_EN);/*ENABLE USART1 */

	
}


void Forward_1 (void)
{
	u8 a = 0,b = 0;
	a = GPIO_u8GetPinValue(GPIOA,PIN4);
	b = GPIO_u8GetPinValue(GPIOA,PIN5);
	
	if(a != b)
		encoder_counter_1++;
	else
		encoder_counter_1--;
}
void Backward_1(void)
{
	u8 a = 0,b = 0;
	a = GPIO_u8GetPinValue(GPIOA,PIN4);
	b = GPIO_u8GetPinValue(GPIOA,PIN5);
	
	if(a == b)
		encoder_counter_1++;
	else
		encoder_counter_1--;
}
void Forward_2 (void)
{
	u8 a = 0,b = 0;
	a = GPIO_u8GetPinValue(GPIOB,PIN12);
	b = GPIO_u8GetPinValue(GPIOB,PIN13);
	
	if(a != b)
		encoder_counter_2++;
	else
		encoder_counter_2--;
}
void Backward_2(void)
{
	u8 a = 0,b = 0;
	a = GPIO_u8GetPinValue(GPIOB,PIN12);
	b = GPIO_u8GetPinValue(GPIOB,PIN13);
	
	if(a == b)
		encoder_counter_2++;
	else
		encoder_counter_2--;
}

void CalculateAngle(void)
{
	s32 angle = 0;
	
	angle = (((encoder_counter_1)*1.0)/(45000))*360 - 20;

	if(angle > 20)
		angle = 20;
	else if(angle < -20)
		angle = -20;
	
//	USART_voidTransmit(UART3,"ANGLE =  ",STRING);
	USART_voidTransmit(UART3,&angle,INT);
	
	USART_voidTransmit(UART3," \n",STRING);
	
}