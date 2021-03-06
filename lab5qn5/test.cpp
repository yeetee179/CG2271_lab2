#include <Arduino.h>
#include <avr/io.h>
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <queue.h>

#define STACK_SIZE 200

xSemaphoreHandle semaphoreBinary = xSemaphoreCreateBinary();
xSemaphoreHandle semaphoreCounting = xSemaphoreCreateCounting( (UBaseType_t)4,(UBaseType_t)  4 );
xSemaphoreHandle semaphoreMutex = xSemaphoreCreateMutex();

int buf[4];
int in=0, out = 0;

void Producer(void *p){
	while(1){
		if(xSemaphoreTake( semaphoreBinary,(TickType_t) 0)){
			if (xSemaphoreTake( semaphoreCounting,(TickType_t) 0)){
				if(xSemaphoreTake( semaphoreMutex,(TickType_t) 0)){
					buf[in] = analogRead(0);
					in = (in + 1) % 4;
					xSemaphoreGive( semaphoreMutex);
				}
				else {
					xSemaphoreGive( semaphoreCounting);
				}
			}
			else {
				xSemaphoreGive(semaphoreBinary);
			}
		}
		else{
			vTaskDelay(1);
		}
	}
}

void Consumer(void *p){
	TickType_t currentTime = xTaskGetTickCount();
	while (1){
		if(xSemaphoreGive(semaphoreCounting)){
			if (xSemaphoreTake( semaphoreMutex, (TickType_t) 0)){
				Serial.println(buf[out]);
				out = (out + 1) % 4;
				xSemaphoreGive( semaphoreMutex);
			}
			else{
				xSemaphoreTake(semaphoreCounting,(TickType_t) 0);
			}
		}
		vTaskDelayUntil(&currentTime, 5000);
	}
}



void ProducerISR(){
	unsigned long current_interrupt_time = millis();
	static unsigned long previous_Interrupt_time = 0;
	static BaseType_t xHigherPriorityTaskWoken;

	xHigherPriorityTaskWoken = pdFALSE;

	if((current_interrupt_time - previous_Interrupt_time) > 200){
		xSemaphoreGiveFromISR(semaphoreBinary, &xHigherPriorityTaskWoken);
	}
	previous_Interrupt_time = current_interrupt_time;

	if (xHigherPriorityTaskWoken == pdTRUE){
		taskYIELD();
	}

}

void setup() {
	Serial.begin(115200);
	attachInterrupt(digitalPinToInterrupt(3), ProducerISR, FALLING);
}

void loop() {
	xTaskCreate(Producer, "Producer", STACK_SIZE, NULL, 1, NULL);
	xTaskCreate(Consumer, "Consumer", STACK_SIZE, NULL, 1, NULL);
	vTaskStartScheduler();
}
