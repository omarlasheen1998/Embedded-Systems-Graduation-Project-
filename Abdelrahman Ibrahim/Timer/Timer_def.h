/*
 * Timer_def.h
 *
 *  Created on: Aug 4, 2020
 *      Author: Hosny
 */

#ifndef MY_REPO_MCAL_TIMER_TIMER_DEF_H_
#define MY_REPO_MCAL_TIMER_TIMER_DEF_H_


/*** TIMER 0 registers PINS ***/
/*TCCR0*/
#define FOC0 	7
#define WGM00	6
#define COM01	5
#define COM00	4
#define WGM01	3
#define CS02	2
#define CS01	1
#define CS00	0

/*TIMER0 CLK Select ... BITs 0,1,2 in the TCCR0 ... From datasheet*/
#define TIM0_NO_CLK_TIM0_STOP	0b000
#define TIM0_CLK_1				0b001
#define TIM0_CLK_8				0b010
#define TIM0_CLK_64				0b011
#define TIM0_CLK_256			0b100
#define TIM0_CLK_1024			0b101
#define TIM0_EXT_CLK_FE			0b110
#define TIM0_EXT_CLK_RE			0b111

/*TIMER0 Force Output Compare ... BIT 7 in the TCCR0 */
#define TIM0_FOC0_OFF			0
#define TIM0_FOC0_ON			1

/*TIMER0 Wave Generation MODES ... BITs 6,3 in the TCCR0 */
#define TIM0_NORMAL		0b00000000
#define TIM0_PWM_PC		0b01000000
#define TIM0_CTC		0b00001000
#define TIM0_PWM_FAST	0b01001000

/*TIMER0 OC0 MODES (non-PWM) ... BITs5,4 in the TCCR0*/
#define TIM0_NORMAL_PORT	0b00
#define TIM0_TOG_OC0		0b01
#define TIM0_CLR_OC0		0b10
#define TIM0_SET_OC0		0b11

/*TIMER0 OC0 MODES (fast/PC-PWM) ... BITs5,4 in the TCCR0*/
//#define TIM0_NORMAL_PORT		0b00 //already defined
#define TIM0_RESERVED			0b01
#define TIM0_CLR_SET_OC0		0b10
#define TIM0_SET_CLR_OC0		0b11



/* TIMER0 Interrupt State */
#define TIM0_OVF_INT_EN			1  //overflow interrupt
#define TIM0_OVF_INT_DIS		0

#define TIM0_CMP_INT_EN			1  //Compare interrupt
#define TIM0_CMP_INT_DIS		0





#endif /* MY_REPO_MCAL_TIMER_TIMER_DEF_H_ */
