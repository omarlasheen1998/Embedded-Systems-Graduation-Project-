/*
 * Timer_registers.h
 *
 *  Created on: Aug 4, 2020
 *      Author: Hosny
 */

#ifndef MY_REPO_MCAL_TIMER_TIMER_REGISTERS_H_
#define MY_REPO_MCAL_TIMER_TIMER_REGISTERS_H_


/*** TIMER0 registers ***/
#define TCNT0_register 	(*(volatile u8*)0x52)  //The current count
#define TCCR0A_register 	(*(volatile u8*)0x53)  //Timer Counter Configuration Register
#define OCR0A_register 	(*(volatile u8*)0x5C)  //Output Compare Register





/*** For All 3 timers ***/
/*TISMK: Timer/Counter Interrupt Mask */
/*Setting bit0 (TOIE0) to ‘1’ enables the TIMER0 overflow interrupt*/
#define TIMSK_register 	(*(volatile u8*)0x59)

/*TIFR: Timer/Counter Interrupt Flag Register */
/*bit0 (TOV0) is set (one) whenever TIMER0 overflows.
 *This bit is reset (zero) whenever the Interrupt Service Routine (ISR) is executed.
 *If there is no ISR to execute, we can clear it manually by writing one to it.
 */
#define TIFR_register 	(*(volatile u8*)0x58)




#endif /* MY_REPO_MCAL_TIMER_TIMER_REGISTERS_H_ */
