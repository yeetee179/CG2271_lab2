/////qn 3
#include <Arduino.h>
#include <avr/io.h>
#include <FreeRTOS.h>
#include <task.h>

#define STACK_SIZE   200
#define LED_PIN      6

void task1(void *p)
{
	int counter = 1;

	for (;;) {
		for(int i =0; i<5; i++){
			digitalWrite(LED_PIN, HIGH);
			vTaskDelay( counter );
			digitalWrite(LED_PIN, LOW);
			vTaskDelay( 20 - counter );
		}
		counter++;
		if (counter == 20)
			counter = 1;
	}
}

void setup()
{
	pinMode(LED_PIN, OUTPUT);
}

void loop() {
	xTaskCreate(task1,           // Pointer to the task entry function
		     "Task1",         // Task name
		     STACK_SIZE,      // Stack size
		     NULL,            // Pointer that will be used as parameter
		     1,               // Task priority
		    NULL);           // Used to pass back a handle by which the created task can be referenced.
	vTaskStartScheduler();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
