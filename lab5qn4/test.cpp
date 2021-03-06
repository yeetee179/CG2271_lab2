#include <Arduino.h>
#include <avr/io.h>
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <queue.h>

#define STACK_SIZE 200

xSemaphoreHandle semaphore0 = xSemaphoreCreateBinary();
xSemaphoreHandle semaphore1 = xSemaphoreCreateBinary();

void int0task(void *p){
	while(1){
		if(xSemaphoreTake( semaphore0, ( TickType_t ) 0)){
			for(int i=0; i<5; i++){
				digitalWrite(7, HIGH); // Set digital I/O pin to a 1
				delay(125); // Delay
				digitalWrite(7, LOW); // Set digital I/O pin to a 0
				delay(125);
			}
		}
		else{
			vTaskDelay(1);
		}
	}
}

// Flashes LED at pin 6: 5 times at 2HZ
void int1task(void * p){
	while (1){
		if( xSemaphoreTake( semaphore1, ( TickType_t ) 0)){
			for(int i=0; i<5; i++){
				digitalWrite(6, HIGH); // Set digital I/O pin to a 1
				delay(250); // Delay
				digitalWrite(6, LOW); // Set digital I/O pin to a 0
				delay(250);
			}
		}
		else{
			vTaskDelay(1);
		}
	}
}

void int0ISR(){
	unsigned long current_interrupt_time = millis();
	static unsigned long previous_Interrupt_time = 0;
	if((current_interrupt_time - previous_Interrupt_time) > 200){
		xSemaphoreGiveFromISR(semaphore0, NULL);
	}
	previous_Interrupt_time = current_interrupt_time;
}


void int1ISR(){
	static BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	unsigned long current_interrupt_time = millis();
	static unsigned long previous_Interrupt_time = 0;
	if((current_interrupt_time - previous_Interrupt_time) > 200){
		xSemaphoreGiveFromISR(semaphore1, &xHigherPriorityTaskWoken);
	}
	previous_Interrupt_time = current_interrupt_time;
}

void setup() {
	attachInterrupt(digitalPinToInterrupt(3), int0ISR, FALLING);
	attachInterrupt(digitalPinToInterrupt(2), int1ISR, FALLING);
	pinMode(7, OUTPUT);
	pinMode(6, OUTPUT);
}

void loop() {
	xTaskCreate(int1task, "Task1", STACK_SIZE, NULL, 1, NULL);
	xTaskCreate(int0task, "Task2", STACK_SIZE, NULL, 2, NULL);
	vTaskStartScheduler();
}

