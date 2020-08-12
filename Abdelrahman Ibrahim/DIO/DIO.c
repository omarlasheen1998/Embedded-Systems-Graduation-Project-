/* GPIO SOURCE FILE
 * DIO.c
 * This source file is for functions implementation
 *  Created on: Aug 2, 2020
 * 		Author: Hosny
 */


#include "DIO_prototypes.h"  //Functions Prototypes
#include "DIO_registers.h"   //registers addresses
#include "DIO_types.h"       //Data types
#include "SDK_Types.h"       //Common header
#include "BIT_CALC.h"        //Common header




 /* How to write in the register?
 * By accessing its address .. to make is easier for typing ..
   registers addresses are defined in DIO_register.h header file

   *NOTE: use (ctrl+space) for selecting data types and defines
*/



/******PORT Functions*******/

/*FUNC_1: Data Direction for whole port  (DDRx Register)
 */
void DIO_SetPortDirection(DIO_PORT_ID Port_ID, DIO_Direction direction)
{
	if(Output == direction)  //put 1 in DDRx .. But which x? .. switch case for x
	{
		switch(Port_ID)
		{
			case PORTA: DDRA_register = 0xff; break;
			case PORTB: DDRB_register = 0xff; break;
			case PORTC: DDRC_register = 0xff; break;
			case PORTD: DDRD_register = 0xff; break;
		}
	}
	else if(Input == direction)  //put 0 in DDRx .. switch for x
	{
		switch(Port_ID)
		{
			case PORTA: DDRA_register = 0x00; break;
			case PORTB: DDRB_register = 0x00; break;
			case PORTC: DDRC_register = 0x00; break;
			case PORTD: DDRD_register = 0x00; break;
		}
	}
}


/*FUNC_2: Port Value for whole port  (PORTx Register)
 *put the (value) in PORTx register .. which x ? .. switch case
 */
void DIO_SetPortValue(DIO_PORT_ID Port_ID, unsigned char value)
{
	switch(Port_ID)
	{
	case PORTA: PORTA_register = value; break;
	case PORTB: PORTB_register = value; break;
	case PORTC: PORTC_register = value; break;
	case PORTD: PORTD_register = value; break;
	}
}



/******************************************************/



/******PINS Functions*****/

/*FUNC_3: Data Direction for Pins separately  (DDRx Register)
 * 1- direction output or input ? .. if condition for each
 * 2- which port ? .. switch case
 * 3- write value to pin  .. FOR WRITING 1: ORing and shift, FOR WRITING 0: ANDing, NOT, and shift
 	SET_BIT and CLR_BIT -- defined in DIO_types.h
 */
void DIO_SetPinDirection(DIO_PORT_ID Port_ID, DIO_PIN_Number PIN_Number, DIO_Direction direction)
{
	if(Output == direction)
	{
		switch(Port_ID)
		{
			/*     ***Defined in DIO_types.h for simplification***
			case PORTA : (DDRA_register) |= (1<<(PIN_Number)); break;
			case PORTB : (DDRB_register) |= (1<<(PIN_Number)); break;
			case PORTC : (DDRC_register) |= (1<<(PIN_Number)); break;
			case PORTD : (DDRD_register) |= (1<<(PIN_Number)); break;
			 */
			case PORTA : 	SET_BIT(DDRA_register,PIN_Number);	break;
			case PORTB :	SET_BIT(DDRB_register,PIN_Number);	break;
			case PORTC :	SET_BIT(DDRC_register,PIN_Number);	break;
			case PORTD :	SET_BIT(DDRD_register,PIN_Number);	break;

		}
	}
	else if(Input == direction)
	{
		switch(Port_ID)
		{
			/*     ***Defined in DIO_types.h for simplification***
			case PORTA : (DDRA_register) &= ~(1<<(PIN_Number)); break;
			case PORTB : (DDRB_register) &= ~(1<<(PIN_Number)); break;
			case PORTC : (DDRC_register) &= ~(1<<(PIN_Number)); break;
			case PORTD : (DDRD_register) &= ~(1<<(PIN_Number)); break;
			*/
			case PORTA :	CLR_BIT(DDRA_register,PIN_Number);	break;
			case PORTB :	CLR_BIT(DDRB_register,PIN_Number);	break;
			case PORTC :	CLR_BIT(DDRC_register,PIN_Number);	break;
			case PORTD :	CLR_BIT(DDRD_register,PIN_Number);	break;
		}
	}
}


/*FUNC_4: Pins values high or low  (DDRx Register)
*/
void DIO_SetPinValue(DIO_PORT_ID Port_ID, DIO_PIN_Number PIN_Number, DIO_Value Value)
{
	u8 ErrorState; //when the argument is out of range .. if condition not satisfied

	if (((Port_ID >= PORTA)&&(Port_ID <= PORTD))&&( (PIN_Number >= pin0)&&(PIN_Number <= pin7))) /*Error check*/
	{
		ErrorState = ErrorStateOK ;

			if (high == Value)  //write 1 in pin's bit in register PORTx .. switch for x
					{
						switch(Port_ID)
						{
							case PORTA : 	SET_BIT(PORTA_register,PIN_Number);	break;
							case PORTB :	SET_BIT(PORTB_register,PIN_Number);	break;
							case PORTC :	SET_BIT(PORTC_register,PIN_Number);	break;
							case PORTD :	SET_BIT(PORTD_register,PIN_Number);	break;
						}
					}
			else if (low == Value)  //write 0 in pin's bit in register PORTx .. switch for x
					{
						switch(Port_ID)
						{
							case PORTA :	CLR_BIT(PORTA_register,PIN_Number);	break;
							case PORTB :	CLR_BIT(PORTB_register,PIN_Number);	break;
							case PORTC :	CLR_BIT(PORTC_register,PIN_Number);	break;
							case PORTD :	CLR_BIT(PORTD_register,PIN_Number);	break;
						}
					}
	 }
	else
	{
		ErrorState = ErrorStateNOK;  //an error occurred
	}
}


/*FUNC_5: Get Pin Value for Pins separately (PINx Register)
 * GET_BIT is defined in DIO_types.c
*/
u8 DIO_GetPinValue(DIO_PORT_ID Port_ID, DIO_PIN_Number PIN_Number)
{
	u8 ErrorState; //when the argument is out of range .. if condition not satisfied
	u8 pinvalue;   //to store pin value and return it

	if (((Port_ID >= PORTA)&&(Port_ID <= PORTD))&&( (PIN_Number >= pin0)&&(PIN_Number <= pin7))) /*Error check*/
	{
		ErrorState = ErrorStateOK ;

		/*Getting Pins Value*/
			switch(Port_ID)
			{
				case PORTA : 	pinvalue = GET_BIT(PINA_register,PIN_Number);	break;
				case PORTB :	pinvalue = GET_BIT(PINB_register,PIN_Number);	break;
				case PORTC :	pinvalue = GET_BIT(PINA_register,PIN_Number);	break;
				case PORTD :	pinvalue = GET_BIT(PINA_register,PIN_Number);	break;
			}

	}
	else
	{
		ErrorState = ErrorStateNOK ; //an error occurred
	}

	return pinvalue ;
}





















