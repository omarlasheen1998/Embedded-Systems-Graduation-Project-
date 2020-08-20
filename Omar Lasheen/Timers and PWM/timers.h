
/*
 * IncFile1.h
 *
 * Created: 8/18/2020 6:13:41 PM
 *  Author: osama
 */ 


#ifndef timers_H_
#define timers_H_

#define PERIODIC 100

void setUpPWM(char pinno);
void pwmWrite(char pinno,unsigned char pinval);
void setUpPeriodicTimer(long time,unsigned char no_of_times,void (*Local_ISR)(void)); //using timer2
void Timer(); // setup millis using timer0
long long millis(); //return elapsed time in millis
void WDT_ON(char prescaler);
void WDT_OFF();
unsigned int measurePeriod();
unsigned int measureFrequency();
float measureDutyCycle();

#endif /* INCFILE1_H_ */