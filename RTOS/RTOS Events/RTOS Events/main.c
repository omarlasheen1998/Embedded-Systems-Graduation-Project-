#define F_CPU 8000000UL

#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"

#include "Gpio.h"

void read_button(void* ptr);
TaskHandle_t task1 = NULL;

void toggle_led(void* ptr);
TaskHandle_t task2 = NULL;
EventGroupHandle_t xb;

int main(void)
{
	pinMode(A0,INPUT_PULLUP);
	pinMode(A1,OUTPUT);
	xTaskCreate(read_button, "Ahmed", 50, NULL, 1, task1);
	xTaskCreate(toggle_led, "Omar", 50, NULL, 2, task2);
	xb= xEventGroupCreate();
	
	vTaskStartScheduler();
}

void read_button(void* ptr)
{	
	uint8_t x1=0;

	while(1)
	{
	if(digitalRead(A0) == 0 && x1 == 0)
	{
	xEventGroupSetBits(xb,1<<0);
	xEventGroupSetBits(xb,1<<1);
	x1=1;
	
	}
	else if(digitalRead(A0) == 1 && x1==1)
	{
	xEventGroupClearBits(xb,1<<0);	
	x1=0;
	
	}	
	}
	
}

void toggle_led(void* ptr)
{
	uint8_t x=0;
	while(1)
	{
	
	xEventGroupWaitBits(xb,1<<0,pdTRUE,pdTRUE,portMAX_DELAY);
	if(x == 0)
	{
		digitalWrite(A1, HIGH);
		x = 1;	
	}
	else
	{
		digitalWrite(A1, LOW);
		x = 0;
	}
	
	}
}

