#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include <stdio.h>
#include "GPIO_interface.h"
#include "RCC_interface.h"

#include "USART_INTERFACE.h"
#include "STK_interface.h"
#include "AFIO_interface.h"
#include "NVIC_interface.h"
#include "EXTI_interface.h"
#include "CAN_interface.h"
#include "PWM_INTERFACE.h"
#include <string.h>

void rcc_init  (void);
void Forward_1 (void);
void Backward_1(void);

u8 Rec_DATA[5];

void CAN_TX(void)
{
	CAN_TxHeaderTypeDef tx_header;
	tx_header.StdId = 0x002;
	tx_header.IDE = CAN_ID_STD;
	tx_header.RTR = CAN_RTR_DATA;
	tx_header.DLC = 8;
	tx_header.TransmitGlobalTime=DISABLE;
	u8 DATA[8] = {'h','e','l','l','o','0','0','\0'};

	CAN_TxHeaderTypeDef tx_header1;
	tx_header1.StdId = 0x003;
	tx_header1.IDE = CAN_ID_STD;
	tx_header1.RTR = CAN_RTR_DATA;
	tx_header1.DLC = 8;
	u8 DATA1[] = {'O','M','A','R','\0'};

	CAN_voidAddTxMsg(&tx_header,DATA);
	CAN_voidAddTxMsg(&tx_header1,DATA1);
	USART_voidTransmit(UART3,"i'm master\n",STRING);
}
void CAN_RX(void)
{
	CAN_RxHeaderTypeDef Rx_header;
	while(CAN_voidRXPending(CAN_RX_FIFO0) == 0);
	
	CAN_voidGetRxMsg(CAN_RX_FIFO0,&Rx_header,Rec_DATA);
	USART_voidTransmit(UART3,Rec_DATA,STRING);
	USART_voidTransmit(UART3,"\n",STRING);
}
u16 Std_id_High(u16 local_u16Std_Id)
{
	return (local_u16Std_Id << 5);
}
void CAN_FilterConfig(void)
{
	CAN_FilterTypeDef CAN_FilterInit;
	CAN_FilterInit.FilterActivation = ENABLE;
	CAN_FilterInit.FilterBank = 0;
	CAN_FilterInit.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	CAN_FilterInit.FilterIdHigh = Std_id_High(0x002);
	CAN_FilterInit.FilterIdLow = 0x0000;
	CAN_FilterInit.FilterMaskIdHigh = 0x0000;
	CAN_FilterInit.FilterMaskIdLow = 0x0000;
	CAN_FilterInit.FilterMode = CAN_FILTERMODE_IDMASK;
	CAN_FilterInit.FilterScale = CAN_FILTERSCALE_32BIT;

	CAN_voidConfigFilter(&CAN_FilterInit);
}

void CAN_Interrupt(void)
{
	CAN_voidInitInterput(CAN_TX_IRQn);
	CAN_voidInitInterput(CAN_RX0_IRQn);
	CAN_voidInitInterput(CAN_RX1_IRQn);
	CAN_voidInitInterput(CAN_SCE_IRQn);

	CAN_voidEnableInterrupt(CAN_IER_TX_MAILBOX_EMPTY | CAN_IER_RX_FIFO0_MSG_PENDING | CAN_IER_ERROR | CAN_IER_LAST_ERROR_CODE | CAN_IER_BUSOFF);
}

void CAN_TxMailbox0CompleteCallback()
{
	/* print MSG on UART1 */
	char MSG[50] = " MSG TRANSMITED m0 \n";
	USART_voidTransmit(UART3,MSG,STRING);
	//NVIC_voidSetPendingFlag(CAN_TX_IRQn);
}
void CAN_RxFifo0MsgPendingCallback()
{
	CAN_RX();
	//NVIC_voidSetPendingFlag(CAN_RX0_IRQn);
}
void CAN_ErrorCallback()
{
	/* print MSG on UART1 */
	char MSG[50] = "Error Code \n";
	u32 x= CAN_voidGetErrorCode();
	USART_voidTransmit(UART3,&x,INT);
	USART_voidTransmit(UART3,"\n",STRING);
}

s32 calculate_setpoint(u32);

s64 encoder_counter_1 = 0, encoder_counter_2 = 0;

int main()
{
	rcc_init();
	EXTI_voidInit();
	
	STK_voidInit();
	
	USART_voidInit(UART1,500000);
	

	GPIO_voidSetPinDirection(GPIOA, PIN4, INPUT_PULL_UP_DOWN);
	GPIO_voidSetPinDirection(GPIOA, PIN5, INPUT_PULL_UP_DOWN);
	
	GPIO_voidSetPinPull	(GPIOA, PIN4, PULL_UP);
	GPIO_voidSetPinPull	(GPIOA, PIN5, PULL_UP);
	
	
	EXTI_voidSetCallBack(EXTI_LINE4,Forward_1);
	EXTI_voidSetCallBack(EXTI_LINE5,Backward_1);
	
	EXTI_voidSetSignalLatch(EXTI_LINE4, ON_CHANGE);
	EXTI_voidSetSignalLatch(EXTI_LINE5, ON_CHANGE);
	
	
	NVIC_voidEnableInterrupt(10);//4
	NVIC_voidEnableInterrupt(23);//5-9
	
	GPIO_voidSetPinDirection(GPIOA, PIN1, OUTPUT_SPEED_50MHZ_PP);
	PWM_voidSetPinDirection(TIM2,CH1);
  
	GPIO_voidSetPinDirection(GPIOA, PIN3, OUTPUT_SPEED_50MHZ_PP);
	PWM_voidSetPinDirection(TIM2,CH3);
  
	/* CAN init */
	CAN_voidInit();
	/* CAN Filter set */
	CAN_FilterConfig();
	CAN_Interrupt();
	/* CAN Start */
	CAN_voidStart();

while(1)
	{
		GPIO_voidSetPinValue(GPIOA, PIN3,HIGH);
		GPIO_voidSetPinValue(GPIOA, PIN1,HIGH);
		
	//	CAN_RX();
		
    if(!strcmp((char*)Rec_DATA,"F"))    
		{ PWM_voidWrite(TIM2,CH3,20000);
		  PWM_voidWrite(TIM2,CH1,20000);}
		
		else if(!strcmp((char*)Rec_DATA,"T"))   
			{PWM_voidWrite(TIM2,CH3,0);
		  PWM_voidWrite(TIM2,CH1,0);}
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
	RCC_voidEnableClock(RCC_APB1,APB1_TIM2_EN);/*ENABLE PORTC AS IO PINS*/
	RCC_voidEnableClock(RCC_APB1,APB1_USART3_EN);/*ENABLE USART3 */
	
  RCC_voidEnableClock(RCC_APB2,APB2_USART1_EN);/*ENABLE USART1 */

	
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

