#define F_CPU 8000000UL

#include "Gpio.h"
#include "Serial.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "mpu_wrappers.h"

uint8_t pins[4] = {A1, A2, A3, A4};
char *colors[4] = {"RED", "YELLOW", "BLUE", "GREEN"};

QueueHandle_t queue1;
QueueHandle_t queue2;

void recieve_button(void* ptr);
TaskHandle_t task1;

void led_output(void* ptr);
TaskHandle_t task2;

int main(void)
{
	Serial_begin(9600);
	
	pinMode(A0,INPUT_PULLUP);
	pinMode(A1,OUTPUT);
	pinMode(A2,OUTPUT);
	pinMode(A3,OUTPUT);
	pinMode(A4,OUTPUT);
	
	queue1 = xQueueCreate(1, sizeof(pins));
	queue2 = xQueueCreate(1, sizeof(colors));
	
	xTaskCreate(recieve_button, "read_button" , 250, NULL, 2, task1);
	xTaskCreate(led_output, "output_led" , 250, NULL, 1, task2);
	
	vTaskStartScheduler();
}

void vApplicationIdleHook(void*ptr)
{
	while(1)
	{
		
	}
}

void recieve_button(void* ptr)
{
	uint8_t counter = 0;
	uint8_t flag = 0;
	
	while(1)
	{
		if (digitalRead(A0) == 0)
		{
			if(queue1 != NULL)
			{
				xQueueOverwrite(queue1, &pins[counter]);
				
				if (queue2 != NULL)
				{
					xQueueOverwrite(queue2, &colors[counter]);
					
					if(counter < 3 && flag == 0)
					{
						counter++;
					}
					else if (counter >= 3 && flag == 0)
					{
						counter = 0;
					}
				}
				flag=1;
			}
		}
		
		else if(digitalRead(A0) == 1)
		{
			flag=0;
		}
		vTaskSuspend(NULL);
	}
}

void led_output(void* ptr)
{
	uint8_t value=0;
	char string_values[10];
	
	while(1)
	{
		if(xQueuePeek(queue1, &value, 1) == pdPASS)
		{
			if (xQueuePeek(queue2, string_values, 1) == pdPASS)
			{
				if(value == A1)
				{
					digitalWrite(A1, HIGH);
					digitalWrite(A2, LOW);
					digitalWrite(A3, LOW);
					digitalWrite(A4, LOW);
					Serial_print("...RED...", STRING);
				}
				else if(value == A2)
				{
					digitalWrite(A2, HIGH);
					digitalWrite(A1, LOW);
					digitalWrite(A3, LOW);
					digitalWrite(A4, LOW);
					Serial_print("...YELLOW...", STRING);
				}
				else if(value == A3)
				{
					digitalWrite(A3, HIGH);
					digitalWrite(A1, LOW);
					digitalWrite(A2, LOW);
					digitalWrite(A4, LOW);
					Serial_print("...BLUE...", STRING);
				}
				else if(value == A4)
				{
					digitalWrite(A4, HIGH);
					digitalWrite(A1, LOW);
					digitalWrite(A2, LOW);
					digitalWrite(A3, LOW);
					Serial_print("...GREEN...", STRING);
				}
				else
				{
					  digitalWrite(A1, LOW);
					  digitalWrite(A2, LOW);
					  digitalWrite(A3, LOW);
					  digitalWrite(A4, LOW);
				}
			}
		}
		vTaskPrioritySet(NULL, 3);
		vTaskResume(task1);
		vTaskPrioritySet(NULL, 1);
	}
}