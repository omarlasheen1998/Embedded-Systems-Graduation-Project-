/*
	************************* 	I2C Master Send Data	*************************
	1. Generate the START condition

	2. confirm that start generation is completed by checking the SB flag in the SR1
	   Note: Until SB is cleared SCL will be stretched (pulled to LOW)

	3. Send the address of the slave with r/nw bit set to w(0) (total 8 bits )

	4. Confirm that address phase is completed by checking the ADDR flag in teh SR1

	5. clear the ADDR flag according to its software sequence
	  Note: Until ADDR is cleared SCL will be stretched (pulled to LOW)

	6. send the data until len becomes 0

	

	7. when Len becomes zero wait for TXE=1 and BTF=1 before generating the STOP condition
		Note: TXE=1 , BTF=1 , means that both SR and DR are empty and next transmission should begin
	   when BTF=1 SCL will be stretched (pulled to LOW)

	8. Generate STOP condition and master need not to wait for the completion of stop condition.
	   Note: generating STOP, automatically clears the BTF
		 
	 ************************* 	I2C Master recieve Data	*************************
		1. Generate the START condition
		
		2. confirm that start generation is completed by checking the SB flag in the SR1
	   Note: Until SB is cleared SCL will be stretched (pulled to LOW)
		 
		3. Send the address of the slave with r/nw bit set to R(1) (total 8 bits )
	
		4. wait until address phase is completed by checking the ADDR flag in teh SR1
	
		# procedure to read only 1 byte from slave
				Disable Acking
				clear the ADDR flag
				wait until  RXNE becomes 1
				generate STOP condition
				read data in to buffer
		## procedure to read data from slave when Len > 1
				clear the ADDR flag
				read the data until Len becomes zero (in for loop
					wait until RXNE becomes 1
					if last 2 bytes are remaining
							Disable Acking
							generate STOP condition
					read the data from data register in to buffer
					increment the buffer address
					
		### re-enable ACKing
				
		 
*/


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "RCC_interface.h"

#include "USART_INTERFACE.h"
#include "STK_interface.h"
#include "AFIO_interface.h"
#include "NVIC_interface.h"

#include "I2C_interface.h"

#define MASTER_EN 

#define SLAVE_ADDRESS  0x40 
#define MASTER_ADDRESS 0x30 

#define clockspped 400000

 
 
 u8 receive_data[20];

void rcc_init(void);

int main(void)
{	
	rcc_init();
	
	USART_voidInit(UART3,9600);
	
	GPIO_voidSetPinDirection(GPIOC,13,OUTPUT_SPEED_50MHZ_PP);
	
#ifdef	 MASTER_EN
	u8 send_data []= "LASHEEN";
	I2C_init(MI2C1,clockspped,MASTER_ADDRESS);
#else
	u8 send_data[20] ="AHMED ADEL#";
	I2C_init(MI2C1,clockspped,SLAVE_ADDRESS);
#endif
	
	GPIO_voidSetPinValue(GPIOC,13,LOW);
	
	while(1)
	{	
		
#ifdef	 MASTER_EN
		I2C_master_rx(MI2C1,SLAVE_ADDRESS,receive_data,11);
		STK_voidDelay_ms(100);
		I2C_master_tx(MI2C1,SLAVE_ADDRESS,send_data,7);
		I2C_generate_stop_condition(MI2C1);
		
		
	#if 1
		USART_voidTransmit(UART3,"master send: ",STRING);
		USART_voidTransmit(UART3,send_data,STRING);
		USART_voidTransmit(UART3,"\n",STRING);
	#endif
		
	#if 1	
		USART_voidTransmit(UART3,"Master receive: ",STRING);
		USART_voidTransmit(UART3,receive_data,STRING);
		USART_voidTransmit(UART3,"\n",STRING);
	#endif

#else
		
		I2C_slave_tx(MI2C1,send_data,11);
		I2C_slave_rx(MI2C1,receive_data,7);
		//STK_voidDelay_ms(1000);
		I2C_slave_Check_StopBit(MI2C1);
		
		
#if 1
		USART_voidTransmit(UART3,"slave receive: ",STRING);
		USART_voidTransmit(UART3,receive_data,STRING);
		USART_voidTransmit(UART3,"\n",STRING);
#endif

#if 1
		USART_voidTransmit(UART3,"slave send: ",STRING);
		USART_voidTransmit(UART3,send_data,STRING);
		USART_voidTransmit(UART3,"\n",STRING);
#endif
		
#endif
		
		STK_voidDelay_ms(1000);
		GPIO_voidSetPinValue(GPIOC,13,HIGH);
		STK_voidDelay_ms(1000);
		GPIO_voidSetPinValue(GPIOC,13,LOW);
		
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
	
	RCC_voidEnableClock(RCC_APB1,APB1_I2C1_EN);/*ENABLE I2C1 */
}
