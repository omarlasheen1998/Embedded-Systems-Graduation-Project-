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

LCD  - Arduino pro mini
VCC  -  5V
GND  -  GND
SDA  -  A4
SCL  -  A5
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

#define clockspped 400000


void rcc_init(void);
void setup(void);
void loop(void);
void setup_mpu_6050_registers(void);
void read_mpu_6050_data(void);
void write_LCD(void);
void print_data(void);
 
//Declaring some global variables
u16 gyro_x, gyro_y, gyro_z;
int16_t acc_x, acc_y, acc_z,acc_total_vector;
int temperature;

long gyro_x_cal, gyro_y_cal, gyro_z_cal;

//long loop_timer;
int lcd_loop_counter;

float angle_pitch, angle_roll;
int angle_pitch_buffer, angle_roll_buffer;
bool set_gyro_angles;
float angle_roll_acc, angle_pitch_acc;
float angle_pitch_output, angle_roll_output;

#define imu_address 0x68



int main(void)
{	
	rcc_init();
	
	USART_voidInit(UART3,9600);
	
	GPIO_voidSetPinDirection(GPIOC,13,OUTPUT_SPEED_50MHZ_PP);
	GPIO_voidSetPinValue(GPIOC,13,HIGH);
	
	I2C_init(MI2C1,clockspped,MASTER_ADDRESS);

	setup();
	
	while(1)
	{	
		
	loop();

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
	
	RCC_voidEnableClock(RCC_APB1,APB1_USART3_EN);/*ENABLE USART3 */
	
	RCC_voidEnableClock(RCC_APB1,APB1_I2C1_EN);/*ENABLE I2C1 */
}






void setup(void) {
  
  setup_mpu_6050_registers();                                         //Setup the registers of the MPU-6050 (500dfs / +/-8g) and start the gyro

  GPIO_voidSetPinValue(GPIOC,13,LOW);                                 //Set digital output 13 high to indicate startup
	
	USART_voidTransmit(UART3," MPU-6050 IMU \n",STRING);							  //Print text to screen
	USART_voidTransmit(UART3,"     V1.0 \n",STRING);							  //Print text to screen
	STK_voidDelay_ms(1000);
	/*
	USART_voidTransmit(UART3,"Calibrating gyro",STRING);
	
  for (int cal_int = 0; cal_int < 2000 ; cal_int ++){                  //Run this code 2000 times
    if(cal_int % 125 == 0){USART_voidTransmit(UART3,".",CHAR);}                         //Print a dot on the LCD every 125 readings
		
    read_mpu_6050_data();                                              //Read the raw acc and gyro data from the MPU-6050
    gyro_x_cal += gyro_x;                                              //Add the gyro x-axis offset to the gyro_x_cal variable
    gyro_y_cal += gyro_y;                                              //Add the gyro y-axis offset to the gyro_y_cal variable
    gyro_z_cal += gyro_z;                                              //Add the gyro z-axis offset to the gyro_z_cal variable
    STK_voidDelay_ms(3);                                                          //Delay 3us to simulate the 250Hz program loop
  }
  gyro_x_cal /= 2000;                                                  //Divide the gyro_x_cal variable by 2000 to get the avarage offset
  gyro_y_cal /= 2000;                                                  //Divide the gyro_y_cal variable by 2000 to get the avarage offset
  gyro_z_cal /= 2000;                                                  //Divide the gyro_z_cal variable by 2000 to get the avarage offset
 
  */
  GPIO_voidSetPinValue(GPIOC,13,HIGH);                                                //All done, turn the LED off
  
  
}

void loop(void){

  read_mpu_6050_data();                                                //Read the raw acc and gyro data from the MPU-6050
	print_data();
/* 
	gyro_x -= gyro_x_cal;                                                //Subtract the offset calibration value from the raw gyro_x value
  gyro_y -= gyro_y_cal;                                                //Subtract the offset calibration value from the raw gyro_y value
  gyro_z -= gyro_z_cal;                                                //Subtract the offset calibration value from the raw gyro_z value
  
  //Gyro angle calculations
  //0.0000611 = 1 / (250Hz / 65.5)
  angle_pitch += gyro_x * 0.0000611;                                   //Calculate the traveled pitch angle and add this to the angle_pitch variable
  angle_roll += gyro_y * 0.0000611;                                    //Calculate the traveled roll angle and add this to the angle_roll variable
  
  //0.000001066 = 0.0000611 * (3.142(PI) / 180degr) The Arduino sin function is in radians
  angle_pitch += angle_roll * sin(gyro_z * 0.000001066);               //If the IMU has yawed transfer the roll angle to the pitch angel
  angle_roll -= angle_pitch * sin(gyro_z * 0.000001066);               //If the IMU has yawed transfer the pitch angle to the roll angel
  
  //Accelerometer angle calculations
  acc_total_vector = sqrt((acc_x*acc_x)+(acc_y*acc_y)+(acc_z*acc_z));  //Calculate the total accelerometer vector
  //57.296 = 1 / (3.142 / 180) The Arduino asin function is in radians
  angle_pitch_acc = asin((float)acc_y/acc_total_vector)* 57.296;       //Calculate the pitch angle
  angle_roll_acc = asin((float)acc_x/acc_total_vector)* -57.296;       //Calculate the roll angle
  
  //Place the MPU-6050 spirit level and note the values in the following two lines for calibration
  angle_pitch_acc -= 0.0;                                              //Accelerometer calibration value for pitch
  angle_roll_acc -= 0.0;                                               //Accelerometer calibration value for roll

  if(set_gyro_angles){                                                 //If the IMU is already started
    angle_pitch = angle_pitch * 0.9996 + angle_pitch_acc * 0.0004;     //Correct the drift of the gyro pitch angle with the accelerometer pitch angle
    angle_roll = angle_roll * 0.9996 + angle_roll_acc * 0.0004;        //Correct the drift of the gyro roll angle with the accelerometer roll angle
  }
  else{                                                                //At first start
    angle_pitch = angle_pitch_acc;                                     //Set the gyro pitch angle equal to the accelerometer pitch angle 
    angle_roll = angle_roll_acc;                                       //Set the gyro roll angle equal to the accelerometer roll angle 
    set_gyro_angles = true;                                            //Set the IMU started flag
  }
  
  //To dampen the pitch and roll angles a complementary filter is used
  angle_pitch_output = angle_pitch_output * 0.9 + angle_pitch * 0.1;   //Take 90% of the output pitch value and add 10% of the raw pitch value
  angle_roll_output = angle_roll_output * 0.9 + angle_roll * 0.1;      //Take 90% of the output roll value and add 10% of the raw roll value
  
 // write_LCD();                                                         //Write the roll and pitch values to the LCD display
*/
  STK_voidDelay_ms(250);                                //Wait until the loop_timer reaches 4000us (250Hz) before starting the next loop
}

void read_mpu_6050_data(void){  
		//Subroutine for reading the raw gyro and accelerometer data
	//Start communicating with the MPU-6050
	u8 send_data;
	u8 receive_data[20];
	send_data = 0x43;
	I2C_master_tx(MI2C1,imu_address,&send_data,1);																		//Send the requested starting register
	I2C_generate_stop_condition(MI2C1);                               			  //End the transmission
	
  I2C_master_rx(MI2C1,imu_address,receive_data,6);                              //Request 14 bytes from the MPU-6050

	

  acc_x 				= (receive_data[0]<<8)|receive_data[1];                                  //Add the low and high byte to the acc_x variable
  acc_y 				= (receive_data[2]<<8)|receive_data[3];                                  //Add the low and high byte to the acc_y variable
  acc_z			 		= (receive_data[4]<<8)|receive_data[5];                                  //Add the low and high byte to the acc_z variable
  /*
	temperature 	= (receive_data[6]<<8)|receive_data[7];                            //Add the low and high byte to the temperature variable
  
	gyro_x  			= (receive_data[8]<<8)|receive_data[9];                                 //Add the low and high byte to the gyro_x variable
  gyro_y  			= (receive_data[10]<<8)|receive_data[11];                                 //Add the low and high byte to the gyro_y variable
  gyro_z  			= (receive_data[12]<<8)|receive_data[13];                                 //Add the low and high byte to the gyro_z variable
	
	*/

}

void write_LCD(void){                                                      //Subroutine for writing the LCD
	int data_flag;
	
  //To get a 250Hz program loop (4us) it's only possible to write one character per loop
  //Writing multiple characters is taking to much time
  if(lcd_loop_counter == 14)lcd_loop_counter = 0;                      //Reset the counter after 14 characters
  lcd_loop_counter ++;                                                 //Increase the counter
	
  if(lcd_loop_counter == 1){
    angle_pitch_buffer = angle_pitch_output * 10;                      //Buffer the pitch angle because it will change
    USART_voidTransmit(UART3,"Pitch:",STRING);                                               //Set the LCD cursor to position to position 0,0
  }
  if(lcd_loop_counter == 2){
    if(angle_pitch_buffer < 0)USART_voidTransmit(UART3,"-",CHAR);                          //Print - if value is negative
    else USART_voidTransmit(UART3,"+",CHAR);                                                //Print + if value is negative
  }
	
  if(lcd_loop_counter == 3)
	{//Print first number
		data_flag = abs(angle_pitch_buffer)/1000;
		USART_voidTransmit(UART3,&data_flag,INT);    											
	}
	if(lcd_loop_counter == 4)
	{//Print second number
		data_flag = (abs(angle_pitch_buffer)/100)%10;
		USART_voidTransmit(UART3,&data_flag,INT);    											
	}
  if(lcd_loop_counter == 5)
	{//Print third number
		data_flag = (abs(angle_pitch_buffer)/10)%10;
		USART_voidTransmit(UART3,&data_flag,INT);    											
	}
  if(lcd_loop_counter == 6)USART_voidTransmit(UART3,".",CHAR);         //Print decimal point
	if(lcd_loop_counter == 7)
	{ //Print decimal number
		data_flag = abs(angle_pitch_buffer)%10;
		USART_voidTransmit(UART3,&data_flag,INT);    											
	}
	 
	
  if(lcd_loop_counter == 8){
    angle_roll_buffer = angle_roll_output * 10;
		USART_voidTransmit(UART3,"\n",CHAR);
    USART_voidTransmit(UART3,"Roll :",STRING);
  }
	  if(lcd_loop_counter == 9){
    if(angle_roll_output < 0)USART_voidTransmit(UART3,"-",CHAR);                          //Print - if value is negative
    else USART_voidTransmit(UART3,"+",CHAR);                                                //Print + if value is negative
  }
		if(lcd_loop_counter == 10)
	{//Print first number
		data_flag = abs(angle_roll_output)/1000;
		USART_voidTransmit(UART3,&data_flag,INT);    											
	}
	if(lcd_loop_counter == 11)
	{//Print second number
		data_flag = (abs(angle_roll_output)/100)%10;
		USART_voidTransmit(UART3,&data_flag,INT);    											
	}
  if(lcd_loop_counter == 12)
	{//Print third number
		data_flag = (abs(angle_roll_output)/10)%10;
		USART_voidTransmit(UART3,&data_flag,INT);    											
	}
  if(lcd_loop_counter == 13)USART_voidTransmit(UART3,".",CHAR);         //Print decimal point
	if(lcd_loop_counter == 14)
	{ //Print decimal number
		data_flag = abs(angle_roll_output)%10;
		USART_voidTransmit(UART3,&data_flag,INT); 
		USART_voidTransmit(UART3,"\n",CHAR);		
	}
  
  	
}

void setup_mpu_6050_registers(void){
  //Activate the MPU-6050
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
	
	USART_voidTransmit(UART3,"\n",CHAR);
	USART_voidTransmit(UART3,"acc_x = ",STRING);
	USART_voidTransmit(UART3,&acc_x,INT);
	USART_voidTransmit(UART3," , acc_y = ",STRING);
	USART_voidTransmit(UART3,&acc_y,INT);
	USART_voidTransmit(UART3," , acc_z = ",STRING);
	USART_voidTransmit(UART3,&acc_z,INT);
	/*
	USART_voidTransmit(UART3,"\n",CHAR);
	USART_voidTransmit(UART3," temperature = ",STRING);
	USART_voidTransmit(UART3,&temperature,INT);
		
	
	USART_voidTransmit(UART3,"\n",CHAR);
	USART_voidTransmit(UART3,"gyro_x = ",STRING);
	USART_voidTransmit(UART3,&gyro_x,INT);
	USART_voidTransmit(UART3," , gyro_y = ",STRING);
	USART_voidTransmit(UART3,&gyro_y,INT);
	USART_voidTransmit(UART3," , gyro_z = ",STRING);
	USART_voidTransmit(UART3,&gyro_z,INT);
	*/
	USART_voidTransmit(UART3,"\n",CHAR);
}










