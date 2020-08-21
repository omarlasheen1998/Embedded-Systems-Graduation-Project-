#include "interrupt.h"
#include "RegDIO.h"
#include "DIO.h"

void INT_initilizaiton(u8 pin_interrupt,u8 status){
	
set_bit(SREG_REG,7);

// Interrupt 0
if( (pin_interrupt==int0) && (status==Falling) ){
	
	pinModepin(portD,2,INPUT_PULLUP);
	
	set_bit(GICR_REG,6);
	
	clc_bit(MCUCR_REG,0);
	set_bit(MCUCR_REG,1);	
	
}

else if( (pin_interrupt==int0) && (status==Rasing) ){
	
	pinModepin(portD,2,INPUT_PULLUP);
	set_bit(GICR_REG,6);
	
	set_bit(MCUCR_REG,0);
	set_bit(MCUCR_REG,1);
	
}

else if( (pin_interrupt==int0) && (status==Low_level) ){
	
	pinModepin(portD,2,INPUT_PULLUP);
	set_bit(GICR_REG,6);
	
	clc_bit(MCUCR_REG,0);
	clc_bit(MCUCR_REG,0);
	
}

else if( (pin_interrupt==int0) && (status==changing) ){
	
	pinModepin(portD,2,INPUT_PULLUP);
	set_bit(GICR_REG,6);
	
	set_bit(MCUCR_REG,0);
	clc_bit(MCUCR_REG,1);
	
}
//interrupt1
if( (pin_interrupt==int1) && (status==Falling) ){
	
	pinModepin(portD,3,INPUT_PULLUP);
	
	set_bit(GICR_REG,7);
	
	
	clc_bit(MCUCR_REG,2);
	set_bit(MCUCR_REG,3);
	
}


else if( (pin_interrupt==int1) && (status==Rasing)){
	
	pinModepin(portD,3,INPUT_PULLUP);
	
	set_bit(GICR_REG,7);
	
	
	set_bit(MCUCR_REG,2);
	set_bit(MCUCR_REG,3);
	
}

else if( (pin_interrupt==int1) && (status==Low_level)){
	
	pinModepin(portD,3,INPUT_PULLUP);
	
	set_bit(GICR_REG,7);
	
	
	clc_bit(MCUCR_REG,2);
	clc_bit(MCUCR_REG,3);
	
}

else if( (pin_interrupt==int1) && (status==changing)){
	
	pinModepin(portD,3,INPUT_PULLUP);
	
	set_bit(GICR_REG,7);
	
	
	set_bit(MCUCR_REG,2);
	clc_bit(MCUCR_REG,3);
	
}

//interrupt2

if( (pin_interrupt==int2) && (status==Falling)){
	
	pinModepin(portB,2,INPUT_PULLUP);
	
	set_bit(GICR_REG,5);
	
	clc_bit(MCUCSR_REG,6);
	
}

else if( (pin_interrupt==int2) && (status==Rasing)){
	
	pinModepin(portB,2,INPUT_PULLUP);
	
	set_bit(GICR_REG,5);
	
	set_bit(MCUCSR_REG,6);
	
}


	
}
