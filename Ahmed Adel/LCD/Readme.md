# I2C Driver
###### The driver can be used for both the Master and the Slave programming.

## Methods Description:

**1- void begin(uint8_t type)**

Definition:
This function Initialized the Two-wire Module(TWI)
Arguments:
The Type of the Controller either a Master or Slave.
-TYPE_MASTER
-TYPE_SLAVE

**2- uint8_t beginTransmission(uint8_t addr)**

Definition:
This function Starts the Transmission by sending a start bit followed by the Slave's address and Write bit (SLA+W).
Arguments:
Address of the Slave.
Addresses should be from 1 to 127.

**3- uint8_t requestFrom(uint8_t addr, uint8_t bytes)**

Definition:
This function Sends a Repeated Start bit followed by the Slave's address and Read bit (SLA+R).
Arguments:
- Address of the Slave.
- Number of bytes to be read from the Slave.

**4- void setAddress(uint8_t addr)**

Definition:
This function sets the address of the Slave that will be addressed with by the Master.
Arguments:
Address of the Slave.

**5- uint8_t listen(void)**

Definition:
This function makes the Slave listen to the I2C bus if it has been addressed.

**6- uint8_t write(uint8_t data)**

Definition:
This function writes a data to the I2C bus. It can be used either with the Master or Slave.
Arguments:
The data to be send.

**7- uint8_t read()**

Definition:
This function reads a data from the I2C bus. It can be used either with the Master or Slave.

**8- void disableGeneralCall(void)**

Definition:
This function disable the responding of the General Call for the Slave.


# Example:
## Master Transmitter and Slave Receiver.

###### Master Controller:
```
int main(void)
{

	I2C::begin(TYPE_MASTER);
	
	I2C::beginTransmission(addr);
	I2C::write(1);
	I2C::endTransmission();
	
	while (1)
	{
	}
}

```

###### Slave Controller:
```
 int main(void)
 {
	 
	 I2C::begin(TYPE_SLAVE);
	 
	 I2C::setAddress(addr);
	 
	 I2C::listen();
	 uint8_t readData = I2C::read();
	 
	 while (1)
	{
	}
 }
```

2- Master Reciever and Slave Transmitter.

