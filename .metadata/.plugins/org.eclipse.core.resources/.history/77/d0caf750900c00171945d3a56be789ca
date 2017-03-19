
/////////qn 5
#include <Arduino.h>
#include <avr/io.h>
#include <FreeRTOS.h>
#include <task.h>

#define STACK_SIZE   200
#define LED_PIN_6      6
#define LED_PIN_7      7
#define LED_PIN_8      8
#define LED_PIN_9      9

int count = 0;

void myDelay(int ms) {
	for (int i = 0; i < ms; i++) {
		delayMicroseconds(1000);
	}
}

void task1() {
	count = 0;
	while (count < 1500) {
		digitalWrite(LED_PIN_6, HIGH);
		myDelay(50);
		digitalWrite(LED_PIN_6, LOW);
		myDelay(50);
		count +=100;
	}
}

void task2(){
	count = 0;
	while (count < 2500) {
		digitalWrite(LED_PIN_7, HIGH);
		myDelay(50);
		digitalWrite(LED_PIN_7, LOW);
		myDelay(50);
		count +=100;
	}
}

void task3(){
	count = 0;
	while (count < 1700) {
		digitalWrite(LED_PIN_8, HIGH);
		myDelay(50);
		digitalWrite(LED_PIN_8, LOW);
		myDelay(50);
		count +=100;
	}
}

void task4(){
	count = 0;
	while (count < 700) {
		digitalWrite(LED_PIN_9, HIGH);
		myDelay(50);
		digitalWrite(LED_PIN_9, LOW);
		myDelay(50);
		count +=100;
	}
}

void setup(){
		pinMode(LED_PIN_6, OUTPUT);
		pinMode(LED_PIN_7, OUTPUT);
		pinMode(LED_PIN_8, OUTPUT);
	pinMode(LED_PIN_9, OUTPUT);
}

void taskall(void *p){
	TickType_t currentTime = 0;

    task1();
    task2();
    //delay
    currentTime = xTaskGetTickCount();
    vTaskDelayUntil( &currentTime, 1000 );

    task1();
    task3();
    task4();
    //delay
    currentTime = xTaskGetTickCount();
    vTaskDelayUntil( &currentTime, 1100 );


    task1();
    task2();
    //delay
    currentTime = xTaskGetTickCount();
    vTaskDelayUntil( &currentTime, 1000 );

    task1();
    task3();
    //delay
    currentTime = xTaskGetTickCount();
    vTaskDelayUntil( &currentTime, 1800 );
}

void loop() {
	xTaskCreate(taskall,       // Pointer to the task entry function
			"TaskAll",         // Task name
			STACK_SIZE,      // Stack size
			NULL,            // Pointer that will be used as parameter
			1,               // Task priority
			NULL);           // Used to pass back a handle by which the created task can be referenced.
	vTaskStartScheduler();
}
