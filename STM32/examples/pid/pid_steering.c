#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include <stdio.h>
#include "GPIO_interface.h"
#include "RCC_interface.h"

#include "USART_INTERFACE.h"
#include "STK_interface.h"
#include "AFIO_interface.h"
#include "NVIC_interface.h"
#include "EXTI_interface.h"

#include "PWM_INTERFACE.h"

void rcc_init  (void);
void Forward_1 (void);
void Backward_1(void);

s32 PID_control_steer (f32 reference_angle);

//f32 kp = 2646.8 , ki=225.45, kd = 514;
//f32 kp = 2646.8 , ki=225.45, kd = 514;
//f32 kp = 20 , ki=20, kd = 6.06;
//f32 kp = 20 , ki=10, kd = 6.06;
//f32 kp = 2276.8 , ki = 125.87, kd=0;
//f32 kp = 0.059942 , ki=0.3697, kd = 0.00226;
f32 kp = 29.88 , ki=20.318, kd = 0.63104;



f32 error_i=0;
s32 error_old=0;//I have to set error old to some non-zero value for the first time

f64 last_time=0;
s32 prev_sp=0;
s32 accum_pwm=0;


s32 calculate_setpoint(u32);

s64 encoder_counter_1 = 0, encoder_counter_2 = 0;

