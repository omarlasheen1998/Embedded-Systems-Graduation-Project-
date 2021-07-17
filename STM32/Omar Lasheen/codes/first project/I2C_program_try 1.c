#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "I2C_private.h"
#include "I2C_config.h"
#include "I2C_interface.h"
#include "GPIO_interface.h"
#include "NVIC_interface.h"
#include "DMA_INTERFACE.h"
#include "DMA_REG.h"

void (*I2C1_CallBack) (void);
void (*I2C2_CallBack) (void);
u8 configure_I2C1,configure_I2C2;


void I2C_Master_init(u8 I2C_TYPE,u32 I2C_CLOCK)
{
if(I2C_TYPE == MI2C1)
{
  configure_I2C1 = I2C_MASTER;
	GPIO_voidSetPinDirection(GPIOB,PIN6,OUTPUT_SPEED_50MHZ_AFOD); /* configure PB6 and PB7 as alt. func. open drain */
	GPIO_voidSetPinDirection(GPIOB,PIN7,OUTPUT_SPEED_50MHZ_AFOD); /* configure PB6 and PB7 as alt. func. open drain */
	//GPIO_voidSetPinPull(GPIOB,PIN6,PULL_UP);
	//GPIO_voidSetPinPull(GPIOB,PIN7,PULL_UP);
	
	I2C1->CR1|= 1<<15;
	I2C1->CR1&= ~(1<<15);
	I2C1->CR2 |= 36; //clock of I2C1 peripheral is 36
	#if I2C1_MODE == STD_MODE
	I2C1->CCR |= (u8)((1.0/(2.0 * I2C_CLOCK))/(1.0/36000000));//refer to the datasheet for the fSCL equation
	I2C1->TRISE = 37; //max rise time =1000ns, trise=1000/1/36mhz +1
	
	#elif I2C1_MODE == FAST_MODE
	SET_BIT(I2C1->CCR,SM_FM_BIT);
	CLR_BIT(I2C1->CCR,FM_DUTY_BIT); 
	I2C1->CCR |= (u8)((1.0/(3.0 * I2C_CLOCK))/(1.0/36000000)); //refer to the datasheet for the fSCL equation
	I2C1->TRISE = 11; //max rise time =300ns, trise=300/1/36mhz +1
	#endif
	
	I2C1->CR1 = 1;	/* PE = 1 */
	I2C1->CR1 |= 1<<10; //ack enabled on receiving bytes
}

else if(I2C_TYPE == MI2C2)
{	
	configure_I2C2 = I2C_MASTER;
	GPIO_voidSetPinDirection(GPIOB,PIN10,OUTPUT_SPEED_50MHZ_AFOD); /* configure PB10 and PB11 as alt. func. open drain */
	GPIO_voidSetPinDirection(GPIOB,PIN11,OUTPUT_SPEED_50MHZ_AFOD); /* configure PB10 and PB11 as alt. func. open drain */
	GPIO_voidSetPinPull(GPIOB,PIN10,PULL_UP);
	GPIO_voidSetPinPull(GPIOB,PIN11,PULL_UP);
		
	I2C2->CR1|= 1<<15;
	I2C2->CR1&= ~(1<<15);
	I2C2->CR2 |= 36; //clock of I2C2 peripheral is 36
	#if I2C2_MODE == STD_MODE
	I2C2->CCR |= (u8)((1.0/(2.0 * I2C_CLOCK))/(1.0/36000000));//refer to the datasheet for the fSCL equation
  I2C2->TRISE = 37;
	
	#elif I2C2_MODE == FAST_MODE
	SET_BIT(I2C2->CCR,SM_FM_BIT);
	CLR_BIT(I2C2->CCR,FM_DUTY_BIT); 
	I2C2->CCR |= (u8)((1.0/(3.0 * I2C_CLOCK))/(1.0/36000000)); //refer to the datasheet for the fSCL equation
	I2C2->TRISE = 11;
	
	#endif
	
	I2C2->CR1 = 1;	/* PE = 1 */
	I2C2->CR1 |= 1<<10; //ack enabled on receiving bytes
}

}

