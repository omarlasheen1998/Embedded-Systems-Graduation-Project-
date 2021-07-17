/*********************************************************************************/
/* Author    : Omar Lasheen                                                        */
/* Version   : V01                                                               */
/* Date      : 29 Jan 2021                                                       */
/*********************************************************************************/
#include "STD_TYPES.h"

#ifndef CAN_PRIVATE_H
#define CAN_PRIVATE_H


#define CAN_Base_Address      (u32)(0x40006400)      //define the boundary address of CAN


/***********   REGISTER ADDRESSES FOR GPIOA     ***********************/

#define CAN_MCR               *((u32 *)(CAN_Base_Address + 0X00))
#define CAN_MSR               *((u32 *)(CAN_Base_Address + 0X04))
#define CAN_TSR               *((u32 *)(CAN_Base_Address + 0X08))
#define CAN_RF0R               *((u32 *)(CAN_Base_Address + 0X0C))
#define CAN_RF1R               *((u32 *)(CAN_Base_Address + 0X10))
#define CAN_IER               *((u32 *)(CAN_Base_Address + 0X14))
#define CAN_ESR               *((u32 *)(CAN_Base_Address + 0X18))
#define CAN_BTR               *((u32 *)(CAN_Base_Address + 0X1C))
#define CAN_TI0R               *((u32 *)(CAN_Base_Address + 0X180))
#define CAN_TDT0R               *((u32 *)(CAN_Base_Address + 0X184))
#define CAN_TDL0R               *((u32 *)(CAN_Base_Address + 0X188))
#define CAN_TDH0R               *((u32 *)(CAN_Base_Address + 0X18C))
#define CAN_TI1R               *((u32 *)(CAN_Base_Address + 0X190))
#define CAN_TDT1R               *((u32 *)(CAN_Base_Address + 0X194))
#define CAN_TDL1R               *((u32 *)(CAN_Base_Address + 0X198))
#define CAN_TDH1R               *((u32 *)(CAN_Base_Address + 0X19C))
#define CAN_TI2R               *((u32 *)(CAN_Base_Address + 0X1A0))
#define CAN_TDT2R               *((u32 *)(CAN_Base_Address + 0X1A4))
#define CAN_TDL2R               *((u32 *)(CAN_Base_Address + 0X1A8))
#define CAN_TDH2R               *((u32 *)(CAN_Base_Address + 0X1AC))
#define CAN_RI0R               *((u32 *)(CAN_Base_Address + 0X1B0))
#define CAN_RDT0R               *((u32 *)(CAN_Base_Address + 0X1B4))
#define CAN_RDL0R               *((u32 *)(CAN_Base_Address + 0X1B8))
#define CAN_RDH0R               *((u32 *)(CAN_Base_Address + 0X1BC))
#define CAN_RI1R               *((u32 *)(CAN_Base_Address + 0X1C4))
#define CAN_RDL1R               *((u32 *)(CAN_Base_Address + 0X1C8))
#define CAN_RDH1R               *((u32 *)(CAN_Base_Address + 0X1CC))
#define CAN_FMR               *((u32 *)(CAN_Base_Address + 0X200))
#define CAN_FM1R               *((u32 *)(CAN_Base_Address + 0X204))
#define CAN_FS1R               *((u32 *)(CAN_Base_Address + 0X20C))
#define CAN_FFA1R               *((u32 *)(CAN_Base_Address + 0X214))
#define CAN_FA1R               *((u32 *)(CAN_Base_Address + 0X21C))
#define CAN_F0R1               *((u32 *)(CAN_Base_Address + 0X240))
#define CAN_F0R2               *((u32 *)(CAN_Base_Address + 0X244))
#define CAN_F1R1               *((u32 *)(CAN_Base_Address + 0X248))
#define CAN_F1R2               *((u32 *)(CAN_Base_Address + 0X24C))
#define CAN_F2R1               *((u32 *)(CAN_Base_Address + 0X250))
#define CAN_F2R2               *((u32 *)(CAN_Base_Address + 0X254))
#define CAN_F3R1               *((u32 *)(CAN_Base_Address + 0X258))
#define CAN_F3R2               *((u32 *)(CAN_Base_Address + 0X25C))
#define CAN_F4R1               *((u32 *)(CAN_Base_Address + 0X260))
#define CAN_F4R2               *((u32 *)(CAN_Base_Address + 0X264))
#define CAN_F5R1               *((u32 *)(CAN_Base_Address + 0X268))
#define CAN_F5R2               *((u32 *)(CAN_Base_Address + 0X26C))
#define CAN_F6R1               *((u32 *)(CAN_Base_Address + 0X270))
#define CAN_F6R2               *((u32 *)(CAN_Base_Address + 0X274))
#define CAN_F7R1               *((u32 *)(CAN_Base_Address + 0X278))
#define CAN_F7R2               *((u32 *)(CAN_Base_Address + 0X27C))
#define CAN_F8R1               *((u32 *)(CAN_Base_Address + 0X280))
#define CAN_F8R2               *((u32 *)(CAN_Base_Address + 0X284))
#define CAN_F9R1               *((u32 *)(CAN_Base_Address + 0X288))
#define CAN_F9R2               *((u32 *)(CAN_Base_Address + 0X28C))
#define CAN_F10R1               *((u32 *)(CAN_Base_Address + 0X290))
#define CAN_F10R2               *((u32 *)(CAN_Base_Address + 0X294))
#define CAN_F11R1               *((u32 *)(CAN_Base_Address + 0X298))
#define CAN_F11R2               *((u32 *)(CAN_Base_Address + 0X29C))
#define CAN_F12R1               *((u32 *)(CAN_Base_Address + 0X2A0))
#define CAN_F12R2               *((u32 *)(CAN_Base_Address + 0X2A4))
#define CAN_F13R1               *((u32 *)(CAN_Base_Address + 0X2A8))
#define CAN_F13R2               *((u32 *)(CAN_Base_Address + 0X2AC))
#define CAN_F14R1               *((u32 *)(CAN_Base_Address + 0X2B0))
#define CAN_F14R2               *((u32 *)(CAN_Base_Address + 0X2B4))
#define CAN_F15R1               *((u32 *)(CAN_Base_Address + 0X2B8))
#define CAN_F15R2               *((u32 *)(CAN_Base_Address + 0X2BC))
#define CAN_F16R1               *((u32 *)(CAN_Base_Address + 0X2C0))
#define CAN_F16R2               *((u32 *)(CAN_Base_Address + 0X2C4))
#define CAN_F17R1               *((u32 *)(CAN_Base_Address + 0X2C8))
#define CAN_F17R2               *((u32 *)(CAN_Base_Address + 0X2CC))
#define CAN_F18R1               *((u32 *)(CAN_Base_Address + 0X2D0))
#define CAN_F18R2               *((u32 *)(CAN_Base_Address + 0X2D4))
#define CAN_F19R1               *((u32 *)(CAN_Base_Address + 0X2D8))
#define CAN_F19R2               *((u32 *)(CAN_Base_Address + 0X2DC))
#define CAN_F20R1               *((u32 *)(CAN_Base_Address + 0X2E0))
#define CAN_F20R2               *((u32 *)(CAN_Base_Address + 0X2E4))
#define CAN_F21R1               *((u32 *)(CAN_Base_Address + 0X2E8))
#define CAN_F21R2               *((u32 *)(CAN_Base_Address + 0X2EC))
#define CAN_F22R1               *((u32 *)(CAN_Base_Address + 0X2F0))
#define CAN_F22R2               *((u32 *)(CAN_Base_Address + 0X2F4))
#define CAN_F23R1               *((u32 *)(CAN_Base_Address + 0X2F8))
#define CAN_F23R2               *((u32 *)(CAN_Base_Address + 0X2FC))
#define CAN_F24R1               *((u32 *)(CAN_Base_Address + 0X300))
#define CAN_F24R2               *((u32 *)(CAN_Base_Address + 0X304))
#define CAN_F25R1               *((u32 *)(CAN_Base_Address + 0X308))
#define CAN_F25R2               *((u32 *)(CAN_Base_Address + 0X30C))
#define CAN_F26R1               *((u32 *)(CAN_Base_Address + 0X310))
#define CAN_F26R2               *((u32 *)(CAN_Base_Address + 0X314))
#define CAN_F27R1               *((u32 *)(CAN_Base_Address + 0X318))
#define CAN_F27R2               *((u32 *)(CAN_Base_Address + 0X31C))







#endif // CAN_PRIVATE_H0