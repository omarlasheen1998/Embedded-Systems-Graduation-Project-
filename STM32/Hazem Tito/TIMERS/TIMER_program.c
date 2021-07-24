#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "TIMER_INTERFACE.h"
#include "TIMER_CONFIG.h"
#include "TIMER_PRIVATE.h"
#include "NVIC_interface.h"
#include "PWM_INTERFACE.h"

static void (*TIMER1_CallBack) (void);
static void (*TIMER2_CallBack) (void);
static void (*TIMER3_CallBack) (void);
static void (*TIMER4_CallBack) (void);


u32 finish_micros_t,old_time_micros_t,finish_millis_t,old_time_millis_t;
u64 time_elapsed_micros_t,time_elapsed_millis_t;
u32  Copy_reloadvalue_t,Ticks;



void TIMER_overflow_micros1(void){
	time_elapsed_micros_t+=65535-finish_micros_t;
	old_time_micros_t=0;

}
void TIMER_overflow_micros2(void){
	time_elapsed_micros_t+=65535-finish_micros_t;
	old_time_micros_t=0;

}

void TIMER_overflow_micros3(void){
	time_elapsed_micros_t+=65535-finish_micros_t;
	old_time_micros_t=0;

}
void TIMER_overflow_micros4(void){
	time_elapsed_micros_t+=65535-finish_micros_t;
	old_time_micros_t=0;

}



void TIMER_overflow_millis1(void){
	time_elapsed_millis_t+=65535/1000.0-finish_millis_t;
	old_time_millis_t=0;

}
void TIMER_overflow_millis2(void){
	time_elapsed_millis_t+=65535/1000.0-finish_millis_t;
	old_time_millis_t=0;

}
void TIMER_overflow_millis3(void){
	time_elapsed_millis_t+=65535/1000.0-finish_millis_t;
	old_time_millis_t=0;

}
void TIMER_overflow_millis4(void){
	time_elapsed_millis_t+=65535/1000.0-finish_millis_t;
	old_time_millis_t=0;

}



void TIMER_voidInit(u8 Copy_u8TIMERID){
	switch(Copy_u8TIMERID){
	case TIM1:
		TIM1_PSC=72;  /***** the value to be prescaled by arr register not prescaler reg
		/*         to get 1 MGH FREQUENCY FOR THE TIMER****************/
		//TIM1_ARR=Copy_u8PRESCALAR;
		TIM1_CR1|=(1<<2); // generating an interrupt update when overflow
		TIM1_DIER|=(1<<0); //setting UIE bit (update interrupt enable)
		TIM1_EGR|=(1<<0);  //setting UG bit (update generation)
		//	TIM1_CR1|=(1<<0);  // enabling counter
		NVIC_voidEnableInterrupt(25);

		break;
	case TIM2:
		TIM2_PSC=72;  // the value to be prescaled by arr register not prescaler reg
		/*         to get 1 MGH FREQUENCY FOR THE TIMER****************/
		//TIM2_ARR=Copy_u8PRESCALAR;
		TIM2_CR1|=(1<<2); // generating an interrupt update when overflow
		TIM2_DIER|=(1<<0); //setting UIE bit (update interrupt enable)
		TIM2_EGR|=(1<<0);  //setting UG bit (update generation)
		//	TIM2_CR1|=(1<<0);  // enabling counter
		NVIC_voidEnableInterrupt(28);
		break ;
	case TIM3:
		TIM3_PSC=72;  // the value to be prescaled by arr register not prescaler reg
		/*         to get 1 MGH FREQUENCY FOR THE TIMER****************/
		//TIM3_ARR=Copy_u8PRESCALAR;
		TIM3_CR1|=(1<<2); // generating an interrupt update when overflow
		TIM3_DIER|=(1<<0); //setting UIE bit (update interrupt enable)
		TIM3_EGR|=(1<<0);  //setting UG bit (update generation)
		//	TIM3_CR1|=(1<<0);  // enabling counter
		NVIC_voidEnableInterrupt(29);
		break;
	case TIM4:
		TIM4_PSC=72; // the value to be prescaled by arr register not prescaler reg
		/*         to get 1 MGH FREQUENCY FOR THE TIMER****************/
		//TIM4_ARR=Copy_u8PRESCALAR;
		TIM4_CR1|=(1<<2); // generating an interrupt update when overflow
		TIM4_DIER|=(1<<0); //setting UIE bit (update interrupt enable)
		TIM4_EGR|=(1<<0);  //setting UG bit (update generation)
		//	TIM4_CR1|=(1<<0);  // enabling counter
		NVIC_voidEnableInterrupt(30);
		break;

	}

}




