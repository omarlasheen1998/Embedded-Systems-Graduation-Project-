#include "Timers.h"


void (*TIMER0_OVF_PTR)(void);
void (*TIMER1_OVF_PTR)(void);
void (*TIMER2_OVF_PTR)(void);

volatile uint32_t OF_Counts0;
volatile uint16_t last_OF_Num0 = 0;
volatile uint32_t OF_counter0 = 0;

volatile uint32_t OF_Counts1 = 0;
volatile uint16_t last_OF_Num1 = 0;
volatile uint32_t OF_counter1 = 0;

volatile uint32_t OF_Counts2 = 0;
volatile uint16_t last_OF_Num2 = 0;
volatile uint32_t OF_counter2 = 0;

volatile uint8_t OF_flag0 = 0;
volatile uint8_t OF_flag1 = 0;
volatile uint8_t OF_flag2 = 0;


void Timer::setClockSource(uint8_t clk){
	switch(this->timerNum){
		case 0:
		TCCR0 |= (clk & 0x07) << CS00;
		return;
		case 1:
		return;
		case 2:
		TCCR2 |= (clk & 0x07) << CS00;
		return;

	}
}



Timer::Timer(uint8_t TimerNumber, uint8_t mode, uint8_t clk_src){


	this->timerNum = TimerNumber;
	this->desiredMode = mode;
	this->clkSource = clk_src;


	if(this->timerNum == 0 || this->timerNum == 2){
		switch(this->clkSource){
			case 0:
			//#warning "CLK Source is not Set."
			break;
			case 1:
			this->timerOF_Time = pow(2,8) * (1 /(float) F_CPU) * pow(10,6);
			break;
			case 2:
			this->timerOF_Time = pow(2,8) * (8 /(float) F_CPU) * pow(10,6);
			break;
			case 3:
			this->timerOF_Time = pow(2,8) * (64 /(float) F_CPU) * pow(10,6);
			break;
			case 4:
			this->timerOF_Time = pow(2,8) * (256 /(float) F_CPU) * pow(10,6);
			break;
			case 5:
			this->timerOF_Time = pow(2,8) * (1024 /(float) F_CPU) * pow(10,6);
			break;
		}
	}
	else if(this->timerNum == 1){
		switch(this->clkSource){
			case 0:
			//#warning "CLK Source is not Set."
			return;
			case 1:
			this->timerOF_Time = pow(2,16) * (1 /(float) F_CPU) * pow(10,6);
			break;
			case 2:
			this->timerOF_Time = pow(2,16) * (8 /(float) F_CPU) * pow(10,6);
			break;
			case 3:
			this->timerOF_Time = pow(2,16) * (64 /(float) F_CPU) * pow(10,6);
			break;
			case 4:
			this->timerOF_Time = pow(2,16) * (256 /(float) F_CPU) * pow(10,6);
			break;
			case 5:
			this->timerOF_Time = pow(2,16) * (1024 /(float) F_CPU) * pow(10,6);
			break;
		}
	}

}


void Timer::CalculateTime(uint16_t desiredTime, double OF_time){
	switch(this->timerNum){
		case 0:
		OF_Counts0 = (desiredTime * pow(10,3)) / OF_time;
		last_OF_Num0 = ((fmod(desiredTime * pow(10,3), OF_time)) / OF_time) * pow(2,8);
		break;
		case 1:
		OF_Counts1 = (desiredTime * pow(10,3)) / OF_time;
		last_OF_Num1 = ((fmod(desiredTime * pow(10,3), OF_time)) / OF_time) * pow(2,8);
		break;
		case 2:
		OF_Counts2 = (desiredTime * pow(10,3)) / OF_time;
		last_OF_Num2 = ((fmod(desiredTime * pow(10,3), OF_time)) / OF_time) * pow(2,8);
		break;

	}

}


void Timer::setup(uint16_t period_ms, void (*Local_ISR)(void)){
	if(this->desiredMode == NORMAL){
		switch(this->timerNum)
		{
		case 0:
			OF_counter0 = 0;
			noInterrupts();

			setClockSource(this->clkSource);
			TIMER0_OVF_PTR = Local_ISR;
			TCNT0 = 0x00;
			TIMSK |= (1 << TOIE0);
			CalculateTime(period_ms, this->timerOF_Time);

			Interrupts();
			break;
		}
	}
}




ISR(TIMER0_OVF_vect){
	noInterrupts();
	OF_counter0++;

	if(OF_counter0 == OF_Counts0){
		TCNT0 = (last_OF_Num0 & 0x00FF);
		OF_flag0 = 1;
		return;
	}

	if(OF_flag0){
		TIMER0_OVF_PTR();
		OF_counter0 = 0;
		OF_flag0 = 0;
	}
	Interrupts();
}

ISR(TIMER2_OVF_vect){
	TIMER2_OVF_PTR();
}
