
#include <Arduino.h>
#include <avr/io.h>
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

#define STACK_SIZE 200

SemaphoreHandle_t semaphoreBinary = xSemaphoreCreateBinary();
TickType_t currentTime1;
TickType_t currentTime2;
TickType_t currentTime3;

void myDelay(int ms) {
	for(int i = 0; i< ms; i++){
		delayMicroseconds(1000);
	}
}

void task1(void *p) {
	while(1){
		if(xSemaphoreTake(semaphoreBinary, (TickType_t) 1) == pdTRUE){
			unsigned int count = 0;
			digitalWrite(9, HIGH);
			while(count < 3000){
				digitalWrite(6, HIGH);
				myDelay(50);
				digitalWrite(6, LOW);
				myDelay(50);
				count += 100;
			}
			xSemaphoreGive(semaphoreBinary);
			digitalWrite(9, LOW);
			vTaskDelayUntil(&currentTime1, 10000);
		}
	}
}

void task2(void *p) {
	while(1){
		unsigned int count = 0;
		while(count < 4000){
			digitalWrite(7, HIGH);
			myDelay(50);
			digitalWrite(7, LOW);
			myDelay(50);
			count += 100;
		}
		vTaskDelayUntil(&currentTime2, 15000);
	}
}

void task3(void *p) {
	while(1){
		if(xSemaphoreTake(semaphoreBinary, (TickType_t) 1) == pdTRUE){
			unsigned int count = 0;
			digitalWrite(9, HIGH);
			while(count < 10000){
				digitalWrite(8, HIGH);
				myDelay(50);
				digitalWrite(8, LOW);
				myDelay(50);
				count += 100;
			}
			xSemaphoreGive(semaphoreBinary);
			digitalWrite(9, LOW);
			vTaskDelayUntil(&currentTime3, 35000);
		}
	}
}

void setup() {
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);
	pinMode(8, OUTPUT);
	pinMode(9, OUTPUT);
	xSemaphoreGive(semaphoreBinary);
	currentTime1 = xTaskGetTickCount();
	currentTime2 = xTaskGetTickCount();
	currentTime3 = xTaskGetTickCount();
}

void loop() {
	xTaskCreate(task1,"Task1",STACK_SIZE,NULL,3,NULL);
	xTaskCreate(task2,"Task2",STACK_SIZE,NULL,2,NULL);
	xTaskCreate(task3,"Task3",STACK_SIZE,NULL,1,NULL);
	vTaskStartScheduler();
}


