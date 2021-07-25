///////////////////////////////////////////////////////////////////////////////////////
/*Terms of use
///////////////////////////////////////////////////////////////////////////////////////
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//THE SOFTWARE.


///////////////////////////////////////////////////////////////////////////////////////
//Support
///////////////////////////////////////////////////////////////////////////////////////
Website: http://www.brokking.net/imu.html
Youtube: https://youtu.be/4BoIE8YQwM8
Version: 1.0 (May 5, 2016)

///////////////////////////////////////////////////////////////////////////////////////
//Connections
///////////////////////////////////////////////////////////////////////////////////////
Power (5V) is provided to the Arduino pro mini by the FTDI programmer

Gyro - Arduino pro mini
VCC  -  5V
GND  -  GND
SDA  -  A4
SCL  -  A5

Gyro - STM32F103C8T6
VCC  -  3.3V
GND  -  GND
SDA  -  B6
SCL  -  B7

*//////////////////////////////////////////////////////////////////////////////////////

//Include LCD and I2C library
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "RCC_interface.h"

#include "USART_INTERFACE.h"
#include "STK_interface.h"
#include "AFIO_interface.h"
#include "NVIC_interface.h"

#include "I2C_interface.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>


#define SLAVE_ADDRESS  0x40 
#define MASTER_ADDRESS 0x30 

#define imu_address 0x68
#define clockspped 400000


void rcc_init(void);
void setup(void);
void loop(void);
void setup_mpu_6050_registers(void);
void read_mpu_6050_data(void);
void write_LCD(void);
void print_data(void);



float yaw = 0;
float pitch = 0;
float roll = 0;
int16_t package = 0;
long loop_timer;
//char mode = 'Y';
int16_t temp = 0;
//Declaring some global variables
int16_t gyro_x, gyro_y, gyro_z;
int16_t acc_x, acc_y, acc_z;
int acc_total_vector;
int16_t temperature;
long gyro_x_cal, gyro_y_cal, gyro_z_cal;
//long loop_timer;
int lcd_loop_counter;
float angle_yaw = 0,angle_pitch, angle_roll;
int angle_gyro_buffer,angle_pitch_buffer, angle_roll_buffer;
bool set_gyro_angles;
float angle_roll_acc, angle_pitch_acc;
float angle_pitch_output, angle_roll_output;


u64 elapsed_time ;
u64 old_elapsed_time;
u64 *ptr=&elapsed_time;

u32 finish,old_time;

void micros(){

elapsed_time += 16000000/9.0 - finish;
old_time =0;

}


int main(void)
{	
	rcc_init();
	
	USART_voidInit(UART1,9600);
	
	GPIO_voidSetPinDirection(GPIOC,13,OUTPUT_SPEED_50MHZ_PP);
	GPIO_voidSetPinValue(GPIOC,13,HIGH);
	
	I2C_init(MI2C1,clockspped,MASTER_ADDRESS);
  STK_voidInit();
	setup();
	
	while(1)
	{	
		
	loop();
  print_data();
	}


}

void rcc_init(void)
{
	/* first we will operate on the pll mode in rcc with internal clock 8mhz*/
 /* INITIALIZE THE SYSTEM CLOCK TO BE 72 MHZ BY CHOOSING AN EXTERNAL CLOCK 16MHZ AND CHOOSE HSE/2
	AND THE MULTIPLIED NUMBER IN PLL IS 9 TO GET THE 72MHZ */
	RCC_voidInitSysClock();
	
	RCC_voidEnableClock(RCC_APB2,APB2_AFIO_EN);/*ENABLE AFIO AS IO PINS*/
	
	RCC_voidEnableClock(RCC_APB2,APB2_GPIOA_EN);/*ENABLE PORTA AS IO PINS*/
	RCC_voidEnableClock(RCC_APB2,APB2_GPIOB_EN);/*ENABLE PORTB AS IO PINS*/
	RCC_voidEnableClock(RCC_APB2,APB2_GPIOC_EN);/*ENABLE PORTC AS IO PINS*/
	
	RCC_voidEnableClock(RCC_APB2,APB2_USART1_EN);/*ENABLE USART3 */
	
	RCC_voidEnableClock(RCC_APB1,APB1_I2C1_EN);/*ENABLE I2C1 */
}