void I2C_Slave_init(u8 I2C_TYPE,u32 I2C_CLOCK, u16 ownaddress){

	if(I2C_TYPE == MI2C1)
	{	
		configure_I2C1 = I2C_SLAVE;
    I2C2->CR1 = 0;	/* PE = 0 */
    I2C2->CR2 = 0;
   // configure i2c pins
	GPIO_voidSetPinDirection(GPIOB,PIN6,OUTPUT_SPEED_50MHZ_AFOD); /* configure PB6 and PB7 as alt. func. open drain */
	GPIO_voidSetPinDirection(GPIOB,PIN7,OUTPUT_SPEED_50MHZ_AFOD); /* configure PB6 and PB7 as alt. func. open drain */
	//GPIO_voidSetPinPull(GPIOB,PIN6,PULL_UP);
	//GPIO_voidSetPinPull(GPIOB,PIN7,PULL_UP);
	
	I2C1->CR1|= 1<<15;
	I2C1->CR1&= ~(1<<15);
	I2C1->CR2 |= 36; //clock of APB1 is 36
	#if I2C1_MODE == STD_MODE
	I2C1->CCR |= (u8)((1.0/(2.0 * I2C_CLOCK))/(1.0/36000000));//refer to the datasheet for the fSCL equation
	I2C1->TRISE = 37;
	
	#elif I2C1_MODE == FAST_MODE
	SET_BIT(I2C1->CCR,SM_FM_BIT);
	CLR_BIT(I2C1->CCR,FM_DUTY_BIT); 
	I2C1->CCR |= (u8)((1.0/(3.0 * I2C_CLOCK))/(1.0/36000000)); //refer to the datasheet for the fSCL equation
	I2C1->TRISE = 11;
	#endif
	
	  #if I2C1_ADDRESSING == ADDRESS_7BITS
	 I2C1->OAR1 = ownaddress<<1;
		#elif I2C1_ADDRESSING == ADDRESS_10BITS
	 I2C1->OAR1 = ownaddress;
		#endif
	 
   // slave needs to acknowledge on receiving bytes
   // set it after enabling Peripheral i.e. PE = 1
    I2C1->CR1 = 1;	/* PE = 1 */
	  I2C1->CR1 |= 1<<6; //ENGC=1
		I2C1->CR1 |= 1<<10; //ack enabled on receiving bytes
 }

	else if(I2C_TYPE == MI2C2)
	{	
		configure_I2C2 = I2C_SLAVE;

    I2C2->CR1 = 0;	/* PE = 0 */
    I2C2->CR2 = 0;
   // configure i2c pins
	GPIO_voidSetPinDirection(GPIOB,PIN10,OUTPUT_SPEED_50MHZ_AFOD); /* configure PB10 and PB11 as alt. func. open drain */
	GPIO_voidSetPinDirection(GPIOB,PIN11,OUTPUT_SPEED_50MHZ_AFOD); /* configure PB10 and PB11 as alt. func. open drain */
	GPIO_voidSetPinPull(GPIOB,PIN10,PULL_UP);
	GPIO_voidSetPinPull(GPIOB,PIN11,PULL_UP);
	
	I2C2->CR1|= 1<<15;
	I2C2->CR1&= ~(1<<15);
	I2C2->CR2 |= 36; //clock of APB1 is 36
	#if I2C2_MODE == STD_MODE
	I2C2->CCR |= (u8)((1.0/(2.0 * I2C_CLOCK))/(1.0/36000000));//refer to the datasheet for the fSCL equation
	I2C2->TRISE = 37;
	
	#elif I2C2_MODE == FAST_MODE
	SET_BIT(I2C2->CCR,SM_FM_BIT);
	CLR_BIT(I2C2->CCR,FM_DUTY_BIT); 
	I2C2->CCR |= (u8)((1.0/(3.0 * I2C_CLOCK))/(1.0/36000000)); //refer to the datasheet for the fSCL equation
	I2C2->TRISE = 11;
	
	#endif
	
	  #if I2C2_ADDRESSING == ADDRESS_7BITS
	 I2C2->OAR1 = ownaddress<<1;
		#elif I2C2_ADDRESSING == ADDRESS_10BITS
	 I2C2->OAR1 = ownaddress;
		#endif
	 
   // slave needs to acknowledge on receiving bytes
   // set it after enabling Peripheral i.e. PE = 1
    I2C2->CR1 = 1;	/* PE = 1 */
	  I2C2->CR1 |= 1<<6;	/* ENGC = 1 */
		I2C2->CR1 |= 1<<10; //ack enabled
  }

}
void I2C_waitForReady(u8 I2C_TYPE)
{
 if(I2C_TYPE == MI2C1)
	while((I2C1->SR2&(1<<1)) != 0); /* check bus busy */

 else if(I2C_TYPE == MI2C2)
	while((I2C2->SR2&(1<<1)) != 0); /* check bus busy */

}

