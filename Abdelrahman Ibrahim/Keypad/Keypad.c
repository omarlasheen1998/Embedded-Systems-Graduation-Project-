/*
 * Keypad.c
 *
 *  Created on: Aug 4, 2020
 *      Author: Hosny
 */


/*** Include Headers ***/
#include "Types_def.h"
#include "BIT_CALC.h"
#include "DIO_prototypes.h"  //Funcs of pins directions and values

#include "Keypad_def.h"
#include "util/delay.h"


/*** Define Names for 4*4 keypad ***/
u8 PinsArr[RowNum][ColNum] ={{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};
//(RowNum 4) & (ColNum 4) are defined in Keypad_def.h


/*** Functions ***/
//Func_1 .. Pins Initialization
void KPD_PinsInitialization()
{	/*Columns connected to PORTA and the first 4Pins are output*/
		DIO_SetPinDirection(ColPort,ColPin1,Output);  //Pin A0
		DIO_SetPinDirection(ColPort,ColPin2,Output);  //Pin A1
		DIO_SetPinDirection(ColPort,ColPin3,Output);  //Pin A2
		DIO_SetPinDirection(ColPort,ColPin4,Output);  //Pin A3
		/*Write 1 to the Columns*/
		DIO_SetPinValue(ColPort,ColPin1,high);
		DIO_SetPinValue(ColPort,ColPin2,high);
		DIO_SetPinValue(ColPort,ColPin3,high);
		DIO_SetPinValue(ColPort,ColPin4,high);
		/**********************************************************/
		/*Rows connected to PORTA and the Second 4Pins are inputs*/
		DIO_SetPinDirection(RowPort,RowPin1,Input);  //Pin A4
		DIO_SetPinDirection(RowPort,RowPin2,Input);  //Pin A5
		DIO_SetPinDirection(RowPort,RowPin3,Input);  //Pin A6
		DIO_SetPinDirection(RowPort,RowPin4,Input);  //Pin A7
		/*Pulling up*/
		DIO_SetPinValue(RowPort,RowPin1,high);
		DIO_SetPinValue(RowPort,RowPin2,high);
		DIO_SetPinValue(RowPort,RowPin3,high);
		DIO_SetPinValue(RowPort,RowPin4,high);
}


//FUNC_2 .. Get pressed key
//Last PressedKey Value remains saved until a new press occurs
//returns the Value of the Key as Char
/* How it works 
 * put zero in a column and check from row if 
 * if a button is pressed it will read the zero 
 * if not pressed it will read high from the pull up
 */
u8 KPD_GetPressedKey()
{
	u8 u8_ColIndex,u8_RowIndex; //for looping 
	u8 u8_PinValue = 1; //initial value 1, this variable will check if the button is pressed or not 
	//Last PressedKey Value remains saved until a new press occurs
	u8 u8_PressedKeyValue = '@';  //The returned value, initially = '@'

	for(u8_ColIndex =0 ; u8_ColIndex < ColNum ; u8_ColIndex++)
			{
				DIO_SetPinValue(ColPort, u8_ColIndex,low);  //write 0 and check from rows if any button is pressed
				for (u8_RowIndex = 0;u8_RowIndex < RowNum; u8_RowIndex ++)
				{
					DIO_GetPinValue(RowPort,u8_RowIndex,& u8_PinValue);
					if (u8_PinValue == 0)    //if (button is pressed)
					{
						while(u8_PinValue == 0)      //Are you are still pressing? .. if yes, wait until you lift your finger 
						{
							DIO_GetPinValue(RowPort,u8_RowIndex,& u8_PinValue);  //i'm holding the value as you are still pressing
							//Disadvantage .. The proccessor in holding!
							//another method .. switch cases and checking the prestate
						}
						(u8_PressedKeyValue) = PinsArr[u8_RowIndex][u8_ColIndex];  //pick the char from the array

						_delay_ms(20);  //Debouncing

					}
					else{ 
					u8_PressedKeyValue = '@'; //Optional
					}
				}
				DIO_SetPinValue(ColPort, u8_ColIndex,high); //remove the zero you used 
			}


return u8_PressedKeyValue ;
}

//To take numbers of x digits (like passwords or RPM value) .. use for loop with x counts and store values in array of size x using the index
