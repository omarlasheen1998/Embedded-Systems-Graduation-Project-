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
		///GPIO_voidSetPinPull(GPIOB,PIN7,PULL_UP);
		
		
		SET_BIT(I2C1->CR1,15);// SWRST: Software reset
		CLR_BIT(I2C1->CR1,15);// SWRST: Software reset
		
		I2C1->CR2 |= 36; //clock of I2C1 peripheral is 36
		
#if I2C1_MODE == STD_MODE
		//I2C1->CCR |= (u8)((1.0/(2.0 * I2C_CLOCK))/(1.0/36000000));//refer to the datasheet for the fSCL equation
		I2C1->CCR |= (u8)( ( 36 * 1000000) / (I2C_CLOCK << 1));
		I2C1->TRISE = 37; //max rise time =1000ns, trise=1000/1/36mhz +1
		
#elif I2C1_MODE == FAST_MODE
		
		SET_BIT(I2C1->CCR,SM_FM_BIT);
		CLR_BIT(I2C1->CCR,FM_DUTY_BIT);// Fm mode duty cycle 9:16
		u8 duty_cycle = I2C_FM_DUTY_2; 
		
		//I2C1->CCR |= (u8)((1.0/(3.0 * I2C_CLOCK))/(1.0/36000000)); //refer to the datasheet for the fSCL equation
		if(duty_cycle == I2C_FM_DUTY_2)
		{
		 I2C1->CCR = ( 36 * 1000000)/(3 * I2C_CLOCK);
		 
		}else if(duty_cycle == I2C_FM_DUTY_16BY9)
		{ /* this is to reach 400khz in fm mode */
			I2C1->CCR = ( 36 * 1000000)/(25 * I2C_CLOCK);
		}
		I2C1->TRISE = 11; //max rise time =300ns, trise=300/1/36mhz +1
#endif
		
		I2C1->CR1 = 1;	/* PE = 1 */
		CLR_BIT(I2C1->CR1,7); //NOSTRETCH 
		SET_BIT(I2C1->CR1,10); //ack enabled on receiving bytes
	}
#if 0
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
#endif
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
	
	SET_BIT(I2C1->CR1,15); // Software reset
	CLR_BIT(I2C1->CR1,15);
	I2C1->CR2 |= 36; //clock of APB1 is 36
	#if I2C1_MODE == STD_MODE
	//I2C1->CCR |= (u8)((1.0/(2.0 * I2C_CLOCK))/(1.0/36000000));//refer to the datasheet for the fSCL equation
	I2C1->CCR |= (u8)( ( 36 * 1000000) / (I2C_CLOCK << 1));
	I2C1->TRISE = 37;
	
	#elif I2C1_MODE == FAST_MODE
	SET_BIT(I2C1->CCR,SM_FM_BIT);
	CLR_BIT(I2C1->CCR,FM_DUTY_BIT);// Fm mode duty cycle 9:16
	u8 duty_cycle = I2C_FM_DUTY_2;
	//I2C1->CCR |= (u8)((1.0/(3.0 * I2C_CLOCK))/(1.0/36000000)); //refer to the datasheet for the fSCL equation
	if(duty_cycle == I2C_FM_DUTY_2)
	{
	 I2C1->CCR = ( 36 * 1000000)/(3 * I2C_CLOCK);
	 
	}else if(duty_cycle == I2C_FM_DUTY_16BY9)
	{ /* this is to reach 400khz in fm mode */
		I2C1->CCR = ( 36 * 1000000)/(25 * I2C_CLOCK);
	}
	
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
	  //SET_BIT(I2C1->CR1,6); //ENGC=1
		CLR_BIT(I2C1->CR1,7); //NOSTRETCH 
		SET_BIT(I2C1->CR1,10); //ack enabled on receiving bytes
 }
#if 0
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
#endif
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
	SET_BIT(I2C1->CR1 ,8); /* start */
	while(GET_BIT(I2C1->SR1,0) == 0); /* wait for SB */
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
			SET_BIT(I2C1->CR1,9); /* stop */
		//}
	//while(GET_BIT(I2C1->SR2,0)) == 1); /* wait for becoming slave */
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
		if(GET_BIT(stat,9) == 1) /* arbitration lost */
			return 1;
		
		if(GET_BIT(stat,1) == 1) /* address sent */
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

void DISABLE_ACK(void)
{
	I2C1->CR1 &= ~(1<<10); //disable acks
}



