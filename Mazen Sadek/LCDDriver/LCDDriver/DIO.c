
#include "RegDIO.h"
#include "DIO.h"



//#include <avr/io.h>

void pinModepin(u8 port,u8 pin ,u8 states){
	//PORTA
	      if (  ( port ==portA ) && (states == INPUT) )
	
		 DDRA_REG &=~(1<<pin);
		 
		 else if (  ( port ==portA ) &&(states == OUTPUT) )
		 DDRA_REG |=(1<<pin);
		 
		 
		 else if (  ( port ==portA ) && (states == INPUT_PULLUP) )
		 {
			 DDRA_REG &=~(1<<pin);
			 PORTA_REG |=(1<<pin);
		 }	
//PORTB	
	
	
 if (  ( port ==portB ) && (states == INPUT) )
 
 DDRB_REG &=~(1<<pin);
 
 else if (  ( port ==portB ) &&(states == OUTPUT) )
 DDRB_REG |=(1<<pin);
 
 
 else if (  ( port ==portB ) && (states == INPUT_PULLUP) )
 {
	 DDRB_REG &=~(1<<pin);
	 PORTB_REG |=(1<<pin);
 }
 
 //PORTC
 
  if (  ( port ==portC ) && (states == INPUT) )
  
  DDRC_REG &=~(1<<pin);
  
  else if (  ( port ==portC ) &&(states == OUTPUT) )
  DDRC_REG |=(1<<pin);
  
  
  else if (  ( port ==portC ) && (states == INPUT_PULLUP) )
  {
	  DDRC_REG &=~(1<<pin);
	  PORTC_REG |=(1<<pin);
  }
  
  //PORTD
  
   if (  ( port ==portD ) && (states == INPUT) )
   
   DDRD_REG &=~(1<<pin);
   
   else if (  ( port ==portD) &&(states == OUTPUT) )
   DDRD_REG |=(1<<pin);
   
   
   else if (  ( port ==portD ) && (states == INPUT_PULLUP) )
   {
	   DDRD_REG &=~(1<<pin);
	   PORTD_REG |=(1<<pin);
   }	
	
	
}




void pinModeport(u8 port,u8 states){
	
	//PORTA
	  if( (port==portA) &&(states==INPUT))
		DDRA_REG =0x00;
		else if  ( (port==portA) &&(states==OUTPUT) )
		DDRA_REG =0xff;
		else if( (port==portA) &&(states == INPUT_PULLUP) )
		{
			DDRA_REG =0X00;
			PORTA_REG =0Xff;
		}
		
		//PORTB
		if( (port==portB) &&(states==INPUT))
		DDRB_REG =0x00;
		else if  ( (port==portB) &&(states==OUTPUT) )
		DDRB_REG =0xff;
		else if( (port==portB) &&(states == INPUT_PULLUP) )
		{
			DDRB_REG =0X00;
			PORTB_REG =0Xff;
		}
		
		//PORTC
		if( (port==portC) &&(states==INPUT))
		DDRC_REG =0x00;
		else if  ( (port==portC) &&(states==OUTPUT) )
		DDRC_REG =0xff;
		else if( (port==portC) &&(states == INPUT_PULLUP) )
		{
			DDRC_REG =0X00;
			PORTC_REG =0Xff;
		}
		
		//PORTD
		if( (port==portD) &&(states==INPUT))
		DDRD_REG =0x00;
		else if  ( (port==portD) &&(states==OUTPUT) )
		DDRD_REG =0xff;
		else if( (port==portD) &&(states == INPUT_PULLUP) )
		{
			DDRD_REG =0X00;
			PORTD_REG =0Xff;
		}
		
	}


void digitalWrightpin(u8 port,u8 pin ,u8 states){
	
//PORTA
	   if((port ==portA) && (states== HIGH))
		
		PORTA_REG |=(1<<pin);
		
		else if((port ==portA) && (states==LOW))
		
		PORTA_REG &=~(1<<pin);
		
 //PORTB
	
	if((port ==portB) &&  (states== HIGH))
	
	PORTB_REG |=(1<<pin);
	
	else if((port ==portB) && (states==LOW))
	
	PORTB_REG &=~(1<<pin);
	
	//PORTC
	if((port ==portC) &&(states== HIGH))
	
	PORTC_REG |=(1<<pin);
	
	else if((port ==portC)&&(states==LOW))
	
	PORTC_REG &=~(1<<pin);
	
	//PORTD
	if((port ==portD) &&(states== HIGH))
	
	PORTD_REG |=(1<<pin);
	
	else if((port ==portD)&&(states==LOW))
	
	PORTD_REG &=~(1<<pin);
	
	
}

void digitalWrightport(u8 port,u8 states){
	
	//	PORTA
	if((port ==portA ) && (states==HIGH))
		PORTA_REG =0xff;
		
   else if((port ==portA ) &&(states==LOW)) 
		PORTA_REG =0x00;
		
	else if	((port ==portA ) && ( (states!=LOW)&&(states!=HIGH) )  )
	PORTA_REG=states;
		
//PORTB
     if((port ==portB ) && (states==HIGH))
	PORTB_REG =0xff;

	else if((port ==portB ) &&(states==LOW))
	PORTB_REG =0x00;

//PORTC
if((port ==portC ) && (states==HIGH))
PORTC_REG =0xff;

else if((port ==portC ) &&(states==LOW))
PORTC_REG =0x00;

//PORTD

if((port ==portD ) && (states==HIGH))
PORTD_REG =0xff;

else if((port ==portD ) &&(states==LOW))
PORTD_REG =0x00;
	
}



