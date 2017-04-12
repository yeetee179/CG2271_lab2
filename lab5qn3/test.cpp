#include <Arduino.h>
#include <avr/io.h>
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <queue.h>
#define STACK_SIZE 200

QueueHandle_t queue = xQueueCreate(2, 4);

void serialPrint(void *p) {
	while (1) {
		int taskNum;
		if(xQueueReceive( queue, &taskNum, ( TickType_t ) 10 )){/////////////added if here/////////
			Serial.print("Task ");
			Serial.println(taskNum);
		}
	}
}

void task1and2(void *p) {
	while (1) {
		int taskNum = (int) p;
		xQueueSend( queue,( void * ) &taskNum, ( TickType_t ) 10 );
		vTaskDelay(1);
	}
}

void setup() {
	Serial.begin(115200);
}

void loop() {
	/* create two tasks one with higher priority than the other */
	xTaskCreate(task1and2, "Task1", STACK_SIZE, (void * ) 1, 1, NULL);
	xTaskCreate(task1and2, "Task2", STACK_SIZE, (void * ) 2, 2, NULL);
	xTaskCreate(serialPrint, "SerialPrint", STACK_SIZE, NULL, 3, NULL);
	/* start scheduler */
	vTaskStartScheduler();
}

