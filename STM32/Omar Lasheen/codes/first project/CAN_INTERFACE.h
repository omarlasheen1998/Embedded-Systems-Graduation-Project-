/*********************************************************************************/
/* Author    : Omar Lasheen                                                        */
/* Version   : V01                                                               */
/* Date      : 29 Jan 2021                                                       */
/*********************************************************************************/
#include "STD_TYPES.h"

#ifndef CAN_INTERFACE_H
#define CAN_INTERFACE_H

enum BITRATE{CAN_50KBPS, CAN_100KBPS, CAN_125KBPS, CAN_250KBPS, CAN_500KBPS, CAN_1000KBPS};

typedef struct
{
	u16 id;
	u8  data[8];
	u8  len;
} CAN_msg_t;

typedef const struct
{
	u8 TS2;
	u8 TS1;
	u8 BRP;
} CAN_bit_timing_config_t;

extern CAN_bit_timing_config_t can_configs[6];

/**
 * Initializes the CAN controller with specified bit rate.
 *
 * @params: bitrate - Specified bitrate. If this value is not one of the defined constants, bit rate will be defaulted to 125KBS
 *
 */
 void CANInit(enum BITRATE bitrate);
 
/**
 * Decodes CAN messages from the data registers and populates a 
 * CAN message struct with the data fields.
 * 
 * @preconditions A valid CAN message is received
 * @params CAN_rx_msg - CAN message struct that will be populated
 * 
 */
 void CANReceive(CAN_msg_t* CAN_rx_msg);
 
/**
 * Encodes CAN messages using the CAN message struct and populates the 
 * data registers with the sent.
 * 
 * @params CAN_rx_msg - CAN message struct that will be populated
 * 
 */
 void CANSend(CAN_msg_t* CAN_tx_msg);
 
 void CANSetFilter(u16 id);
 
 void CANSetFilters(u16* ids, u8 num);
 
/**
 * Returns whether there are CAN messages available.
 *
 * @returns If pending CAN messages are in the CAN controller
 *
 */
 u8 CANMsgAvail(void);
 
 extern CAN_msg_t CAN_rx_msg;  // Holds receiving CAN messages
 extern CAN_msg_t CAN_tx_msg;  // Holds transmitted CAN messagess


#endif // CAN_INTERFACE_H