u8 digitalRead(u8 port,u8 pin){
	
	
		//PORTA
		if(port==portA)
		return ((PINA_REG >>pin)&(0x01));
		//PORTB
		else if(port==portB)
		return ((PINB_REG >>pin)&(0x01));
		//PORTC
		else if(port==portC)
		return ((PINC_REG >>pin)&(0x01));
		//PORTD
		else if(port==portD)
		return ((PIND_REG >>pin)&(0x01));
		
		else
		return -1;
		
}




	/*
	switch (port){
	
	case portA:
	
	  if(states == INPUT)
		DDRA&=~(1<<pin);
		
		else if(states == OUTPUT)
		DDRA|=(1<<pin);
		else if(states == INPUT_PULLUP)
		{
		DDRA&=~(1<<pin);
		PORTA|=(1<<pin);
		}
		break;
		
	case portB:
	
	  if(states==INPUT)
	  DDRB&=~(1<<pin);
	  else if(states ==OUTPUT)
	  DDRB|=(1<<pin);
	  else if(states == INPUT_PULLUP)
	  {
		  DDRB&=~(1<<pin);
		  PORTB|=(1<<pin);
	  }
	  
	  break;
	case portC:
	
	  if(states==INPUT)
	  DDRC&=~(1<<pin);
	  else if(states ==OUTPUT)
	  DDRC|=(1<<pin);
	  else if(states == INPUT_PULLUP)
	  {
		  DDRC&=~(1<<pin);
		  PORTC|=(1<<pin);
	  }
	  break;
	  
	case portD:
	
	  if(states==INPUT)
	  DDRD&=~(1<<pin);
	  else if(states ==OUTPUT)
	  DDRD|=(1<<pin);
	  else if(states == INPUT_PULLUP)
	  {
		  DDRD&=~(1<<pin);
		  PORTD|=(1<<pin);
	  }
	  break;
	
	}
	}
	
	
	
	void pinModeport(u8 port,u8 states){
		
		switch(port){
			
			case portA:
			if(states==INPUT)
			DDRA=0x00;
			else if(states==OUTPUT)
			DDRA=0xff;
			else if(states == INPUT_PULLUP)
			{
				DDRA=0X00;
				PORTA=0Xff;
			}
			break;
			case portB:
			if(states==INPUT)
			DDRB=0x00;
			else if(states==OUTPUT)
			DDRB=0xff;
			else if(states == INPUT_PULLUP)
			{
				DDRB=0X00;
				PORTB=0Xff;
			}
			
			case portC:
			if(states==INPUT)
			DDRC=0x00;
			else if(states==OUTPUT)
			DDRC=0xff;
			else if(states == INPUT_PULLUP)
			{
				DDRC=0X00;
				PORTC=0Xff;
			}
			
			case portD:
			if(states==INPUT)
			DDRD=0x00;
			else if(states==OUTPUT)
			DDRD=0xff;
			else if(states == INPUT_PULLUP)
			{
				DDRD=0X00;
				PORTD=0Xff;
			}
			
		}
	}
	
	
	void digitalWrightpin(u8 port,u8 pin ,u8 states){
		
		
		switch(port){
			
			case portA:
			
			if(states== HIGH)
			PORTA|=(1<<pin);
			else if(states==LOW)
			PORTA&=~(1<<pin);
			
			case portB:
			
			if(states== HIGH)
			PORTB|=(1<<pin);
			else if(states==LOW)
			PORTB&=~(1<<pin);
			
			case portC:
			if(states== HIGH)
			PORTC|=(1<<pin);
			else if(states==LOW)
			PORTC&=~(1<<pin);
			
			case portD:
			if(states== HIGH)
			PORTD|=(1<<pin);
			else if(states==LOW)
			PORTD&=~(1<<pin);
			
			
		}
		
		
	}
	
	
	void digitalWrightport(u8 port,u8 states){
		
		switch(port){
			
			case portA:
			
			if(states==HIGH)
			PORTA=0xff;
			else if(states==LOW)
			PORTA=0x00;
			
			case portB:
			if(states==HIGH)
			PORTB=0xff;
			else if(states==LOW)
			PORTB=0x00;
			case portC:
			if(states==HIGH)
			PORTC=0xff;
			else if(states==LOW)
			PORTC=0x00;
			
			case portD:
			if(states==HIGH)
			PORTD=0xff;
			else if(states==LOW)
			PORTD=0x00;
			
		}
		
	}
	
	
	u8 digitalRead(u8 port,u8 pin){
		
		switch(port){
			
			case portA:
			return ((PINA>>pin)&(0x01));
			case PORTB:
			return ((PINB>>pin)&(0x01));
			case portC:
			return ((PINB>>pin)&(0x01));
			case portD:
			return ((PINB>>pin)&(0x01));
			
			
			
		}
		
	}*/