void I2C_MasterReadData(u8 I2C_TYPE,u8 address,u32* buff, u8 len,u8 checkStop)
{
	
	if(I2C_TYPE == MI2C1)
	{
		 /* Wait until BUSY flag is reset */
		//I2C_waitForReady(MI2C1);
		
		 /* Disable Pos */
		CLR_BIT(I2C1->CR1,11);
		
		I2C1->CR2|= 1<<11; //DMAEN 
		
		SET_BIT(I2C1->CR2,12); /* LAST DMA*/
		
		
		
	  //I2C1->CR1 &= ~(1<<10); //disable acks
		I2C1->CR1 |= (1<<10); //enable acks
		
		MDMA1_VidSetAddress( CHANNEL7 , &( I2C1 -> DR ) , &( buff ) , len );
		MDMA1_VidInerruptEnable        ( CHANNEL7 , DMA_TCIE );
		MDMA1_VidDMAEnable( CHANNEL7 );
		
		u8 add =0;
		
		do{
				I2C_waitForReady(MI2C1); /* wait while the bus is busy */
				I2C_sendStart(MI2C1);	/* generate start condition */
			 add = I2C_sendAddrForRead(MI2C1,address);
			}while(add != 0); /* send addr.  for read; repeat if arbitration lost */
		
		
		
		do{
		if((I2C1->SR2 & 1<<0) && ((I2C1->SR2 & 1<<2) == 0)) // SB & BTF
			break;
		}while(1);
	
		while(GET_BIT(I2C1->CR2,12)== 0);
		I2C1->CR1 &= ~(1<<10); //disable acks
		//generate STOP condition
		
		if(checkStop == 1)
			I2C_sendStop(MI2C1);

		//while( MDMA1_u8GetFlag( CHANNEL7 , DMA_TCIF ) == 0 );
		//MDMA1_VidClearFlag    ( CHANNEL7 , DMA_TCIF );		
	}
}




void I2C_SlaveSendData(u8 I2C_TYPE,u8* data,u8 len,u8 checkStop)
{
	if(I2C_TYPE == MI2C1)
	{	
		//rest i2c
		CLR_BIT(I2C1->CR1,0);
		SET_BIT(I2C1->CR1,0);
		
		/* Wait until BUSY flag is reset */
		//I2C_waitForReady(MI2C1);
		 /* Disable Pos */
		CLR_BIT(I2C1->CR1,11);
		//I2C1->CR1 &= ~(1<<10); //disable acks
		I2C1->CR1 |= (1<<10); //enable acks
		
		#if 0
		do{
			if(I2C_SlaveListen(MI2C1) == I2C_EVENT_SLAVE_ADDRESS_MATCHED)
				if(I2C_SlaveListen(MI2C1) == I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED)
					break;
		}while(1);
	#endif 
		while(GET_BIT(I2C1->SR1,1)==0);
		u32 temp1 = I2C1->SR1;
		temp1 = I2C1->SR2;
		if (GET_BIT(I2C1->SR2,2)==1)
		{
			u8 i =len;
			for(u8 i=0;i<len;i++)
			{
				I2C1->DR = data[i];
			do{
				
				if((I2C1->SR1 &(1<<7)) != 0) /* TxE = 1 */
					break;
				
			}	while(1);
			
			}
			
			
			if (checkStop==1)
					if ((I2C1->SR1 & (1<<10))) //AF bit
						CLR_BIT(I2C1->SR1,10); //clear AF bit
						
					
				
			}
		}
}




