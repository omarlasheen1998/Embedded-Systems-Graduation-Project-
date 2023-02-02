#define F_CPU 8000000UL

#include <util/delay.h>
#include "FreeRTOS.h"
#include "projdefs.h"
#include "task.h"
#include "mpu_wrappers.h"
#include "Gpio.h"
#include "lcd.h"
#include "Serial.h"

TaskHandle_t omar = NULL;
void led1_blink(void *ptr);

TaskHandle_t lasheen = NULL;
void led2_blink(void *ptr);

TaskHandle_t lcd_print = NULL;
void lcd_task_status(void *ptr);

int main(void)
{
	Serial_begin(9600);
	xTaskCreate(led1_blink, "Ahmed", 50, NULL, 2, &omar);
	xTaskCreate(led2_blink, "Tarek", 50, NULL, 1, &lasheen);
	xTaskCreate(lcd_task_status, "lcd", 150, NULL, 3, &lcd_print);
	vTaskStartScheduler();
}

void led1_blink(void *ptr)
{
	char x=0;
	pinMode(A0, OUTPUT);
	const TickType_t start_count_1 = xTaskGetTickCount();
	while(1)
	{
		if(x==0)
		{
			digitalWrite(A0, HIGH);
			x=1;
		}
		else
		{
			digitalWrite(A0, LOW);
			x=0;
		}
		vTaskDelayUntil(&start_count_1, pdMS_TO_TICKS(100));
		//vTaskSuspend(NULL);
	}
}

void led2_blink(void *ptr)
{
	char x=0;
	pinMode(A1, OUTPUT);
	const TickType_t start_count_2 = xTaskGetTickCount();
	while(1)
	{
		if(x==0)
		{
			digitalWrite(A1, HIGH);
			x=1;
		}
		else
		{
			digitalWrite(A1, LOW);
			x=0;
		}
		vTaskDelayUntil(&start_count_2, pdMS_TO_TICKS(500));
		//vTaskResume(omar);
	}
}

void lcd_task_status(void *ptr)
{
	TaskStatus_t task_1_details;
	TaskStatus_t task_2_details;
	TaskStatus_t task_3_details;
	
	const TickType_t start_count_3 = xTaskGetTickCount();
	
	while(1)
	{
		vTaskGetInfo(omar, &task_1_details, pdTRUE, eInvalid);
		vTaskGetInfo(lasheen, &task_2_details, pdTRUE, eInvalid);
		vTaskGetInfo(NULL, &task_3_details, pdTRUE, eInvalid);
		
		Serial_print("...Task_1: ", STRING);
		Serial_print((int*)&task_1_details.usStackHighWaterMark,INT);
		Serial_print("...", STRING);
	    
		if (task_1_details.eCurrentState == eRunning)
		{
			Serial_print("...Task 1 is running...", STRING);
		}
		else if (task_1_details.eCurrentState == eReady)
		{
			Serial_print("...Task 1 is ready...", STRING); //for testing task starvation
		}
		else if (task_1_details.eCurrentState == eBlocked)
		{
			Serial_print("...Task 1 is blocked...", STRING);
		}
		else if (task_1_details.eCurrentState == eSuspended)
		{
			Serial_print("...Task 1 is suspended...", STRING);
		}
		else if (task_1_details.eCurrentState == eDeleted)
		{
			Serial_print("...Task 1 is deleted...", STRING);
		}
		
		Serial_print("...Task_2: ", STRING);
		Serial_print((int*)&task_2_details.usStackHighWaterMark,INT);
		Serial_print("...", STRING);
		if (task_2_details.eCurrentState == eRunning)
		{
			Serial_print("...Task 2 is running...", STRING);
		}
		else if (task_2_details.eCurrentState == eReady)
		{
			Serial_print("...Task 2 is ready...", STRING); //for testing task starvation
		}
		else if (task_2_details.eCurrentState == eBlocked)
		{
			Serial_print("...Task 2 is blocked...", STRING);
		}
		else if (task_2_details.eCurrentState == eSuspended)
		{
			Serial_print("...Task 2 is suspended...", STRING);
		}
		else if (task_2_details.eCurrentState == eDeleted)
		{
			Serial_print("...Task 2 is deleted...", STRING);
		}
		
		Serial_print("...Task_3: ", STRING);
		Serial_print((int*)&task_3_details.usStackHighWaterMark,INT);
		Serial_print(" ...", STRING);
		
		if (task_3_details.eCurrentState == eRunning)
		{
			Serial_print("...Task 3 is running...", STRING);
		}
		else if (task_3_details.eCurrentState == eReady)
		{
			Serial_print("...Task 3 is ready...", STRING); //for testing task starvation
		}
		else if (task_3_details.eCurrentState == eBlocked)
		{
			Serial_print("...Task 3 is blocked...", STRING);
		}
		else if (task_3_details.eCurrentState == eSuspended)
		{
			Serial_print("...Task 3 is suspended...", STRING);
		}
		else if (task_3_details.eCurrentState == eDeleted)
		{
			Serial_print("...Task 3 is deleted...", STRING);
		}
			
		vTaskDelayUntil(&start_count_3, pdMS_TO_TICKS(1000));
	}
}