void TIMER_start(u8 Copy_u8TIMERID,u32 Copy_reloadvalue_t,void (*Copy_ptr) (void)){
	switch(Copy_u8TIMERID){
	case TIM1:
		TIM1_ARR=Copy_reloadvalue_t;  //reload the counter value
		TIM1_CR1|=(1<<0); // enable the counter
		TIMER1_CallBack=Copy_ptr;
		break;
	case TIM2:
		TIM2_ARR=Copy_reloadvalue_t;   //reload the counter value
		TIM2_CR1|=(1<<0);  // enable the counter
		TIMER2_CallBack=Copy_ptr;
		break;
	case TIM3:
		TIM3_ARR=Copy_reloadvalue_t;    //reload the counter value
		TIM3_CR1|=(1<<0);   // enable the counter
		TIMER3_CallBack=Copy_ptr;
		break;
	case TIM4:
		TIM4_ARR=Copy_reloadvalue_t;   //reload the counter value
		TIM4_CR1|=(1<<0);   // enable the counter
		TIMER4_CallBack=Copy_ptr;
		break;
	}
}

void TIMER_stop(u8 Copy_u8TIMERID){
	switch(Copy_u8TIMERID){
	case TIM1:
		TIM1_ARR=0;  //reload the counter value
		TIM1_CR1&=~(1<<0); // disable the counter
		break;
	case TIM2:
		TIM2_ARR=0;   //reload the counter value
		TIM2_CR1&=~(1<<0);  // disable the counter
		break;
	case TIM3:
		TIM3_ARR=0;    //reload the counter value
		TIM3_CR1&=~(1<<0);   // disable the counter
		break;
	case TIM4:
		TIM4_ARR=0;   //reload the counter value
		TIM4_CR1&=~(1<<0);   // disable the counter
		break;
	}
}

u32 Get_Elapsedtime(u8 Copy_u8TIMERID,u32  Copy_reloadvalue_t){
	u32 elapsed_time;

	switch(Copy_u8TIMERID){
	case TIM1:
		elapsed_time=TIM1_ARR-Copy_reloadvalue_t;
		return elapsed_time;
		break;
	case TIM2:
		elapsed_time=TIM2_ARR-Copy_reloadvalue_t;
		return elapsed_time;
		break;
	case TIM3:
		elapsed_time=TIM3_ARR-Copy_reloadvalue_t;
		return elapsed_time;
		break;
	case TIM4:
		elapsed_time=TIM4_ARR-Copy_reloadvalue_t;
		return elapsed_time;
		break;
	}
	return elapsed_time;

}

u64 MICROS(u8 Copy_u8TIMERID){
	switch(Copy_u8TIMERID){
	case TIM1:
		finish_micros_t=Get_Elapsedtime(TIM1, 0);
		time_elapsed_micros_t+=finish_micros_t-old_time_micros_t;
		old_time_micros_t=finish_micros_t;
		return time_elapsed_micros_t;
		break;
	case TIM2:
		finish_micros_t=Get_Elapsedtime(TIM2, 0);
		time_elapsed_micros_t+=finish_micros_t-old_time_micros_t;
		old_time_micros_t=finish_micros_t;
		return time_elapsed_micros_t;
		break;
	case TIM3:
		finish_micros_t=Get_Elapsedtime(TIM3, 0);
		time_elapsed_micros_t+=finish_micros_t-old_time_micros_t;
		old_time_micros_t=finish_micros_t;
		return time_elapsed_micros_t;
		break;
	case TIM4:
		finish_micros_t=Get_Elapsedtime(TIM4, 0);
		time_elapsed_micros_t+=finish_micros_t-old_time_micros_t;
		old_time_micros_t=finish_micros_t;
		return time_elapsed_micros_t;
		break;
	}
	return time_elapsed_micros_t;

}
u64 MILLIS(u8 Copy_u8TIMERID){
	switch(Copy_u8TIMERID){
	case TIM1:
		finish_millis_t=Get_Elapsedtime(TIM1,0)/1000.0;
		time_elapsed_millis_t+=finish_millis_t-old_time_millis_t;
		old_time_millis_t=finish_millis_t;
		return time_elapsed_millis_t;
		break;
	case TIM2:
		finish_millis_t=Get_Elapsedtime(TIM2,0)/1000.0;
		time_elapsed_millis_t+=finish_millis_t-old_time_millis_t;
		old_time_millis_t=finish_millis_t;
		return time_elapsed_millis_t;
		break;
	case TIM3:
		finish_millis_t=Get_Elapsedtime(TIM3,0)/1000.0;
		time_elapsed_millis_t+=finish_millis_t-old_time_millis_t;
		old_time_millis_t=finish_millis_t;
		return time_elapsed_millis_t;
		break;
	case TIM4:
		finish_millis_t=Get_Elapsedtime(TIM4, 0)/1000.0;
		time_elapsed_millis_t+=finish_millis_t-old_time_millis_t;
		old_time_millis_t=finish_millis_t;
		return time_elapsed_millis_t;
		break;
	}
	return time_elapsed_millis_t;
}

