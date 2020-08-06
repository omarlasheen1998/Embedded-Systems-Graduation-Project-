/* This header file is for DIO types definitions
 * DIO_types.h
 *
 *  Created on: Aug 2, 2020
 *      Author: Hosny
 */

#ifndef MY_REPO_MCAL_DIO_DIO_TYPES_H_
#define MY_REPO_MCAL_DIO_DIO_TYPES_H_



//Defining direction (input argument FUNC_1)
typedef enum{
	Input, //0
	Output //1
}DIO_Direction;


//Defining Port_ID (input argument FUNC_1)
typedef enum{
	PORTA, //0
	PORTB, //1
	PORTC, //2
	PORTD  //3
}DIO_PORT_ID;


//Defining Port Value (input argument FUNC_2)
typedef enum{
	low,  //0
	high, //1
}DIO_Value;


//Defining pin number (input argument FUNC_3)
typedef enum{
	pin0,  //0
	pin1,  //1
	pin2,  //2
	pin3,  //3
	pin4,  //4
	pin5,  //5
	pin6,  //6
	pin7   //7
}DIO_PIN_Number;



#endif /* MY_REPO_MCAL_DIO_DIO_TYPES_H_ */
