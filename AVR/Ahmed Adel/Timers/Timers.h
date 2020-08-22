/*
 * Timers.h
 *
 *  Created on: Aug 7, 2020
 *      Author: ahmed
 */

#ifndef TIMERS_H_
#define TIMERS_H_

#include <avr/io.h>
#include <math.h>


class Timer{

public:
	Timer(uint8_t TimerNumber, uint8_t mode, uint8_t clk_src);
	void setClockSource(uint8_t clk);
	void setup(uint16_t period_ms, void (*Local_ISR)(void));


	enum CLOCK_SRC{
		NO_CLK = 0,
		INTERNAL_CLK,
		PS_8,
		PS_64,
		PS_256,
		PS_1024,
		EXT_CLK_FE,
		EXT_CLK_RE

	};

	enum MODE_SELECT{
		NORMAL = 0,
		CTC,
		PWM,
		PHASE_CORRECT = 2,
		FAST_PWM
	};




private:
	uint8_t timerNum;
	uint8_t desiredMode;
	uint8_t clkSource;


	double timerOF_Time;

};


#endif /* TIMERS_H_ */
