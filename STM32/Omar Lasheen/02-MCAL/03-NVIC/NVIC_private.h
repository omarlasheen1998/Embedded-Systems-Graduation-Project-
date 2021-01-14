/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 5 OCT  2020                                                       */
/*********************************************************************************/
#ifndef NVIC_PRIVATE_H
#define NVIC_PRIVATE_H

/*******************   BASE Address Definition    *********************/

#define NVIC_Base_Address      0xE000E100      //define the boundary address of NVIC
#define SCB_Base_Address       0xE000ED00	   //define the boundary address of SCB

/*******************   Register Definition     ***********************/
/* Interrupt set-enable registers   */
#define NVIC_ISER0			*((uint32 *)(NVIC_Base_Address + 0x000)) /* Enable External interrupts from 0  to 31 */
#define NVIC_ISER1			*((uint32 *)(NVIC_Base_Address + 0x004)) /* Enable External interrupts from 32 to 63 */
//#define NVIC_ISER2			*((uint32 *)(NVIC_Base_Address + 0x008))

/* Interrupt clear-enable registers */
#define NVIC_ICER0			*((uint32 *)(NVIC_Base_Address + 0x080))
#define NVIC_ICER1			*((uint32 *)(NVIC_Base_Address + 0x084))
//#define NVIC_ICER2			*((uint32 *)(NVIC_Base_Address + 0x088))

/* Interrupt set-pending registers  */
#define NVIC_ISPR0			*((uint32 *)(NVIC_Base_Address + 0x100))
#define NVIC_ISPR1			*((uint32 *)(NVIC_Base_Address + 0x104))
//#define NVIC_ISPR2			*((uint32 *)(NVIC_Base_Address + 0x108))

/* Interrupt clear-pending registers */
#define NVIC_ICPR0			*((uint32 *)(NVIC_Base_Address + 0x180))
#define NVIC_ICPR1			*((uint32 *)(NVIC_Base_Address + 0x184))
//#define NVIC_ICPR2			*((uint32 *)(NVIC_Base_Address + 0x188))

/* Interrupt active bit registers   */
#define NVIC_IABR0			*((volatile uint32 *)(NVIC_Base_Address + 0x200))
#define NVIC_IABR1			*((volatile uint32 *)(NVIC_Base_Address + 0x204))
//#define NVIC_IABR2			*((volatile uint32 *)(NVIC_Base_Address + 0x208))

/* Interrupt priority registers     */
/* from 0 to 20 EX: NVIC_IPR[3] */
#define NVIC_IPR			 ((uint8  *)(NVIC_Base_Address + 0x300))

/* Software trigger interrupt register */
#define NVIC_STIR			*((uint32 *)(NVIC_Base_Address + 0xE00))

/* System control block (SCB) */
/* Application interrupt and reset control register  */
#define SCB_AIRCR			*((uint32 *)(SCB_Base_Address  + 0x0C ))

/*******************   Groups & SUB Definition     ***********************/
/* splits the NVIC_PRI_n fields in the Interrupt Priority Registers into separate group priority and subpriority fields.*/

/* in (SCB -> AIRCR) 4 bits for group & 0 sub			 */
#define NVIC_GROUP_4_SUB_0				0x05FA0300
/* in (SCB -> AIRCR) 3 bits for group & 1 bit for sub 	 */
#define NVIC_GROUP_3_SUB_1				0x05FA0400
/* in (SCB -> AIRCR) 2 bits for group & 2 bits for sub	 */
#define NVIC_GROUP_2_SUB_2				0x05FA0500
/* in (SCB -> AIRCR) 1 bits for group & 3 bits for sub 	 */
#define NVIC_GROUP_1_SUB_3				0x05FA0600
/* in (SCB -> AIRCR) 0  group & 4 bits for sub */
#define NVIC_GROUP_0_SUB_4				0x05FA0700


#endif // NVIC_PRIVATE_H
