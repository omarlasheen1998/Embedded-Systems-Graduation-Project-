#include "STD_TYPES.h"

#ifndef I2C_INTERFACE_H_
#define I2C_INTERFACE_H_

#define MI2C1 1
#define MI2C2 2

#define I2C_MASTER 0
#define I2C_SLAVE 1

#define STD_MODE 2
#define FAST_MODE 3

#define SM_FM_BIT 15
#define FM_DUTY_BIT 14

#define ADDRESS_7BITS 7
#define ADDRESS_10BITS 10

#define I2C_EVENT_SLAVE_STOP_DETECTED 10
#define I2C_EVENT_SLAVE_ADDRESS_MATCHED 20
#define I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED 30
#define I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED 40
#define I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED 50



void I2C_Master_init(u8 I2C_TYPE,u32 I2C_CLOCK);

void I2C_waitForReady(u8 I2C_TYPE);
void I2C_sendStart(u8 I2C_TYPE);
void I2C_sendStop(u8 I2C_TYPE);
u8 I2C_sendAddrForRead(u8 I2C_TYPE,u8 addr);
u8 I2C_sendAddrForWrite(u8 I2C_TYPE,u8 addr);

void I2C_MasterSendData(u8 I2C_TYPE,u8 address,u8* data,u8 len);
void I2C_MasterReadData(u8 I2C_TYPE,u8 address,u8* buff, u8 len);

void I2C_voidInterruptInit(u8 I2C_TYPE);
void I2C_voidLoadData(u8 I2C_TYPE,u8 data);
u8 I2C_u8ReturnData(u8 I2C_TYPE);
void I2C1_voidSetCallBack( void (*ptr) (void) );
void I2C2_voidSetCallBack( void (*ptr) (void) );
void I2C_Slave_init(u8 I2C_TYPE,u32 I2C_CLOCK, u16 ownaddress);
u8 I2C_SlaveListen(u8 I2C_TYPE);
void I2C_SlaveSendData(u8 I2C_TYPE,u8* data,u8 len);
void I2C_SlaveReadData(u8 I2C_TYPE,u8* buff, u8 len);









#endif /* I2C_INTERFACE_H_ */