void setup() {
  // put your setup code here, to run once:
    setup_mpu_6050_registers();
    GPIO_voidSetPinValue(GPIOC,13,LOW);                                   //Set digital output 13 high to indicate startup
	
	USART_voidTransmit(UART1," MPU-6050 IMU \n",STRING);							  //Print text to screen
	USART_voidTransmit(UART1,"     V1.0 \n",STRING);							  //Print text to screen
	STK_voidDelay_ms(1000);
	
	USART_voidTransmit(UART1,"Calibrating gyro",STRING);
 STK_voidDelay_ms(2000);

  for (int cal_int = 0; cal_int < 2000 ; cal_int ++) {                 //Run this code 2000 times
        if(cal_int % 125 == 0){USART_voidTransmit(UART1,".",STRING);}                         //Print a dot on the LCD every 125 readings

		read_mpu_6050_data();                                              //Read the raw acc and gyro data from the MPU-6050
    gyro_z_cal += gyro_z;                                              //Add the gyro z-axis offset to the gyro_z_cal variable
    gyro_y_cal += gyro_y;
    gyro_x_cal += gyro_x;  
				STK_voidDelay_ms(3);                                                          //Delay 1us to simulate the 250Hz program loop
                                                         //Delay 3us to simulate the 250Hz program loop
  } 
	//Divide the gyro_y_cal variable by 2000 to get the avarage offset
  gyro_x_cal /= 2000;                                                  //Divide the gyro_x_cal variable by 2000 to get the avarage offset
  gyro_y_cal /= 2000;                                                  //Divide the gyro_y_cal variable by 2000 to get the avarage offset
  gyro_z_cal /= 2000;   
  GPIO_voidSetPinValue(GPIOC,13,HIGH);                                                //All done, turn the LED off

  STK_voidSetIntervalPeriodic(16000000,micros);	

	 old_elapsed_time = 1.0*STK_u32GetElapedTime()/9; 
}

void loop() {
	
  read_mpu_6050_data();

	finish = 1.0*STK_u32GetElapedTime()/9;
  elapsed_time += finish - old_time;
  old_time = finish;

	u64 difference = elapsed_time - old_elapsed_time;
  	
  if (((gyro_z - gyro_z_cal) > 60) || ((gyro_z - gyro_z_cal) < -60)) {

		angle_yaw += (gyro_z - gyro_z_cal) * ((elapsed_time - old_elapsed_time)/ 500000000.0);

  }

  if (((gyro_y - gyro_y_cal) > 60) || ((gyro_y - gyro_y_cal) < -60)) {

		angle_pitch += (gyro_y - gyro_y_cal) * ((elapsed_time - old_elapsed_time)/500000000.0);

  }
  
	if (((gyro_x - gyro_x_cal) > 60) || ((gyro_x - gyro_x_cal) < -60)) {

		angle_roll += (gyro_x - gyro_x_cal) * ((elapsed_time - old_elapsed_time)/500000000.0);

  }
	
  old_elapsed_time = elapsed_time;
	USART_voidTransmit(UART1,&difference,INT);
	USART_voidTransmit(UART1,"\n",STRING);
	
  yaw = angle_yaw * 8 ;
  pitch = angle_pitch * 8 ;
	roll= angle_roll * 8 ;
	/*if(pitch < -99)
  pitch = -99;
	else if(pitch > 99)
	pitch = 99;
	*/	
  //package = (yaw * 100) + pitch ;

	/*finish = 1.0*STK_u32GetElapedTime()/9;
  elapsed_time += finish - old_time;
  old_time = finish;

	u64 old= elapsed_time;
	
	while(elapsed_time - old <5000)
	{
	
	finish = 1.0*STK_u32GetElapedTime()/9;
  elapsed_time += finish - old_time;
  old_time = finish;

	}
	*/
	//finish = (1.0*STK_u32GetElapedTime()/9.0) + 5000;
	//STK_voidStopTimer();

  //STK_voidDelay_ms(5);
	
 
}