void I2C_sendStart(u8 I2C_TYPE)
{
	if(I2C_TYPE == MI2C1)
	{
	I2C1->CR1 |= (1<<8); /* start */
	while((I2C1->SR1&(1<<0)) == 0); /* wait for SB */
	int stat = I2C1->SR2;
	}
	
	else if(I2C_TYPE == MI2C2)
	{
	I2C2->CR1 |= (1<<8); /* start */
	while((I2C2->SR1&(1<<0)) == 0); /* wait for SB */
	int stat = I2C2->SR2;
	}
	
}

void I2C_sendStop(u8 I2C_TYPE)
{
	if(I2C_TYPE == MI2C1)
	{
		//if ((I2C1->SR1&(1<<2))|| (I2C1->SR1&(1<<7))) //BTF | TXE
		//{
			I2C1->CR1 |= (1<<9); /* stop */
		//}
	while((I2C1->SR2&(1<<0)) != 0); /* wait for becoming slave */
		I2C1->CR1 |= (1<<10); //enable acks
	}

  else if(I2C_TYPE == MI2C2)
	{
	I2C2->CR1 |= (1<<9); /* stop */
	while((I2C2->SR2&(1<<0)) != 0); /* wait for becoming slave */
	}
	//I2C1->CR1 |= (1<<10); //enable acks

}

u8 I2C_sendAddr(u8 I2C_TYPE,u8 addr)
{

if(I2C_TYPE == MI2C1)
{
	I2C1->DR = addr;
	int stat;
	do{
		stat = I2C1->SR1;
		if((stat&(1<<9)) != 0) /* arbitration lost */
			return 1;
		
		if((stat&(1<<1)) != 0) /* address sent */
		{
			stat = I2C1->SR2; /* read SR2 to clear ADDR flag */
			return 0;
		}
	}	while(1);
}

else if(I2C_TYPE == MI2C2)
{
	I2C2->DR = addr;
	int stat;
	do{
		stat = I2C2->SR1;
		if((stat&(1<<9)) != 0) /* arbitration lost */
			return 1;
		
		if((stat&(1<<1)) != 0) /* address sent */
		{
			stat = I2C2->SR2; /* read SR2 to clear ADDR flag */
			return 0;
		}
	}	while(1);
}

}

u8 I2C_sendAddrForRead(u8 I2C_TYPE,u8 addr)
{
	return I2C_sendAddr(I2C_TYPE,(addr<<1) | 0x1); /* addr+Read(1) */
}

u8 I2C_sendAddrForWrite(u8 I2C_TYPE,u8 addr)
{
	return I2C_sendAddr(I2C_TYPE,(addr<<1)); /* addr+Write(0) */
}

void I2C_MasterSendData(u8 I2C_TYPE,u8 address,u8* data,u8 len)
{
	if(I2C_TYPE == MI2C1)
	{
	I2C_sendStart(MI2C1);
	I2C_sendAddrForWrite(MI2C1,address);	
			
		do{
		if((I2C1->SR2 & 1<<0) && ((I2C1->SR2 & 1<<2) != 0)) //MSL & TRA
			break;
		}while(1);
			
	for(u8 i=0;i<len;i++)
	{
		I2C1->DR = data[i];
	do{
		
		if((I2C1->SR1 &(1<<7)) != 0) /* TxE = 1 */
			break;
	}	while(1);
  
	}
  
	}
	else if(I2C_TYPE == MI2C2)
	{I2C_sendStart(MI2C2);
	I2C_sendAddrForWrite(MI2C2,address);	
	
				do{
		if((I2C2->SR2 & 1<<0) && ((I2C2->SR2 & 1<<2) != 0))
			break;
		}while(1);
			
	for(u8 i=0;i<len;i++)
	{
		I2C2->DR = data[i];
	do{
		
		if((I2C2->SR1 &(1<<7)) != 0) /* TxE = 1 */
			break;
	}	while(1);
  }
  }
}

