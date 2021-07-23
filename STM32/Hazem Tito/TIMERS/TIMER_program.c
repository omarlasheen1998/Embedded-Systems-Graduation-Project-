#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "TIMER_interface.h"
#include "TIMER_config.h"
#include "TIMER_private.h"
#include "NVIC_interface.h"

static void (*TIMER1_CallBack) (void);
static void (*TIMER2_CallBack) (void);
static void (*TIMER3_CallBack) (void);
static void (*TIMER4_CallBack) (void);


uint32 finish_micros,old_time_micros,finish_millis,old_time_millis;
uint64 time_elapsed_micros,time_elapsed_millis;
uint32  Copy_reloadvalue;



void TIMER_overflow_micros(uint8 Copy_u8TIMERID){
	switch(Copy_u8TIMERID){
	case 1:
		time_elapsed_micros+=65535-finish_micros;
		old_time_micros=0;
		break;
	case 2:
		time_elapsed_micros+=65535-finish_micros;
		old_time_micros=0;
		break ;
	case 3:
		time_elapsed_micros+=65535-finish_micros;
		old_time_micros=0;
		break;
	case 4:
		time_elapsed_micros+=65535-finish_micros;
		old_time_micros=0;
		break;

	}
}


void TIMER_overflow_millis(uint8 Copy_u8TIMERID){
	switch(Copy_u8TIMERID){
	case 1:
		time_elapsed_millis+=65535-finish_millis;
		old_time_millis=0;
		break;
	case 2:
		time_elapsed_millis+=65535-finish_millis;
		old_time_millis=0;
		break ;
	case 3:
		time_elapsed_millis+=65535-finish_millis;
		old_time_millis=0;
		break;
	case 4:
		time_elapsed_millis+=65535-finish_millis;
		old_time_millis=0;
		break;

	}

}



