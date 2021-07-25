#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_private.h"
#include "EXTI_interface.h"
#include "RCC_INTERFACE.h"
#include "USART_INTERFACE.h"
#include "NVIC_interface.h"
#include "GPIO_interface.h"
#include "AFIO_interface.h"

#define ENCODER_RESOLUTION 22500UL

s64 count_encoder =0,count_encoder2 =0;
u8 a=0,b=0,c=0,d=0;


void *ptr=&count_encoder;
void *ptr2=&count_encoder2;

void Forward1(void){
	a =GPIO_u8GetPinValue(GPIOA,4);
	b=GPIO_u8GetPinValue(GPIOA,5);
if(a!= b)
{
count_encoder++;
}
else 
{
count_encoder--;
}
}


void Backward1(void){

a =GPIO_u8GetPinValue(GPIOA,4);
b=GPIO_u8GetPinValue(GPIOA,5);
if(a == b)
{
count_encoder++;
}
else
{
count_encoder--;
}
}

void Forward2(void){
	c =GPIO_u8GetPinValue(GPIOB,14);
	d=GPIO_u8GetPinValue(GPIOB,15);
if(c!= d)
{
count_encoder2++;
}
else 
{
count_encoder2--;
}
}


void Backward2(void){

c =GPIO_u8GetPinValue(GPIOB,14);
d=GPIO_u8GetPinValue(GPIOB,15);
if(c == d)
{
count_encoder2++;
}
else
{
count_encoder2--;
}
}


int main(void){
	
RCC_voidInitSysClock();	
RCC_voidEnableClock(RCC_APB2,APB2_AFIO_EN);
RCC_voidEnableClock(RCC_APB1,APB1_USART3_EN);	
RCC_voidEnableClock(RCC_APB2,APB2_GPIOA_EN);
RCC_voidEnableClock(RCC_APB2,APB2_GPIOB_EN);
	
USART_voidInit(UART3,9600);
EXTI_voidInit();

GPIO_voidSetPinDirection(GPIOA,PIN4,INPUT_PULL_UP_DOWN);
GPIO_voidSetPinDirection(GPIOA,PIN5,INPUT_PULL_UP_DOWN);

GPIO_voidSetPinDirection(GPIOB,PIN14,INPUT_PULL_UP_DOWN);
GPIO_voidSetPinDirection(GPIOB,PIN15,INPUT_PULL_UP_DOWN);
	
GPIO_voidSetPinPull(GPIOA,PIN4,PULL_UP);
GPIO_voidSetPinPull(GPIOA,PIN5,PULL_UP);	

GPIO_voidSetPinPull(GPIOB,PIN14,PULL_UP);
GPIO_voidSetPinPull(GPIOB,PIN15,PULL_UP);	
	
EXTI_voidSetCallBack(EXTI_LINE4,Forward1);
EXTI_voidSetCallBack(EXTI_LINE5,Backward1);

EXTI_voidSetCallBack(EXTI_LINE14,Forward2);
EXTI_voidSetCallBack(EXTI_LINE15,Backward2);
	
MAFIO_voidSetEXTIConfiguration(PIN4,GPIOA);
MAFIO_voidSetEXTIConfiguration(PIN5,GPIOA);	

MAFIO_voidSetEXTIConfiguration(PIN14,GPIOB);
MAFIO_voidSetEXTIConfiguration(PIN15,GPIOB);	
	
EXTI_voidSetSignalLatch(EXTI_LINE4,ON_CHANGE);
EXTI_voidSetSignalLatch(EXTI_LINE5,ON_CHANGE);

EXTI_voidSetSignalLatch(EXTI_LINE14,ON_CHANGE);
EXTI_voidSetSignalLatch(EXTI_LINE15,ON_CHANGE);

NVIC_voidEnableInterrupt(40);
NVIC_voidEnableInterrupt(10);
NVIC_voidEnableInterrupt(23);

//NVIC_voidSetPendingFlag(40);

while(1){
	
USART_voidTransmit(UART3,ptr,INT);
USART_voidTransmit(UART3,"	",STRING);
USART_voidTransmit(UART3,ptr2,INT);
USART_voidTransmit(UART3,"\n",STRING);
}

}