void read_mpu_6050_data() {
u8 send_data;
u8 receive_data[20];
send_data = 0x3B;
I2C_master_tx(MI2C1,imu_address,&send_data,1);																	//Send the requested starting register
I2C_generate_stop_condition(MI2C1);                               			//End the transmission
	
  I2C_master_rx(MI2C1,imu_address,receive_data,14);                              //Request 14 bytes from the MPU-6050
//Subroutine for reading the raw gyro and accelerometer data
 
  acc_x = (receive_data[0]<<8)|receive_data[1];                                  //Add the low and high byte to the acc_x variable
  acc_y = (receive_data[2]<<8)|receive_data[3];                                  //Add the low and high byte to the acc_y variable
  acc_z = (receive_data[4]<<8)|receive_data[5];                                  //Add the low and high byte to the acc_z variable
  
	temperature = (receive_data[6]<<8)|receive_data[7];                            //Add the low and high byte to the temperature variable
  
	gyro_x  = (receive_data[8]<<8)|receive_data[9];                                 //Add the low and high byte to the gyro_x variable
  gyro_y  = (receive_data[10]<<8)|receive_data[11];                                 //Add the low and high byte to the gyro_y variable
  gyro_z  = (receive_data[12]<<8)|receive_data[13];                                 //Add the low and high byte to the gyro_z variable
}

void setup_mpu_6050_registers() {  //Activate the MPU-6050
  u8 send_data[2];
 
  send_data[0] = 0x6B;                                               //Send the requested starting register
  send_data[1] = 0x00;                                                //Set the requested starting register
	
	I2C_master_tx(MI2C1,imu_address,send_data,2);											 //Send the requested starting register
	I2C_generate_stop_condition(MI2C1);                               	 //End the transmission
	
	//Configure the accelerometer (+/-8g)
	send_data[0] = 0x1C;                                               //Send the requested starting register
  send_data[1] = 0x10;                                                //Set the requested starting register
	
	I2C_master_tx(MI2C1,imu_address,send_data,2);											 //Send the requested starting register
	I2C_generate_stop_condition(MI2C1);                               	 //End the transmission
	
 //Configure the gyro (500dps full scale)
	send_data[0] = 0x1B;                                               //Send the requested starting register
	send_data[1] = 0x08;                                                //Set the requested starting register
	
	I2C_master_tx(MI2C1,imu_address,send_data,2);											 //Send the requested starting register
	I2C_generate_stop_condition(MI2C1);                               	 //End the transmission
}


void print_data(void)
{
	
	USART_voidTransmit(UART1,"\n",STRING);
	USART_voidTransmit(UART1,"gyro_x = ",STRING);
	USART_voidTransmit(UART1,&roll,FLOAT);
	USART_voidTransmit(UART1,"           , gyro_y = ",STRING);
	USART_voidTransmit(UART1,&pitch,FLOAT);
	USART_voidTransmit(UART1,"           , gyro_z = ",STRING);
	USART_voidTransmit(UART1,&yaw,FLOAT);

	/*
	USART_voidTransmit(UART1,"\n",CHAR);
	USART_voidTransmit(UART1," temperature = ",STRING);
	USART_voidTransmit(UART1,&temperature,INT);
		
	
	USART_voidTransmit(UART1,"\n",CHAR);
	USART_voidTransmit(UART1,"gyro_x = ",STRING);
	USART_voidTransmit(UART1,&gyro_x,INT);
	USART_voidTransmit(UART1," , gyro_y = ",STRING);
	USART_voidTransmit(UART1,&gyro_y,INT);
	USART_voidTransmit(UART1," , gyro_z = ",STRING);
	USART_voidTransmit(UART1,&gyro_z,INT);
	*/
	USART_voidTransmit(UART1,"\n",STRING);
}










