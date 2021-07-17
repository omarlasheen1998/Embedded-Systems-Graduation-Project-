#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "RCC_interface.h"

#include "USART_INTERFACE.h"
#include "STK_interface.h"
#include "AFIO_interface.h"
#include "NVIC_interface.h"

#include "ESP8266_interface.h"

void rcc_init(void);
void clear_data(uint8* data_cleared);

int main(void)
{	
	rcc_init();
	
	USART_voidInit(UART3,9600);
	
	USART_voidInit(UART1,115200);
	STK_voidInit();
	
	//ESP8266_voidInit();
	//ESP8266_voidConnectToWiFi("Islam","islam999");
	ESP8266_voidResetESP();
	uint8 data[60] ={0};
	
	while(1)
	{
		
		if (strcmp(data, "DONE UPLOAD") != 0){
		
		do{
			/* add 5 for datalegth because ("GET " + 1 )*/
			clear_data(data);
			ESP8266_voidSendData("162.253.155.226","42","http://iotarm.freevar.com/status.txt",data);
			USART_voidTransmit(UART3,data,STRING);
			//STK_voidDelay_ms(1000);
			if(strcmp(data,"") == 0)
				ESP8266_voidResetESP();
		}while(strcmp(data,"") == 0);
		

		clear_data(data);
		ESP8266_voidSendData("162.253.155.226","50","http://iotarm.freevar.com/test.php?config=ok",data);
		USART_voidTransmit(UART3,data,STRING);
		USART_voidTransmit(UART3,"\n",STRING);
		while(strcmp(data,"") == 0)
		{
			ESP8266_voidResetESP();
			clear_data(data);
			ESP8266_voidSendData("162.253.155.226","52","http://iotarm.freevar.com/test.php?config=none",data);
			USART_voidTransmit(UART3,data,STRING);
			USART_voidTransmit(UART3,"\n",STRING);
		}
		
		//STK_voidDelay_ms(500);
		}
		
		
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
	RCC_voidEnableClock(RCC_APB2,APB2_GPIOC_EN);/*ENABLE PORTC AS IO PINS*/
	
	RCC_voidEnableClock(RCC_APB1,APB1_USART3_EN);/*ENABLE USART3 */
	
	RCC_voidEnableClock(RCC_APB2,APB2_USART1_EN);/*ENABLE USART1 */

	
}

void clear_data(uint8* data_cleared)
{
	u8 LOC_u8Iterator1 = 0 ;

	for( LOC_u8Iterator1 = 0 ; LOC_u8Iterator1 < 60 ; LOC_u8Iterator1++ ){

		data_cleared[ LOC_u8Iterator1 ] = 0 ;

	}
}