u8 I2C_SlaveListen(u8 I2C_TYPE)
{
	if(I2C_TYPE == MI2C1)
	{	
		u32 stat1 =I2C1->SR1;
		u32 stat2 =I2C1->SR2;
		
		/* ADDR set --------------------------------------------------------------*/	
		if( GET_BIT(stat1,1))
		{
			//stat = I2C1->SR2; /* read SR2 to clear ADDR flag */
			return I2C_EVENT_SLAVE_ADDRESS_MATCHED;
		}
		/* STOPF set --------------------------------------------------------------*/
		else if(GET_BIT(stat1,4))
		{
			CLR_BIT(I2C1->CR1,9);  /* write CR1 to clear STOPF flag */	
			return I2C_EVENT_SLAVE_STOP_DETECTED;
		}
		/* General call address (Slave mode)  */
		else if(GET_BIT(stat2,4))
		{
		 return I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED;	
		}
    /* Data bytes transmitted  */
		else if((GET_BIT(stat2,2)) == 1)
		{
		 return I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED;	
		}
		/* Data bytes received  */
		else if(GET_BIT(stat2,2) == 0)
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



void I2C_Master_Receive(u8 I2C_TYPE, u16 DevAddress, u8 *pData, u8 Size)
{
  
    /* Disable Pos */
    CLR_BIT(I2C1->CR1, 11); //I2C_CR1_POS

    
#if 1
    /* Prepare transfer parameters */
    u8* pBuffPtr    = pData;
    u8 XferCount   = Size;
    u8 XferSize    = XferCount;
    //hi2c->XferOptions = I2C_NO_OPTION_FRAME;
#endif
	
#if 0
		I2C_sendStart(MI2C1);
    /* Send Slave Address */
    if (I2C_sendAddrForRead(I2C1,DevAddress) == 1)
    {
      //return 0;  //HAL_ERROR;
    }
#endif
		u8 add =0;
		do{
				//I2C_waitForReady(MI2C1); /* wait while the bus is busy */
				I2C_sendStart(MI2C1);	/* generate start condition */
				add = I2C_sendAddrForRead(MI2C1,DevAddress);
			}while(add != 0); /* send addr.  for read; repeat if arbitration lost */
		
    if (XferSize == 0U)
    {
      /* Clear ADDR flag */
//      __HAL_I2C_CLEAR_ADDRFLAG(hi2c);

      /* Generate Stop */
      SET_BIT(I2C1->CR1, 9);
    }
    else if (XferSize == 1U)
    {
      /* Disable Acknowledge */
      CLR_BIT(I2C1->CR1, 10);

      /* Clear ADDR flag */
     // __HAL_I2C_CLEAR_ADDRFLAG(hi2c);
     
      /* Generate Stop */
      SET_BIT(I2C1->CR1, 9);

    }
    else if (XferSize == 2U)
    {
      /* Enable Pos */
      SET_BIT(I2C1->CR1, 11);

      /* Clear ADDR flag */
     // __HAL_I2C_CLEAR_ADDRFLAG(hi2c);

      /* Disable Acknowledge */
      CLR_BIT(I2C1->CR1, 10);
    }
    else
    { /* XferSize > 2U */
			
      /* Enable Acknowledge */
      SET_BIT(I2C1->CR1, 10);

      /* Clear ADDR flag */
      //__HAL_I2C_CLEAR_ADDRFLAG(hi2c);
    }

    while (XferSize > 0U)
    {
      if (XferSize <= 3U)
      {
        /* One byte */
        if (XferSize == 1U)
        {
          /* Wait until RXNE flag is set */
          while (GET_BIT(I2C1->SR1,6) != 1);
          

          /* Read data from DR */
          *pBuffPtr = (u8)I2C1->DR;

          /* Increment Buffer pointer */
          pBuffPtr++;

          /* Update counter */
          XferSize--;
          XferCount--;
        }
        /* Two bytes */
        else if (XferSize == 2U)
        {
          /* Wait until BTF flag is set */
           while (GET_BIT(I2C1->SR1,2) != 1);

          /* Generate Stop */
          SET_BIT(I2C1->CR1, 9);

          /* Read data from DR */
          *pBuffPtr = (u8)I2C1->DR;

          /* Increment Buffer pointer */
          pBuffPtr++;

          /* Update counter */
          XferSize--;
          XferCount--;

          /* Read data from DR */
          *pBuffPtr = (u8)I2C1->DR;

          /* Increment Buffer pointer */
          pBuffPtr++;

          /* Update counter */
          XferSize--;
          XferCount--;
        }
        /* 3 Last bytes */
        else
        {
          /* Wait until BTF flag is set */
					u16 timeOut=0;
         while ((GET_BIT(I2C1->SR1,2) != 1)&&(timeOut <10000)){timeOut++;}
 
          /* Disable Acknowledge */
          CLR_BIT(I2C1->CR1, 10);

          /* Read data from DR */
          *pBuffPtr = (u8)I2C1->DR;

          /* Increment Buffer pointer */
          pBuffPtr++;

          /* Update counter */
          XferSize--;
          XferCount--;

          /* Wait until BTF flag is set */
          while (GET_BIT(I2C1->SR1,2) != 1);
 
          /* Generate Stop */
          SET_BIT(I2C1->CR1, 9);

          /* Read data from DR */
          *pBuffPtr = (u8)I2C1->DR;

          /* Increment Buffer pointer */
          pBuffPtr++;

          /* Update counter */
          XferSize--;
          XferCount--;

          /* Read data from DR */
          *pBuffPtr = (u8)I2C1->DR;

          /* Increment Buffer pointer */
          pBuffPtr++;

          /* Update counter */
          XferSize--;
          XferCount--;
        }
      }
      else /* XferSize > 3*/
      { 
        /* Wait until RXNE flag is set */
				 while (GET_BIT(I2C1->SR1,6) != 1);
 

        /* Read data from DR */
        *pBuffPtr = (u8)I2C1->DR;

        /* Increment Buffer pointer */
        pBuffPtr++;

        /* Update counter */
        XferSize--;
        XferCount--;
#if 0
				/* check BTF flag is set */
        if ((GET_BIT(I2C1->SR1,2) != 1)&&(XferSize >3))
        {
          /* Read data from DR */
          *pBuffPtr = (u8)I2C1->DR;

          /* Increment Buffer pointer */
          pBuffPtr++;

          /* Update counter */
					XferSize--;
					XferCount--;
        }
				#endif
      }
    }
  }

	
	
#if 0	
	  
void HAL_I2C_Slave_Transmit(u8 I2C_TYPE, u8 *pData, u8 Size)
{
  
    if ((pData == 0) || (Size == 0U))
    {
     /*Error*/
    }

  
    /* Disable Pos */
    CLR_BIT(I2C1->CR1, 11);


    /* Prepare transfer parameters */
    u8 * pBuffPtr    = pData;
    u8 XferCount   = Size;
    u8 XferSize    = XferCount;

    /* Enable Address Acknowledge */
    SET_BIT(I2C1->CR1, 10);

    /* Wait until ADDR flag is set */
    while(GET_BIT(I2C1->SR1,1)!= 1);

    /* Clear ADDR flag */
    HAL_I2C_CLEAR_ADDRFLAG();

    

    while (XferSize > 0U)
    {
      /* Wait until TXE flag is set */
      while(GET_BIT(I2C1->SR1 ,7) != 1); 

      /* Write data to DR */
      I2C1->DR = *pBuffPtr;

      /* Increment Buffer pointer */
      pBuffPtr++;

      /* Update counter */
      XferCount--;
      XferSize--;

      if ((GET_BIT(I2C1->SR1, 2) == 1) && (XferSize != 0U)) /* I2C_FLAG_BTF */
      {
        /* Write data to DR */
        I2C1->DR = *pBuffPtr;

        /* Increment Buffer pointer */
				pBuffPtr++;

        /* Update counter */
        XferCount--;
        XferSize--;
      }
    }

    /* Wait until AF flag is set */
    while (GET_BIT(I2C1->SR1,10));
		
    /* Clear AF flag */
    CLR_BIT(I2C1->SR1,10);

    /* Disable Address Acknowledge */
    CLR_BIT(I2C1->CR1, 10);

   
}
#endif

void HAL_I2C_CLEAR_ADDRFLAG(void)
{
	u32 stat1 =I2C1->SR1;
	u32 stat2 =I2C1->SR2;
}



void I2C_MasterSendData(u8 I2C_TYPE,u8 address,u8* data,u8 len)
{
	if(I2C_TYPE == MI2C1)
	{
		
	//I2C_sendStart(MI2C1);
	//I2C_sendAddrForWrite(MI2C1,address);	
		u8 add =0;
		do{
				//I2C_waitForReady(MI2C1); /* wait while the bus is busy */
				I2C_sendStart(MI2C1);	/* generate start condition */
				add = I2C_sendAddrForWrite(MI2C1,address);
			}while(add != 0); /* send addr.  for read; repeat if arbitration lost */
		
		do{
		if((I2C1->SR2 & 1<<0) && ((I2C1->SR2 & 1<<2) != 0)) //MSL & TRA
			break;
		}while(1);
			
	for(u8 i=0;i<len;i++)
	{
		I2C1->DR = data[i];
	while(GET_BIT(I2C1->SR1,7)==0); /* TXE =1*/
  
	}
	while(GET_BIT(I2C1->SR1,2)==0);
  
	}
}



#if 1

void I2C_SlaveReadData(u8 I2C_TYPE,u8* buff, u8 len,u8 checkStop)
{
	
	if(I2C_TYPE == MI2C1)
	{
		
		//I2C1->CR2|= 1<<11; //DMAEN 
	  I2C1->CR1 |= 1<<10; //enable acks
		
		#if 0
		do{
		if((I2C_SlaveListen(MI2C1) == I2C_EVENT_SLAVE_ADDRESS_MATCHED )|| (I2C_SlaveListen(MI2C1) == I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED ))
			if(I2C_SlaveListen(MI2C1) == I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED)
				break;
	}while(1);
		#endif
		while(GET_BIT(I2C1->SR1,1)==0);
		u32 temp1 = I2C1->SR1;
		temp1 = I2C1->SR2;
		if (GET_BIT(I2C1->SR2,2)==0)
		{
				u8  size = len;
			while(size>0)
			{
				while(GET_BIT(I2C1->SR1,6) == 0);  //waiting for RxNE 
				buff[len-size] = I2C1->DR;
				size--;
			}
				
			#if 1	
			if(checkStop==1)
			{
				do{
					if(I2C_SlaveListen(MI2C1) == I2C_EVENT_SLAVE_STOP_DETECTED)
						break;
				}while(1);
			}
			#endif
				//while( MDMA1_u8GetFlag( CHANNEL7 , DMA_TCIF ) == 0 ); //waiting for transfer to be completed
				//MDMA1_VidClearFlag    ( CHANNEL7 , DMA_TCIF );

			

			}
		}
}
#endif
//*&***********************************************

#if 0
void I2C_SlaveReadData(u8 I2C_TYPE,u8* buff, u8 len,u8 checkStop)
{
	
	if(I2C_TYPE == MI2C1)
	{
		
		I2C1->CR2|= 1<<11; //DMAEN 
	  I2C1->CR1 |= 1<<10; //enable acks
		MDMA1_VidSetAddress            ( CHANNEL7 , &( I2C1 -> DR ) , buff , len );
		MDMA1_VidInerruptEnable        ( CHANNEL7 , DMA_TCIE );	
		MDMA1_VidDMAEnable             ( CHANNEL7);
		
		do{
		if((I2C_SlaveListen(MI2C1) == I2C_EVENT_SLAVE_ADDRESS_MATCHED )|| (I2C_SlaveListen(MI2C1) == I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED ))
			if(I2C_SlaveListen(MI2C1) == I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED)
				break;
	}while(1);
		
	while( MDMA1_u8GetFlag( CHANNEL7 , DMA_TCIF ) == 0 ); //waiting for transfer to be completed
		MDMA1_VidClearFlag    ( CHANNEL7 , DMA_TCIF );
		
	#if 1	
	if(checkStop==1)
	{
		do{
			if(I2C_SlaveListen(MI2C1) == I2C_EVENT_SLAVE_STOP_DETECTED)
				break;
		}while(1);
	}
	#endif
		

	
	/*
	while((I2C1->SR1&(1<<6)) == 0);  //waiting for RxNE 
	buff[0] = I2C1->DR;
*/
	}
}
#endif
 
 
 
 void HAL_I2C_MasterSendData(u8 I2C_TYPE,u8 address,u8* data,u8 len)
{
	if(I2C_TYPE == MI2C1)
	{
			
		u8 add =0;
		do{
				//I2C_waitForReady(MI2C1); /* wait while the bus is busy */
				I2C_sendStart(MI2C1);	/* generate start condition */
				add = I2C_sendAddrForWrite(MI2C1,address);
			}while(add != 0); /* send addr.  for read; repeat if arbitration lost */
		
		do{
			/* MSL MASTER mode& TRA Data bytes transmitted*/
			if((GET_BIT(I2C1->SR2,0)==1) && (GET_BIT(I2C1->SR2,2) == 1)) //MSL MASTER mode& TRA Data bytes transmitted
				break;
		}while(1);
		
	 u8 size = len; /* reused in onther state */ 
		
	while(size>0)
	{
		u16 timeout = 0;
		while((GET_BIT(I2C1->SR1,7)==0)&&(timeout<100000)){timeout++;} /* wait TXE =1*/
		I2C1->DR = data[len - size];
		size--;
		if((GET_BIT(I2C1->SR1,2)==0)&&(size != 0))//BTF
		{
			I2C1->DR = data[len - size];
			size--;
		}
		timeout = 0;
		while((GET_BIT(I2C1->SR1,2)==0)&&(timeout<100000)){timeout++;} //wait BTF (data send)
	}
	//while(GET_BIT(I2C1->SR1,2)==0);
  
	}
}