void TIMER_voidInit(uint8 Copy_u8TIMERID){
	switch(Copy_u8TIMERID){
	case 1:
		TIM1_PSC=72;  /***** the value to be prescaled by arr register not prescaler reg
		/*         to get 1 MGH FREQUENCY FOR THE TIMER****************/
		//TIM1_ARR=Copy_u8PRESCALAR;
		TIM1_CR1|=(1<<2); // generating an interrupt update when overflow
		TIM1_DIER|=(1<<0); //setting UIE bit (update interrupt enable)
		TIM1_EGR|=(1<<0);  //setting UG bit (update generation)
		//	TIM1_CR1|=(1<<0);  // enabling counter
		NVIC_voidEnableInterrupt(25);

		break;
	case 2:
		TIM2_PSC=72;  // the value to be prescaled by arr register not prescaler reg
		/*         to get 1 MGH FREQUENCY FOR THE TIMER****************/
		//TIM2_ARR=Copy_u8PRESCALAR;
		TIM2_CR1|=(1<<2); // generating an interrupt update when overflow
		TIM2_DIER|=(1<<0); //setting UIE bit (update interrupt enable)
		TIM2_EGR|=(1<<0);  //setting UG bit (update generation)
		//	TIM2_CR1|=(1<<0);  // enabling counter
		NVIC_voidEnableInterrupt(28);
		break ;
	case 3:
		TIM3_PSC=72;  // the value to be prescaled by arr register not prescaler reg
		/*         to get 1 MGH FREQUENCY FOR THE TIMER****************/
		//TIM3_ARR=Copy_u8PRESCALAR;
		TIM3_CR1|=(1<<2); // generating an interrupt update when overflow
		TIM3_DIER|=(1<<0); //setting UIE bit (update interrupt enable)
		TIM3_EGR|=(1<<0);  //setting UG bit (update generation)
		//	TIM3_CR1|=(1<<0);  // enabling counter
		NVIC_voidEnableInterrupt(29);
		break;
	case 4:
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




void TIMER_start(uint8 Copy_u8TIMERID,uint32 Copy_reloadvalue,void (*Copy_ptr) (void)){
	switch(Copy_u8TIMERID){
	case 1:
		TIM1_ARR=Copy_reloadvalue;  //reload the counter value
		TIM1_CR1|=(1<<0); // enable the counter
		TIMER1_CallBack=Copy_ptr;
		break;
	case 2:
		TIM2_ARR=Copy_reloadvalue;   //reload the counter value
		TIM2_CR1|=(1<<0);  // enable the counter
		TIMER2_CallBack=Copy_ptr;
		break;
	case 3:
		TIM3_ARR=Copy_reloadvalue;    //reload the counter value
		TIM3_CR1|=(1<<0);   // enable the counter
		TIMER3_CallBack=Copy_ptr;
		break;
	case 4:
		TIM4_ARR=Copy_reloadvalue;   //reload the counter value
		TIM4_CR1|=(1<<0);   // enable the counter
		TIMER4_CallBack=Copy_ptr;
		break;
	}
}

void TIMER_stop(uint8 Copy_u8TIMERID){
	switch(Copy_u8TIMERID){
	case 1:
		TIM1_ARR=0;  //reload the counter value
		TIM1_CR1&=~(1<<0); // disable the counter
		break;
	case 2:
		TIM2_ARR=0;   //reload the counter value
		TIM2_CR1&=~(1<<0);  // disable the counter
		break;
	case 3:
		TIM3_ARR=0;    //reload the counter value
		TIM3_CR1&=~(1<<0);   // disable the counter
		break;
	case 4:
		TIM4_ARR=0;   //reload the counter value
		TIM4_CR1&=~(1<<0);   // disable the counter
		break;
	}
}

uint32 Get_Elapsedtime(uint8 Copy_u8TIMERID,uint32  Copy_reloadvalue){
	uint32 elapsed_time;

	switch(Copy_u8TIMERID){
	case 1:
		elapsed_time=TIM1_ARR-Copy_reloadvalue;
		return elapsed_time;
		break;
	case 2:
		elapsed_time=TIM2_ARR-Copy_reloadvalue;
		return elapsed_time;
		break;
	case 3:
		elapsed_time=TIM3_ARR-Copy_reloadvalue;
		return elapsed_time;
		break;
	case 4:
		elapsed_time=TIM4_ARR-Copy_reloadvalue;
		return elapsed_time;
		break;
	}
	return elapsed_time;

}

uint64 MICROS(uint8 Copy_u8TIMERID,uint32 Copy_reloadvalue){
	switch(Copy_u8TIMERID){
	case 1:
		finish_micros=Get_Elapsedtime(1, Copy_reloadvalue);
		time_elapsed_micros+=finish_micros-old_time_micros;
		old_time_micros=finish_micros;
		return time_elapsed_micros;
		break;
	case 2:
		finish_micros=Get_Elapsedtime(2, Copy_reloadvalue);
		time_elapsed_micros+=finish_micros-old_time_micros;
		old_time_micros=finish_micros;
		return time_elapsed_micros;
		break;
	case 3:
		finish_micros=Get_Elapsedtime(3, Copy_reloadvalue);
		time_elapsed_micros+=finish_micros-old_time_micros;
		old_time_micros=finish_micros;
		return time_elapsed_micros;
		break;
	case 4:
		finish_micros=Get_Elapsedtime(4, Copy_reloadvalue);
		time_elapsed_micros+=finish_micros-old_time_micros;
		old_time_micros=finish_micros;
		return time_elapsed_micros;
		break;
	}
	return time_elapsed_micros;

}
uint64 MILLIS(uint8 Copy_u8TIMERID,uint32 Copy_reloadvalue){
	switch(Copy_u8TIMERID){
	case 1:
		finish_millis=Get_Elapsedtime(1, Copy_reloadvalue);
		time_elapsed_millis+=finish_micros-old_time_millis;
		old_time_millis=finish_millis;
		return time_elapsed_millis;
		break;
	case 2:
		finish_millis=Get_Elapsedtime(2, Copy_reloadvalue);
		time_elapsed_millis+=finish_micros-old_time_millis;
		old_time_millis=finish_millis;
		return time_elapsed_millis;
		break;
	case 3:
		finish_millis=Get_Elapsedtime(3, Copy_reloadvalue);
		time_elapsed_millis+=finish_micros-old_time_millis;
		old_time_millis=finish_millis;
		return time_elapsed_millis;
		break;
	case 4:
		finish_millis=Get_Elapsedtime(4, Copy_reloadvalue);
		time_elapsed_millis+=finish_micros-old_time_millis;
		old_time_millis=finish_millis;
		return time_elapsed_millis;
		break;
	}
	return time_elapsed_millis;
}

void START_MICROS(uint8 Copy_u8TIMERID){
	switch (Copy_u8TIMERID) {
	case 1:
		TIMER_start(1,65535,TIMER_overflow_micros(1));
		break;
	case 2:
		TIMER_start(2,65535,TIMER_overflow_micros(2));
		break;
	case 3:
		TIMER_start(3,65535,TIMER_overflow_micros(3));
		break;
	case 4:
		TIMER_start(4,65535,TIMER_overflow_micros(4));
		break;

	}

}
void START_MILLIS(uint8 Copy_u8TIMERID){
	switch (Copy_u8TIMERID) {
	case 1:
		TIMER_start(1,65535,TIMER_overflow_millis(1));
		break;
	case 2:
		TIMER_start(2,65535,TIMER_overflow_millis(2));
		break;
	case 3:
		TIMER_start(3,65535,TIMER_overflow_millis(3));
		break;
	case 4:
		TIMER_start(4,65535,TIMER_overflow_millis(4));
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

/*void Delay_In_Us(uint8 Copy_u8TIMERID,uint8 Copy_numberofus){
	switch(Copy_u8TIMERID){
	case 1:
		TIM1_CR1|=(1<<0);  // enabling counter
		Ticks=0;
		while(Ticks<Copy_numberofus);//still here untill reach my us
		TIM1_CR1&=~(1<<0);// disable the counter after reaching required us

		break;
	case 2:
		TIM2_CR1|=(1<<0);  // enabling counter
		Ticks=0;
		while(Ticks<Copy_numberofus);//still here untill reach my us
		TIM2_CR1&=~(1<<0);// disable the counter after reaching required us
		break;
	case 3:
		TIM3_CR1|=(1<<0);  // enabling counter
		Ticks=0;
		while(Ticks<Copy_numberofus);//still here untill reach my us
		TIM3_CR1&=~(1<<0);// disable the counter after reaching required us
		break;
	case 4:
		TIM4_CR1|=(1<<0);  // enabling counter
		Ticks=0;
		while(Ticks<Copy_numberofus);//still here untill reach my us
		TIM4_CR1&=~(1<<0);// disable the counter after reaching required us
		break;

	}

}*/
/*void Delay_In_Ms(uint8 Copy_u8TIMERID,uint8 Copy_numberofms){
	switch(Copy_u8TIMERID){
	case 1:
		TIM1_CR1|=(1<<0);  // enabling counter
		Ticks=0;
		while(Ticks<(Copy_numberofms*1000));//still here untill reach my ms
		TIM1_CR1&=~(1<<0);// disable the counter after reaching required ms
		break;
	case 2:
		TIM2_CR1|=(1<<0);  // enabling counter
		Ticks=0;
		while(Ticks<(Copy_numberofms*1000));//still here untill reach my ms
		TIM2_CR1&=~(1<<0);// disable the counter after reaching required ms
		break;
	case 3:
		TIM3_CR1|=(1<<0);  // enabling counter
		Ticks=0;
		while(Ticks<(Copy_numberofms*1000));//still here untill reach my ms
		TIM3_CR1&=~(1<<0);// disable the counter after reaching required ms

		break;
	case 4:
		TIM4_CR1|=(1<<0);  // enabling counter
		Ticks=0;
		while(Ticks<(Copy_numberofms*1000));//still here untill reach my ms
		TIM4_CR1&=~(1<<0);// disable the counter after reaching required ms
		break;

	}

}*/


