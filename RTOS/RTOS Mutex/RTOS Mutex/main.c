#define F_CPU 8000000UL

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "Gpio.h"
#include "Serial.h"

SemaphoreHandle_t mutex = NULL;

void print_tarek(void *ptr);
TaskHandle_t tarek;

void print_omar(void *ptr);
TaskHandle_t omar;

int x=0,y=0;
int main(void)
{
	pinMode(A0,INPUT_PULLUP);
	Serial_begin(9600);
	
	xTaskCreate(print_tarek,"TAREK",150,NULL,1,tarek);
	xTaskCreate(print_omar,"LASHEEN",150,NULL,2,omar);
	mutex = xSemaphoreCreateMutex();

	vTaskStartScheduler();
	
}

void print_tarek(void *ptr)
{
	
	while (1)
	{
		xSemaphoreTake(mutex, portMAX_DELAY);
		//taskENTER_CRITICAL();
		if(digitalRead(A0) == 0)
		{
			x++;
			y++;
			if(x==y && x==100)
			{
			x=0;
			y=0;
			}
			
			Serial_print((int*)&x,INT);
			Serial_print("...",STRING);
			Serial_print((int*)&y,INT);
			Serial_print("...",STRING);
		}
		//taskEXIT_CRITICAL();
		xSemaphoreGive(mutex);
	}
}

void print_omar(void *ptr)
{
	while (1)
	{
		xSemaphoreTake(mutex, portMAX_DELAY);
		if(x != y)
		{
			Serial_print("...shared Data problem...",STRING);
		}
		xSemaphoreGive(mutex);
       vTaskDelay(5);
		
	}
}