#include <Arduino.h>
#include <avr/io.h>
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

#define STACK_SIZE 200

SemaphoreHandle_t semaphoreBinary = xSemaphoreCreateBinary();

QueueHandle_t queue = xQueueCreate(10, sizeof(int));;

void Consumer(void *p)
{
	TickType_t currentTime = xTaskGetTickCount();
	while(1){
		int potentioValue;
		if(xQueueReceive(queue, &potentioValue, (TickType_t) 0)){
			Serial.println(potentioValue);
		}
		vTaskDelayUntil(&currentTime, 5000);
	}
}

void ProducerISR(){
	int potentioValue;
	static unsigned long previous_Interrupt_time = 0;
	unsigned long current_interrupt_time = millis();

	if(current_interrupt_time - previous_Interrupt_time > 100){
		potentioValue = analogRead(0);
		xQueueSendToBack(queue, &potentioValue, (TickType_t) 5000);

		previous_Interrupt_time = current_interrupt_time;
	}
}

void setup() {
	attachInterrupt(digitalPinToInterrupt(3), ProducerISR, RISING);
	Serial.begin(115200);
}

void loop() {
	xTaskCreate(Consumer, "Consumer", STACK_SIZE, NULL, 1, NULL);
	vTaskStartScheduler();
}