int main()
{
	rcc_init();
	EXTI_voidInit();
	
	STK_voidInit();
	
	USART_voidInit(UART3,500000);
	

	GPIO_voidSetPinDirection(GPIOA, PIN4, INPUT_PULL_UP_DOWN);
	GPIO_voidSetPinDirection(GPIOA, PIN5, INPUT_PULL_UP_DOWN);
	
	GPIO_voidSetPinPull	(GPIOA, PIN4, PULL_UP);
	GPIO_voidSetPinPull	(GPIOA, PIN5, PULL_UP);
	
	EXTI_voidSetCallBack(EXTI_LINE4,Forward_1);
	EXTI_voidSetCallBack(EXTI_LINE5,Backward_1);
	
	EXTI_voidSetSignalLatch(EXTI_LINE4, ON_CHANGE);
	EXTI_voidSetSignalLatch(EXTI_LINE5, ON_CHANGE);
	
	NVIC_voidEnableInterrupt(10);//4
	NVIC_voidEnableInterrupt(23);//5-9
		
	GPIO_voidSetPinDirection(GPIOA, PIN1, OUTPUT_SPEED_50MHZ_PP);
	PWM_voidSetPinDirection(TIM2,CH1);
  
  STK_voidStartMicros();
	   
		 //u32 steer = 3000;
   	u32 setpoints[6]={3000,4000,2000,0,1000,5000};
		u8 j=0;
while(1)
	{
		/*GPIO_voidSetPinValue(GPIOA, PIN3,LOW);
		for(u32 i=0;i<=65535;i+=15)
		{
			PWM_voidWrite(TIM2,CH3,i);
	    x = STK_u32GetElapedTime();	
			while( ((x - old_time)* 1.0/9000) < 10){
			x = STK_u32GetElapedTime();	
			}
			old_time = x;
			rpm = CalculateRPM();
		  USART_voidTransmit(UART3," ,RPM_1 =  ",STRING);
	    USART_voidTransmit(UART3,&rpm,INT);
      USART_voidTransmit(UART3," ,PWM =  ",STRING);
	    USART_voidTransmit(UART3,&i,INT);
		  USART_voidTransmit(UART3," \n",STRING);
		}*/	
      /*rpm = __fabs(encoder_counter_1);		
	    USART_voidTransmit(UART3," encoder =  ",STRING);
	    USART_voidTransmit(UART3,&rpm,INT);
      USART_voidTransmit(UART3," \n",STRING);
		*/

		
		   
     for(u16 i=0;i<1000;i++)
		{
      USART_voidTransmit(UART3,"Setpoint= ",STRING);
	    USART_voidTransmit(UART3, setpoints+j ,INT);
		  USART_voidTransmit(UART3,"	,",STRING);
    
		
    				
			s32 pwm = PID_control_steer(setpoints[j]);
		
		if(pwm >= 0)
		{
		GPIO_voidSetPinValue(GPIOA, PIN1,HIGH);
		PWM_voidWrite(TIM2,CH1,(u16)__fabs(pwm));
		}
		else if (pwm<0)
		{
		GPIO_voidSetPinValue(GPIOA, PIN1,LOW);
		PWM_voidWrite(TIM2,CH1,(u16)__fabs(pwm));
		}
		
	  }
		j++;
		if(j>5)
			j=0;
		
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
//	RCC_voidEnableClock(RCC_APB2,APB2_GPIOC_EN);/*ENABLE PORTC AS IO PINS*/
	RCC_voidEnableClock(RCC_APB1,APB1_TIM2_EN);/*ENABLE PORTC AS IO PINS*/
	RCC_voidEnableClock(RCC_APB1,APB1_USART3_EN);/*ENABLE USART3 */
	
//	RCC_voidEnableClock(RCC_APB2,APB2_USART1_EN);/*ENABLE USART1 */

	
}


void Forward_1 (void)
{
	u8 a = 0,b = 0;
	a = GPIO_u8GetPinValue(GPIOA,PIN4);
	b = GPIO_u8GetPinValue(GPIOA,PIN5);
	
	if(a != b)
		encoder_counter_1++;
	else
		encoder_counter_1--;
}
void Backward_1(void)
{
	u8 a = 0,b = 0;
	a = GPIO_u8GetPinValue(GPIOA,PIN4);
	b = GPIO_u8GetPinValue(GPIOA,PIN5);
	
	if(a == b)
		encoder_counter_1++;
	else
		encoder_counter_1--;
}

s32 calculate_setpoint(u32 angle)
{
u32 setpoint = (angle * 360)/45000;

}
	
	
s32 PID_control_steer (f32 reference_angle)
{
	s32 current_angle=0;
	//u32 x=0,y=0;
	//x = Micros();
	if (reference_angle==prev_sp){
	
	current_angle = encoder_counter_1;
		
	USART_voidTransmit(UART3,"current_angle = ",STRING);
	USART_voidTransmit(UART3,&current_angle,INT);
	//USART_voidTransmit(UART3,"\n",STRING);
		
	f32 time_diff = (Micros()/1000000.0) - last_time;
	last_time +=time_diff;
	
	s32 error_p = reference_angle - current_angle;
	if ( error_p<100 && error_p>-100)
		error_p=0;

	error_i += error_p* time_diff;
	f32 error_d = (error_p - error_old)/time_diff;
	
	s32 drive_pwm = kp*error_p + ki* error_i	+ kd*error_d;
	if ( drive_pwm > 45000)
		drive_pwm = 45000;
	else if (drive_pwm < -45000)
		drive_pwm = -45000;

	if (drive_pwm <12000 && drive_pwm > -12000){
		accum_pwm+=drive_pwm;
		drive_pwm=0;
	}
	if (accum_pwm>15000 || accum_pwm<-15000){
	drive_pwm=accum_pwm;
	accum_pwm=0;
	}
	/*
	USART_voidTransmit(UART3,"	,time_diff =  ",STRING);
	USART_voidTransmit(UART3,&time_diff,FLOAT);
//	USART_voidTransmit(UART3,"\n",STRING);
	

  USART_voidTransmit(UART3,"	,error_p =  ",STRING);
	USART_voidTransmit(UART3,&error_p,INT);
	
  USART_voidTransmit(UART3,"	,error_i =  ",STRING);
	USART_voidTransmit(UART3,&error_i,FLOAT);
	
  USART_voidTransmit(UART3,"	,error_d =  ",STRING);
	USART_voidTransmit(UART3,&error_d,FLOAT);
	
	USART_voidTransmit(UART3,"	,drive_pwm =  ",STRING);
	USART_voidTransmit(UART3,&drive_pwm,INT);
	*/
	USART_voidTransmit(UART3," \n",STRING);	

	
	error_old=error_p;
	prev_sp=reference_angle;

/*  y = Micros() - x;
  
	USART_voidTransmit(UART3,"	,time =  ",STRING);
	USART_voidTransmit(UART3,&y,INT);
	USART_voidTransmit(UART3," \n",STRING);
*/
	return(drive_pwm);
	}
	
	else{
	
	f32 time_diff = (Micros()/1000000.0) - last_time;
	last_time +=time_diff;
	
	s32 error_p = reference_angle - prev_sp;
	//error_i = error_p* time_diff;
	//s32 drive_pwm = kp*error_p+ ki*error_i;
	error_i =0;	
  s32 drive_pwm = kp*error_p;		
		
	USART_voidTransmit(UART3,"current_angle = ",STRING);
	USART_voidTransmit(UART3,&current_angle,INT);
	USART_voidTransmit(UART3,"\n",STRING);
		
		/*
	USART_voidTransmit(UART3,"first reading:  error_p =  ",STRING);
	USART_voidTransmit(UART3,&error_p,INT);
	USART_voidTransmit(UART3,"	,drive_pwm =  ",STRING);
	USART_voidTransmit(UART3,&drive_pwm,INT);
	USART_voidTransmit(UART3," \n",STRING);	
		*/
	error_old=error_p;
	prev_sp=reference_angle;
	
	/* y = Micros() - x;
  
	USART_voidTransmit(UART3,"	,time =  ",STRING);
	USART_voidTransmit(UART3,&y,INT);
	USART_voidTransmit(UART3," \n",STRING);
*/
	return(drive_pwm);
	
	}
/*
	s32 current_angle = calculate_angle();
	s32 error = reference_angle - current_angle;
	error_i += error* time_diff;
	s32 error_d = (error - error_old)/time_diff;
	
	s32 drive_pwm = kp*error + ki*error_i + kd*error_d;
	
	error_old=error;
	return(drive_pwm)
	
*/
}	