void I2C_MasterReadData(u8 I2C_TYPE,u8 address,u32* buff, u8 len,u8 checkStop)
{
	
	if(I2C_TYPE == MI2C1)
	{
		I2C1->CR2|= 1<<11; //DMAEN 
		
	  //I2C1->CR1 &= ~(1<<10); //disable acks
		I2C1->CR1 |= (1<<10); //enable acks
		
		MDMA1_VidSetAddress( CHANNEL7 , &( I2C1 -> DR ) , &( buff ) , len );
		MDMA1_VidDMAEnable( CHANNEL7 );
		
		I2C_sendStart(MI2C1);
		
		I2C_sendAddrForRead(MI2C1,address);
		
		
		
		do{
		if((I2C1->SR2 & 1<<0) && ((I2C1->SR2 & 1<<2) == 0)) // SB & BTF
			break;
		}while(1);
		#if 0
		if (len == 1 )
		{
			
		}
		u8 len_r = len;
		if (len > 1)
		{
			
			if (len > 2)
			{
				MDMA1_VidSetAddress( CHANNEL7 , &( I2C1 -> DR ) , &( buff) , len-2 );
				MDMA1_VidDMAEnable( CHANNEL7 );
				
				while( MDMA1_u8GetFlag( CHANNEL7 , DMA_TCIF ) == 0 );
				MDMA1_VidClearFlag    ( CHANNEL7 , DMA_TCIF );
				
				I2C1->CR1 &= ~(1<<10); //disable acks
				I2C_sendStop(MI2C1);
				
				MDMA1_VidSetAddress( CHANNEL7 , &( I2C1 -> DR ) , (&( buff)+len-2) , 2 );
				MDMA1_VidDMAEnable( CHANNEL7 );
				
				while( MDMA1_u8GetFlag( CHANNEL7 , DMA_TCIF ) == 0 );
				MDMA1_VidClearFlag    ( CHANNEL7 , DMA_TCIF );
				
				

				
			}
			
			if (len == 2)
			{
				MDMA1_VidSetAddress( CHANNEL7 , &( I2C1 -> DR ) , &( buff) , len );
				MDMA1_VidDMAEnable( CHANNEL7 );
				
				I2C1->CR1 &= ~(1<<10); //disable acks
				I2C_sendStop(MI2C1);
			}
				\
				
			
		}
		#endif
		//I2C1->CR1 &= ~(1<<10); //disable acks
		
		//I2C_sendStop(MI2C1);
		while(GET_BIT(I2C1->CR2,12)== 0);
		I2C1->CR1 &= ~(1<<10); //disable acks
		//generate STOP condition
		if(checkStop == 1)
			I2C_sendStop(MI2C1);

		while( MDMA1_u8GetFlag( CHANNEL7 , DMA_TCIF ) == 0 );
		MDMA1_VidClearFlag    ( CHANNEL7 , DMA_TCIF );
		
	/*	
		do{
	
		if((I2C1->SR1 &(1<<6)) != 0) // RxNE = 1 
			break;
	}	while(1);
		*/	
		
		//while((MDMA1->ISR & 1<<25) == 0); //waiting for transfer to be completed
	
	//while((I2C1->SR1&(1<<6)) == 0);  //waiting for RxNE 
	//buff[0]= I2C1->DR;
		//I2C1->CR1 |= (1<<10); //enable acks

	}
	
	else if(I2C_TYPE == MI2C2)
	{
				I2C2->CR2|= 1<<11; //DMAEN 
	  I2C2->CR1 |= 1<<10; //enable acks
	  MDMA1->CHANNEL[4].CMAR = (u32)(buff);
		MDMA1->CHANNEL[4].CPAR = (u32)(&I2C1->DR);
		MDMA1->CHANNEL[4].CNDTR = len;
		MDMA1->CHANNEL[4].CNDTR = len;
		MDMA1->CHANNEL[4].CCR |= (1<<0)|(1<<1)|(1<<7); //EN,TCIE,MINC
		I2C_sendStart(MI2C2);
		I2C_sendAddrForRead(MI2C2,address);
				
		do{
		if((I2C2->SR2 & 1<<0) && ((I2C2->SR2 & 1<<2) == 0))
			break;
		}while(1);
			
		while((MDMA1->ISR & 1<<17) == 0); //waiting for transfer to be completed
		
  }
	
}

