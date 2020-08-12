
#include "ADC.h"
#include "RegDIO.h"



void ADC_initilization(u8 mode_source,u8 pin,u8 number_bits ){
	// source
	if(mode_source ==Internal){
		
		set_bit(ADMUX_REG,7);
		set_bit(ADMUX_REG,6);
	}
	
	else if(mode_source ==AREF){
		
		clc_bit(ADMUX_REG,7);
		clc_bit(ADMUX_REG,6);
	}
	
   //mode bits

if(number_bits==10){
	clc_bit(ADMUX_REG,5);
}

else if(number_bits==8){
	
	set_bit(ADMUX_REG,5);
} 

	//pinsADC
	if(pin == 0){
		
		clc_bit(ADMUX_REG,0);
		clc_bit(ADMUX_REG,1);
		clc_bit(ADMUX_REG,2);
		clc_bit(ADMUX_REG,3);
		clc_bit(ADMUX_REG,4);
		
	}
	
	else if(pin == 1){
		
		set_bit(ADMUX_REG,0);
		clc_bit(ADMUX_REG,1);
		clc_bit(ADMUX_REG,2);
		clc_bit(ADMUX_REG,3);
		clc_bit(ADMUX_REG,4);
		
	}
	
	else if(pin == 2){
		
		clc_bit(ADMUX_REG,0);
		set_bit(ADMUX_REG,1);
		clc_bit(ADMUX_REG,2);
		clc_bit(ADMUX_REG,3);
		clc_bit(ADMUX_REG,4);
		
	}
	
	
	else if(pin == 3){
		
		set_bit(ADMUX_REG,0);
		set_bit(ADMUX_REG,1);
		clc_bit(ADMUX_REG,2);
		clc_bit(ADMUX_REG,3);
		clc_bit(ADMUX_REG,4);
		
	}
	
	else if(pin == 4){
		
		clc_bit(ADMUX_REG,0);
		clc_bit(ADMUX_REG,1);
		set_bit(ADMUX_REG,2);
		clc_bit(ADMUX_REG,3);
		clc_bit(ADMUX_REG,4);
		
	}
	
	else if(pin == 5){
		
		set_bit(ADMUX_REG,0);
		clc_bit(ADMUX_REG,1);
		set_bit(ADMUX_REG,2);
		clc_bit(ADMUX_REG,3);
		clc_bit(ADMUX_REG,4);
	}
	
	else if(pin == 6){
		
		clc_bit(ADMUX_REG,0);
		set_bit(ADMUX_REG,1);
		set_bit(ADMUX_REG,2);
		clc_bit(ADMUX_REG,3);
		clc_bit(ADMUX_REG,4);
		
	}
	
	
	else if(pin == 7){
		
		set_bit(ADMUX_REG,0);
		set_bit(ADMUX_REG,1);
		set_bit(ADMUX_REG,2);
		clc_bit(ADMUX_REG,3);
		clc_bit(ADMUX_REG,4);
		
	}
	
	//Enable
	set_bit(ADCSRA_REG,7);
	
	//Prescaller
	set_bit(ADCSRA_REG,0);
	set_bit(ADCSRA_REG,1);
	set_bit(ADCSRA_REG,2);
	
}


u16 ADC_getValue(u8 number_bits){
	
	//Startconversion
	set_bit(ADCSRA_REG,6);
	
	while( ( (ADCSRA_REG) & (1<<6) ) );
	
	if(number_bits==10){
		
		return ( (ADCL_REG)|(ADCH_REG<<8) ) ;
		
	}
	
	else if (number_bits==8){
		
		return (ADCH_REG);
	}
	
	return 0;
	
}