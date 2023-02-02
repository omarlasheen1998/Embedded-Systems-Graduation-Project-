#define F_CPU 8000000UL

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

#include "Gpio.h"

TaskHandle_t taskomar;
void read_button (void* ptr);

TimerHandle_t timer1;
void led_toggle (TimerHandle_t timer1);


uint16_t period = 1000;
uint8_t flag = 0;
uint8_t flag1 = 0;

int main(void)
{
    pinMode(A0, INPUT_PULLUP);
	pinMode(A1, INPUT_PULLUP);
	pinMode(A2, INPUT_PULLUP);
	pinMode(A3, INPUT_PULLUP);
	pinMode(A4, OUTPUT);
	pinMode(A5, OUTPUT);
	
	timer1 = xTimerCreate("tarek",pdMS_TO_TICKS(1000), pdTRUE,(void*) 0, led_toggle);
	
 	
	if (xTaskCreate(read_button, "omar", 100, NULL,0, taskomar) != pdTRUE)
	{
		digitalWrite(A5,HIGH);
	}
	
		xTimerStart(timer1, 0);

	vTaskStartScheduler();
	
}

void read_button (void* ptr)
{
	while(1)
	{
		if(digitalRead(A0) == 0 && flag == 0)
		{
			xTimerReset(timer1,0);
			flag = 1;
		}
		else if(digitalRead(A1) == 0 && flag == 0)
		{
			xTimerStop(timer1,0);
			flag = 1;
		}
		else if(digitalRead(A2) == 0 && flag == 0)
		{
			period = period*2;
			xTimerChangePeriod(timer1, pdMS_TO_TICKS(period), 0);
			flag = 1;
		}
		else if(digitalRead(A3) == 0 && flag == 0)
		{
			period = period/2;
			xTimerChangePeriod(timer1, pdMS_TO_TICKS(period), 0);
			flag = 1;
		}
		else if(digitalRead(A0) == 1 && digitalRead(A1) == 1 && digitalRead(A2) == 1 && digitalRead(A3) == 1)
		{
			flag = 0;
		}
	}
}

void led_toggle (TimerHandle_t timer)
{
	if(flag1 == 0)
	{
		digitalWrite(A4, HIGH);
		flag1 = 1;
	}
	else if(flag1 == 1)
	{
		digitalWrite(A4, LOW);
		flag1 = 0;
	}
}

