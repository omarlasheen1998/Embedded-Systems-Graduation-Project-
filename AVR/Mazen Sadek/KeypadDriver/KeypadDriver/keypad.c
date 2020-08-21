 
 #include "DIO.h"
 #include "keypad.h"
 #include "RegDIO.h"
 
  #ifndef F_CPU
  #define F_CPU 16000000ul
  #endif
  
 #include <util/delay.h>

 u8 arr[4][4]={
	            {'7','8','9','/'},
	            {'4','5','6','*'},
		        {'1','2','3','-'},
			    {'#','0','=','+'}
			 };
 
 
void keypad_initilaization(){
	 
	 pinModepin(keypad_port,R0,OUTPUT);
	 pinModepin(keypad_port,R1,OUTPUT);
	 pinModepin(keypad_port,R2,OUTPUT);
	 pinModepin(keypad_port,R3,OUTPUT);
	 
	  pinModepin(keypad_port,C0,INPUT);
	  pinModepin(keypad_port,C1,INPUT);
	  pinModepin(keypad_port,C2,INPUT);
	  pinModepin(keypad_port,C3,INPUT);
	 
	 digitalWrightport(keypad_port,HIGH);
	 
 }


u8 keypad_getpress(){
	u8 result=0;
	
	for(u8 Rows=0; Rows<4;Rows++){
		
		digitalWrightpin(keypad_port,Rows,LOW);
		for(u8 collum=4;collum<8;collum++){
			
			if(digitalRead(keypad_port,collum)==LOW){
				
				 result =arr[Rows][collum-4];
				while(digitalRead(keypad_port,collum)==LOW);
				_delay_ms(10);
				
			}
			
		}
		digitalWrightpin(keypad_port,Rows,HIGH);
		
	}
	
	return result;
	
}