void START_MICROS(u8 Copy_u8TIMERID){
	switch (Copy_u8TIMERID) {
	case TIM1:
		TIMER_start(TIM1,65535,TIMER_overflow_micros1);
		break;
  case TIM2:
		TIMER_start(TIM2,65535,TIMER_overflow_micros2);
		break;

	case TIM3:
		TIMER_start(TIM3,65535,TIMER_overflow_micros3);
		break;
	case TIM4:
		TIMER_start(TIM4,65535,TIMER_overflow_micros4);
		break;

	}

}
void START_MILLIS(u8 Copy_u8TIMERID){
	switch (Copy_u8TIMERID) {
	case TIM1:
		TIMER_start(TIM1,65535,TIMER_overflow_millis1);
		break;
  case TIM2:
		TIMER_start(TIM2,65535,TIMER_overflow_millis2);
		break;

	case 3:
		TIMER_start(TIM3,65535,TIMER_overflow_millis3);
		break;
	case 4:
		TIMER_start(TIM4,65535,TIMER_overflow_millis4);
		break;

	}
}


void TIM1_UP_IRQHandler(void){
	TIMER1_CallBack();
	TIM1_SR &= ~ (1<<0);
}
void TIM2_IRQHandler(void){
	TIMER2_CallBack();
	TIM2_SR&=~(1<<0);
}
void TIM3_IRQHandler(void){
	TIMER3_CallBack();
	TIM3_SR&=~(1<<0);
}
void TIM4_IRQHandler(void){
	TIMER4_CallBack();
	TIM4_SR&=~(1<<0);
}

void Delay_In_Us(u8 Copy_u8TIMERID,u32 Copy_numberofus){
	static u32 TICKS=0;
	switch(Copy_u8TIMERID){
	case TIM1:
		//TIM1_CR1|=(1<<0);  // enabling counter
	  TIMER_start(TIM1,65535,TIMER_overflow_micros1);	
	  while(MICROS(TIM1)- TICKS<(Copy_numberofus));//still here untill reach my us
		TICKS=MICROS(TIM1);
	  //TIM1_CR1&=~(1<<0);// disable the counter after reaching required us
    TIMER_stop(TIM1);
		break;
	case TIM2:
		//TIM2_CR1|=(1<<0);  // enabling counter
     TIMER_start(TIM1,65535,TIMER_overflow_micros2);	
	  while(MICROS(TIM2)- TICKS<(Copy_numberofus));//still here untill reach my us
		TICKS=MICROS(TIM2);//still here untill reach my us
		//TIM2_CR1&=~(1<<0);// disable the counter after reaching required us
		TIMER_stop(TIM2);
	  break;
	case TIM3:
		//TIM3_CR1|=(1<<0);  // enabling counter
	  TIMER_start(TIM3,0,TIMER_overflow_micros3);	
	  while(MICROS(TIM3)- TICKS<(Copy_numberofus));//still here untill reach my us
		TICKS=MICROS(TIM3);//still here untill reach my us
		TIM3_CR1&=~(1<<0);// disable the counter after reaching required us
		TIMER_stop(TIM3);
	  break;
	case TIM4:
		//TIM4_CR1|=(1<<0);  // enabling counter
    TIMER_start(TIM4,0,TIMER_overflow_micros4);	
	  while(MICROS(TIM4)- TICKS<(Copy_numberofus));//still here untill reach my us
		TICKS=MICROS(TIM4);//still here untill reach my us
	//	TIM4_CR1&=~(1<<0);// disable the counter after reaching required us
		TIMER_stop(TIM4);
	  break;

	}

}


void Delay_In_Ms(u8 Copy_u8TIMERID,u32 Copy_numberofms){
	static u32 TICKS=0;
	switch(Copy_u8TIMERID){
	case TIM1:
		//TIM1_CR1|=(1<<0);  // enabling counter
		TIMER_start(TIM1,65535,TIMER_overflow_millis1);
		while(MILLIS(TIM1)- TICKS<(Copy_numberofms));//still here untill reach my ms
		TICKS = MILLIS(TIM1);//still here untill reach my ms
		//TIM1_CR1&=~(1<<0);// disable the counter after reaching required ms
	  TIMER_stop(TIM1);
			
	break;
	case TIM2:
		//TIM2_CR1|=(1<<0);  // enabling counter
		TIMER_start(TIM2,65535,TIMER_overflow_millis2);	
	  while(MILLIS(TIM2)- TICKS<(Copy_numberofms));//still here untill reach my ms
		TICKS = MILLIS(TIM2);
		//TIM2_CR1&=~(1<<0);// disable the counter after reaching required ms
		TIMER_stop(TIM2);
	  break;
	case TIM3:
		//TIM3_CR1|=(1<<0);  // enabling counter
	  TIMER_start(TIM3,65535,TIMER_overflow_millis3);	
	  while(MILLIS(TIM3)- TICKS<(Copy_numberofms));//still here untill reach my ms
		TICKS = MILLIS(TIM3);
	// 	TIM3_CR1&=~(1<<0);// disable the counter after reaching required ms
		TIMER_stop(TIM3);
		break;
	case TIM4:
		//TIM4_CR1|=(1<<0);  // enabling counter
		TIMER_start(TIM4,65535,TIMER_overflow_millis4);		
	  while(MILLIS(TIM4)- TICKS<(Copy_numberofms));//still here untill reach my ms
		TICKS = MILLIS(TIM4);
		//TIM4_CR1&=~(1<<0);// disable the counter after reaching required ms
		TIMER_stop(TIM4);
	  break;

	}

}


