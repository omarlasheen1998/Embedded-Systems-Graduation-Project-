/*
 * DIO.h
 * This header file is for DIO Functions Prototypes
 *  Created on: Aug 2, 2020
 *      Author: Hosny
 */

#ifndef MY_REPO_MCAL_DIO_DIO_PROTOTYPES_H_  //(ifndef = if not defined) .. for not including file twice
#define MY_REPO_MCAL_DIO_DIO_PROTOTYPES_H_


/*PORT Functions */

/*FUNC_1: PORT Data Direction  (DDRx Register)
 * input arguments: Port ID, Direction
 * void return
 *
 * Port ID data type should be defined!
 * PortA, PortB, PortC, PortD
 * Direction data type should be defined!
 * Input, Output
 *
 * defined using enum in DIO_types.h file
 * */
 void DIO_SetPortDirection(DIO_PORT_ID Port_ID, DIO_Direction direction);


 /*FUNC_2: PORT value  (PORTx Register)
  * input arguments: Port ID, Value
  * void return
  *
  * Value data type will be unsigned 8 bit (ex: 0b00000100, 0xff)
  * */
 void DIO_SetPortValue(DIO_PORT_ID Port_ID, unsigned char value);



 /*************************************/



 /*PINS Functions*/

 /*FUNC_3: Data Direction for Pins separately  (DDRx Register)
  * input arguments: Port ID, Pin number, Data Direction
  * void return
  *
  * Pin number data type should be defined!
  * pin0, pin1, pin2, pin3, pin4, pin5, pin6, pin7
  * defined using enum in DIO_types.h file
  * */
 void DIO_SetPinDirection(DIO_PORT_ID Port_ID, DIO_PIN_Number PIN_Number, DIO_Direction direction);


 /*FUNC_4: Pin Value for Pins separately  (PORTx Register)
  * input arguments: Port ID, Pin number, Value
  * void return
  *
  * DIO_Value should be defined!
  * low, high
  *  defined using enum in DIO_types.h file
  * */
 void DIO_SetPinValue(DIO_PORT_ID Port_ID, DIO_PIN_Number PIN_Number, DIO_Value Value);


 /*FUNC_5: Get Pin Value for Pins separately (PINx Register)
  * input arguments: Port ID, Pin number
  * WILL return value .. high or low .. already defined in DIO_Value
  *
  * */
 DIO_Value DIO_GetPinValue(DIO_PORT_ID Port_ID, DIO_PIN_Number PIN_Number);



 /*************************************/





#endif /* MY_REPO_MCAL_DIO_DIO_PROTOTYPES_H_ */
