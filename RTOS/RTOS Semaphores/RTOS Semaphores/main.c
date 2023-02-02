#define F_CPU 8000000UL

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "Gpio.h"
#include "Serial.h"

uint8_t flag = 0;
uint8_t flag1 = 0;

xSemaphoreHandle led  = NULL;

void read_button(void* ptr);
TaskHandle_t read_handle = NULL;

void led_toggle(void* ptr);
TaskHandle_t led_handle = NULL;

int main(void)
{
	pinMode(A0, INPUT_PULLUP);
	pinMode(A1, OUTPUT);
	
	xTaskCreate(read_button, "omar", 100, NULL, 1, read_handle);
	xTaskCreate(led_toggle, "ahmed", 100, NULL, 2, led_handle);
	
	vTaskStartScheduler();
}

void read_button(void* ptr)
{
	while(1)
	{	
		if(digitalRead(A0) == 0 && flag1==0)
		{
			flag1 = 1;
			xSemaphoreGive(led);
		}
		else if(digitalRead(A0) == 1 && flag1==1)
		{
				flag1 = 0;
		}
	}
}

void led_toggle(void* ptr)
{
	led = xSemaphoreCreateBinary();
	while(1)
	{
		xSemaphoreTake(led, portMAX_DELAY);
		
		if(flag == 0)
		{
			digitalWrite(A1, HIGH);
			flag = 1;
		}
		else if(flag == 1)
		{
			digitalWrite(A1, LOW);
			flag = 0;
		}
	}
}

