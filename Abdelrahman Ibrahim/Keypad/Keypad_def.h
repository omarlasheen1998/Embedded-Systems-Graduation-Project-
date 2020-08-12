/*
 * Keypad_def.h
 *
 *  Created on: Aug 4, 2020
 *      Author: Hosny
 */

#ifndef MY_REPO_MCAL_KEYPAD_KEYPAD_DEF_H_
#define MY_REPO_MCAL_KEYPAD_KEYPAD_DEF_H_


/*Keypad Elements Array*

 	 '7'	 	 '8'		'9'			'A'     ... Row 1 .. Pin0
 	 '4'		 '5'		'6'			'B'     ... Row 2 .. pin1
 	 '1'		 '2'		'3'			'C'     ... Row 3 .. pin2
 	 '*'		 '0'		'#'			'D'     ... Row 4 .. pin3

    Col 1       Col 2       Col 3       Col 4
    pin4		pin5		pin6		pin7
*/

// Columns: Output , Rows: Input (Pull up resistors , Active low)

/* Number of Columns and Rows */
#define ColNum 4
#define RowNum 4



/*Choose Which port Keypad COLMUNS will be Connected to*/
#define ColPort PORTA //Let it be PORT B
/*First 4 pins  .. output*/
#define ColPin1 pin0  //pin A0
#define ColPin2 pin1
#define ColPin3 pin2
#define ColPin4 pin3


/*Choose Which port Keypad ROWS will be Connected to*/
#define RowPort	PORTA //Let it be PORT A
/*Second 4 pins .. input*/
#define RowPin1 pin4  //pin A4
#define RowPin2 pin5
#define RowPin3 pin6
#define RowPin4 pin7




//FUNC_1 .. Pins Initialization
void KPD_PinsInitialization();


//FUNC_2 .. Get pressed key
//Last PressedKey Value remains saved until a new press occurs
//returns the Value of the Key as Char
u8 KPD_GetPressedKey();




#endif /* MY_REPO_MCAL_KEYPAD_KEYPAD_DEF_H_ */
