#include "Timers.h"

Timer::Timer(uint8_t TimerNumber, uint8_t mode, uint8_t clk_src){
	this->timerNum = TimerNumber;
	this->desiredMode = mode;
	this->clkSource = clk_src;

	if(this->timerNum == 0 || this->timerNum == 2){
		switch(clkSource){
		case 0:
			//#warning "CLK Source is not Set."
			return;
		case 1:
			this->timerOF_Time = pow(2,8) * (1 / F_CPU) * pow(10,6);
			return;
		case 2:
			this->timerOF_Time = pow(2,8) * (8 / F_CPU) * pow(10,6);
			return;
		case 3:
			this->timerOF_Time = pow(2,8) * (64 / F_CPU) * pow(10,6);
			return;
		case 4:
			this->timerOF_Time = pow(2,8) * (256 / F_CPU) * pow(10,6);
			return;
		case 5:
			this->timerOF_Time = pow(2,8) * (1024 / F_CPU) * pow(10,6);
			return;
		}
	}
	else if(this->timerNum == 1){
		switch(clkSource){
			case 0:
				//#warning "CLK Source is not Set."
				return;
			case 1:
				this->timerOF_Time = pow(2,16) * (1 / F_CPU);
				return;
			case 2:
				this->timerOF_Time = pow(2,16) * (8 / F_CPU);
				return;
			case 3:
				this->timerOF_Time = pow(2,16) * (64 / F_CPU);
				return;
			case 4:
				this->timerOF_Time = pow(2,16) * (256 / F_CPU);
				return;
			case 5:
				this->timerOF_Time = pow(2,16) * (1024 / F_CPU);
				return;
		}
	}

}



void Timer::setup(uint16_t period_ms, void (*Local_ISR)(void)){
	if(this->desiredMode == NORMAL){

	}
}