void I2C_SlaveSendData(u8 I2C_TYPE,u8* data,u8 len,u8 checkStop)
{
	if(I2C_TYPE == MI2C1)
	{
		
	do{
		if(I2C_SlaveListen(MI2C1) == I2C_EVENT_SLAVE_ADDRESS_MATCHED)
			if(I2C_SlaveListen(MI2C1) == I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED)
			break;
	}while(1);
	
	for(u8 i=0;i<len;i++)
	{
		I2C1->DR = data[i];
	do{
		
		if((I2C1->SR1 &(1<<7)) != 0) /* TxE = 1 */
			break;
	}	while(1);
  
	}
	if (checkStop==1)
			if ((I2C1->SR1 & (1<<10)))
				CLR_BIT(I2C1->SR1,10); //clear AF bit
				
			
		
	}
	else if(I2C_TYPE == MI2C2)
	{
	
		do{
		if(I2C_SlaveListen(MI2C2) == I2C_EVENT_SLAVE_ADDRESS_MATCHED)
			if(I2C_SlaveListen(MI2C2) == I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED)
			break;
	}while(1);
	
	for(u8 i=0;i<len;i++)
	{
		I2C2->DR = data[i];
	do{
		
		if((I2C2->SR1 &(1<<7)) != 0) /* TxE = 1 */
			break;
	}	while(1);
  }
  }
}

void I2C_SlaveReadData(u8 I2C_TYPE,u32* buff, u8 len,u8 checkStop)
{
	
	if(I2C_TYPE == MI2C1)
	{
		
		I2C1->CR2|= 1<<11; //DMAEN 
	  I2C1->CR1 |= 1<<10; //enable acks
		
		
		do{
		if((I2C_SlaveListen(MI2C1) == I2C_EVENT_SLAVE_ADDRESS_MATCHED )|| (I2C_SlaveListen(MI2C1) == I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED ))
			if(I2C_SlaveListen(MI2C1) == I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED)
				break;
	}while(1);
		
		
	#if 1	
	if(checkStop==1)
	{
		do{
			if(I2C_SlaveListen(MI2C1) == I2C_EVENT_SLAVE_STOP_DETECTED)
				break;
		}while(1);
	}
	#endif
		while( MDMA1_u8GetFlag( CHANNEL7 , DMA_TCIF ) == 0 ); //waiting for transfer to be completed
		MDMA1_VidClearFlag    ( CHANNEL7 , DMA_TCIF );

	
	/*
	while((I2C1->SR1&(1<<6)) == 0);  //waiting for RxNE 
	buff[0] = I2C1->DR;
*/
	}
	
	else if(I2C_TYPE == MI2C2)
	{
				I2C2->CR2|= 1<<11; //DMAEN 
	  I2C2->CR1 |= 1<<10; //enable acks
	  MDMA1->CHANNEL[4].CMAR = (u32)(buff);
		MDMA1->CHANNEL[4].CPAR = (u32)(&I2C1->DR);
		MDMA1->CHANNEL[4].CNDTR = len;
		MDMA1->CHANNEL[4].CNDTR = len;
		MDMA1->CHANNEL[4].CCR |= (1<<0)|(1<<1)|(1<<7); //EN,TCIE,MINC
		
				do{
		if(I2C_SlaveListen(MI2C2) == I2C_EVENT_SLAVE_ADDRESS_MATCHED)
			if(I2C_SlaveListen(MI2C2) == I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED)
			break;
	}while(1);
				
		while((MDMA1->ISR & 1<<17) == 0); //waiting for transfer to be completed
		
  }
	
}
u8 I2C_SlaveListen(u8 I2C_TYPE)
{
	if(I2C_TYPE == MI2C1)
	{	
	int stat;
	
if(I2C1->SR1 & 1<<1)
{
	stat = I2C1->SR2; /* read SR2 to clear ADDR flag */
	return I2C_EVENT_SLAVE_ADDRESS_MATCHED;
}

else if(I2C1->SR1 & 1<<4)
{
  CLR_BIT(I2C1->CR1,9);  /* write CR1 to clear STOPF flag */	
  return I2C_EVENT_SLAVE_STOP_DETECTED;
}

else if(I2C1->SR2 & 1<<4)
{
 return I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED;	
}

else if((I2C1->SR2 & 1<<2) != 0)
{
 return I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED;	
}

else if((I2C1->SR2 & 1<<2) == 0)
{
 return I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED;	
}
	}

else if(I2C_TYPE == MI2C2)
	{	
	int stat;
	
if(I2C2->SR1 & 1<<1)
{
	stat = I2C2->SR2; /* read SR2 to clear ADDR flag */
	return I2C_EVENT_SLAVE_ADDRESS_MATCHED;
}

else if(I2C2->SR1 & 1<<4)
{
  I2C2->CR1|= 0x10;  /* write CR1 to clear STOPF flag */	
  return I2C_EVENT_SLAVE_STOP_DETECTED;
}

else if(I2C2->SR2 & 1<<4)
{
 return I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED;	
}

else if((I2C2->SR2 & 1<<2) != 0)
{
 return I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED;	
}

else if((I2C2->SR2 & 1<<2) == 0)
{
 return I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED;	
}

}
 
return 0;
}
void I2C_voidLoadData(u8 I2C_TYPE,u8 data){
	if(I2C_TYPE == MI2C1)
	I2C1->DR = data;
	
	else
	I2C2->DR = data;
}
u8 I2C_u8ReturnData(u8 I2C_TYPE)
{
	if(I2C_TYPE == MI2C1)
	return I2C1->DR;
	else if(I2C_TYPE == MI2C2)
	return I2C2->DR;
}

