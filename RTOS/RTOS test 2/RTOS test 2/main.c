#define F_CPU 8000000UL

#include "Gpio.h"
#include "Serial.h"
#include "FreeRTOS.h"
#include "task.h"

int x = 0;
int y = 0;

void task_1 (void *ptr);
TaskHandle_t first_task;

void task_2 (void *ptr);
TaskHandle_t second_task;


int main(void)
{
	Serial_begin(9600);
	xTaskCreate(task_1, "task_omar", 50, NULL, 1, first_task);
	xTaskCreate(task_2, "task_lasheen", 100, NULL, 2, second_task);
	vTaskStartScheduler();
}

void task_1 (void *ptr)
{
	while(1)
	{
		taskENTER_CRITICAL();
		x++;
		y++;
		taskEXIT_CRITICAL();
	}
}

void task_2 (void *ptr)
{
	while(1)
	{
		if(x != y)
		{
			Serial_print("...Shared data problem...",STRING);
		}
		else
		{
			Serial_print("...X equal Y...",STRING);	
		}
		
		vTaskDelay(50);
	}
}