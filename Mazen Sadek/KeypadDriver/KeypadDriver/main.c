


 
 #include "DIO.h"
 #include "keypad.h"
 #include "RegDIO.h"

int main(void)
{

keypad_initilaization();
pinModeport(portD,OUTPUT);

    while (1) 
    {
		u8 x=keypad_getpress();
		if( x=='2'){
			
			digitalWrightpin(portD,0,HIGH);
		}
		else if( x=='*'){
			
			digitalWrightpin(portD,1,HIGH);
		}
		
    }
}