void I2C_voidInterruptInit(u8 I2C_TYPE)
{

if(I2C_TYPE == MI2C1)
{

SET_BIT( I2C1 -> CR2 , 10 ); //I2C1_TXE_INT_ENABLE 
SET_BIT( I2C1 -> CR2 , 9 ); //I2C1_RXNE_INT_ENABLE

//set I2C1 Event Interrupt
NVIC_voidEnableInterrupt(31);
}

else if(I2C_TYPE == MI2C2)
{

SET_BIT( I2C2 -> CR2 , 10 ); //I2C2_TXE_INT_ENABLE 
SET_BIT( I2C2 -> CR2 , 9 ); //I2C2_RXNE_INT_ENABLE

//set I2C2 Event Interrupt
NVIC_voidEnableInterrupt(33);
	
}

}
void I2C1_voidSetCallBack( void (*ptr) (void) ){

	I2C1_CallBack = ptr;

}


void I2C2_voidSetCallBack( void (*ptr) (void) ){

	I2C2_CallBack = ptr;

}

__weak void I2C1_IRQHandler(void){

	I2C1_CallBack();

}

__weak void I2C2_IRQHandler(void){

	I2C2_CallBack();

}





void I2C_MasterReadDataNoDMA(u8 I2C_TYPE,u8 address,u32* buff, u8 len,u8 checkStop)
{
	
	if(I2C_TYPE == MI2C1)
	{
		
		I2C_sendStart(MI2C1);
		
		I2C_sendAddrForRead(MI2C1,address);
		
		
		if (len == 1 )
		{
			I2C1->CR1 &= ~(1<<10); //disable acks
			while(GET_BIT(I2C1->SR1,6) ==0); // WAIT  RxNE = 1 
			if(checkStop == 1)
				I2C_sendStop(MI2C1);
			*buff = I2C1->DR;
		}
		
		if (len > 1)
		{	
			
		//read the data until Len becomes zero
		for ( u8 i = len ; i > 0 ; i--)
		{
			//wait until RXNE becomes 1
			while(GET_BIT(I2C1->SR1,6) ==0); // WAIT  RxNE = 1 

			if(i == 2) //if last 2 bytes are remaining
			{
				//Disable Acking
				I2C1->CR1 &= ~(1<<10); //disable acks

				//generate STOP condition
				if(checkStop == 1)
					I2C_sendStop(MI2C1);

			}

			//read the data from data register in to buffer
			*buff = I2C1->DR;

			//increment the buffer address
			buff++;

		}
		}
		

		I2C1->CR1 |= (1<<10); //enable acks

	}
}