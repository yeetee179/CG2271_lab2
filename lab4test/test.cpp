///*
// * test.cpp
// *
// *  Created on: 8 Mar 2017
// *      Author: user-pc
// */
///////qn 2D
//#include <Arduino.h>
//#include <avr/io.h>
//#include <FreeRTOS.h>
//#include <task.h>
//
//#define STACK_SIZE   200
//#define LED_PIN      6
//
//int tickCount = 0;
//
//
//void task1(void *p)
//{
//	for (;;) {
//	  digitalWrite(LED_PIN, HIGH);
//	  vTaskDelay( 1000 );
//	  digitalWrite(LED_PIN, LOW);
//	  vTaskDelay( 1000 );
//	}
//}
//
//void setup()
//{
//	pinMode(LED_PIN, OUTPUT);
//}
//
//void loop() {
//	xTaskCreate(task1,           // Pointer to the task entry function
//		     "Task1",         // Task name
//		     STACK_SIZE,      // Stack size
//		     NULL,            // Pointer that will be used as parameter
//		     1,               // Task priority
//		    NULL);           // Used to pass back a handle by which the created task can be referenced.
//	vTaskStartScheduler();
//}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////qn 2E
//#include <Arduino.h>
//#include <avr/io.h>
//#include <FreeRTOS.h>
//#include <task.h>
//
//#define STACK_SIZE   200
//#define LED_PIN_6      6
//#define LED_PIN_7      7
//#define LED_PIN_8      8
//
//void task1(void *p)
//{
//	for (;;) {
//	  digitalWrite(LED_PIN_6, HIGH);
//	  vTaskDelay( 1500 );
//	  digitalWrite(LED_PIN_6, LOW);
//	  vTaskDelay( 1500 );
//	}
//}
//
//void task2(void *p)
//{
//	for (;;) {
//	  digitalWrite(LED_PIN_7, HIGH);
//	  vTaskDelay( 2000 );
//	  digitalWrite(LED_PIN_7, LOW);
//	  vTaskDelay( 2000 );
//	}
//}
//
//void task3(void *p)
//{
//	for (;;) {
//	  digitalWrite(LED_PIN_8, HIGH);
//	  vTaskDelay( 4000 );
//	  digitalWrite(LED_PIN_8, LOW);
//	  vTaskDelay( 4000 );
//	}
//}
//void setup()
//{
//	pinMode(LED_PIN_6, OUTPUT);
//	pinMode(LED_PIN_7, OUTPUT);
//	pinMode(LED_PIN_8, OUTPUT);
//}
//
//void loop() {
//	xTaskCreate(task1,       // Pointer to the task entry function
//			"Task1",         // Task name
//			STACK_SIZE,      // Stack size
//			NULL,            // Pointer that will be used as parameter
//			3,               // Task priority
//			NULL);           // Used to pass back a handle by which the created task can be referenced.
//	xTaskCreate(task2,       // Pointer to the task entry function
//			"Task2",         // Task name
//			STACK_SIZE,      // Stack size
//			NULL,            // Pointer that will be used as parameter
//			2,               // Task priority
//			NULL);           // Used to pass back a handle by which the created task can be referenced.
//	xTaskCreate(task3,       // Pointer to the task entry function
//			"Task3",         // Task name
//			STACK_SIZE,      // Stack size
//			NULL,            // Pointer that will be used as parameter
//			1,               // Task priority
//			NULL);           // Used to pass back a handle by which the created task can be referenced.
//	vTaskStartScheduler();
//}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////qn 3
//#include <Arduino.h>
//#include <avr/io.h>
//#include <FreeRTOS.h>
//#include <task.h>
//
//#define STACK_SIZE   200
//#define LED_PIN      6
//
//void task1(void *p)
//{
//	int counter = 1;
//
//	for (;;) {
//		for(int i =0; i<5; i++){
//			digitalWrite(LED_PIN, HIGH);
//			vTaskDelay( counter );
//			digitalWrite(LED_PIN, LOW);
//			vTaskDelay( 20 - counter );
//		}
//		counter++;
//		if (counter == 20)
//			counter = 1;
//	}
//}
//
//void setup()
//{
//	pinMode(LED_PIN, OUTPUT);
//}
//
//void loop() {
//	xTaskCreate(task1,           // Pointer to the task entry function
//		     "Task1",         // Task name
//		     STACK_SIZE,      // Stack size
//		     NULL,            // Pointer that will be used as parameter
//		     1,               // Task priority
//		    NULL);           // Used to pass back a handle by which the created task can be referenced.
//	vTaskStartScheduler();
//}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////qn 4 a
//#include <Arduino.h>
//#include <avr/io.h>
//#include <FreeRTOS.h>
//#include <task.h>
//
//#define STACK_SIZE   200
//#define LED_PIN_6      6
//#define LED_PIN_7      7
//#define LED_PIN_8      8
//#define LED_PIN_9      9
//
//const TickType_t task1TimeInterval = 5000;
//const TickType_t task2TimeInterval = 10000;
//const TickType_t task3TimeInterval = 10000;
//const TickType_t task4TimeInterval = 20000;
//
//
//void myDelay(int ms) {
//	for (int i = 0; i < ms; i++) {
//		delayMicroseconds(1000);
//	}
//}
//
//void task1(void *p) {
//	static TickType_t currentTime1 = 0;
//	for (;;) {
//		currentTime1 = xTaskGetTickCount();
//		int count = 0;
//		while (count < 1500) {
//			digitalWrite(LED_PIN_6, HIGH);
//			myDelay(50);
//			digitalWrite(LED_PIN_6, LOW);
//			myDelay(50);
//			count +=100;
//		}
//		vTaskDelayUntil( &currentTime1, task1TimeInterval );
//	}
//
//}
//
//void task2(void *p)
//{
//	static TickType_t currentTime2 = 0;
//	for (;;) {
//		currentTime2 = xTaskGetTickCount();
//		int count = 0;
//		while (count < 2500) {
//			digitalWrite(LED_PIN_7, HIGH);
//			myDelay(50);
//			digitalWrite(LED_PIN_7, LOW);
//			myDelay(50);
//			count +=100;
//		}
//		vTaskDelayUntil( &currentTime2, task2TimeInterval );
//	}
//}
//
//void task3(void *p)
//{
//	static TickType_t currentTime3 = 0;
//	for (;;) {
//		currentTime3 = xTaskGetTickCount();
//		int count = 0;
//		while (count < 1700) {
//			digitalWrite(LED_PIN_8, HIGH);
//			myDelay(50);
//			digitalWrite(LED_PIN_8, LOW);
//			myDelay(50);
//			count +=100;
//		}
//		vTaskDelayUntil( &currentTime3, task3TimeInterval );
//	}
//}
//
//void task4(void *p)
//{
//	static TickType_t currentTime4 = 0;
//	for (;;) {
//		int count = 0;
//		currentTime4 = xTaskGetTickCount();
//		while (count < 700) {
//			digitalWrite(LED_PIN_9, HIGH);
//			myDelay(50);
//			digitalWrite(LED_PIN_9, LOW);
//			myDelay(50);
//			count +=100;
//		}
//		vTaskDelayUntil( &currentTime4, task4TimeInterval );
//	}
//}
//
//void setup()
//{
//	pinMode(LED_PIN_6, OUTPUT);
//	pinMode(LED_PIN_7, OUTPUT);
//	pinMode(LED_PIN_8, OUTPUT);
//	pinMode(LED_PIN_9, OUTPUT);
//}
//
//void loop() {
//	xTaskCreate(task1,       // Pointer to the task entry function
//			"Task1",         // Task name
//			STACK_SIZE,      // Stack size
//			NULL,            // Pointer that will be used as parameter
//			4,               // Task priority
//			NULL);           // Used to pass back a handle by which the created task can be referenced.
//	xTaskCreate(task2,       // Pointer to the task entry function
//			"Task2",         // Task name
//			STACK_SIZE,      // Stack size
//			NULL,            // Pointer that will be used as parameter
//			3,               // Task priority
//			NULL);           // Used to pass back a handle by which the created task can be referenced.
//	xTaskCreate(task3,       // Pointer to the task entry function
//			"Task3",         // Task name
//			STACK_SIZE,      // Stack size
//			NULL,            // Pointer that will be used as parameter
//			2,               // Task priority
//			NULL);           // Used to pass back a handle by which the created task can be referenced.
//	xTaskCreate(task4,       // Pointer to the task entry function
//			"Task4",         // Task name
//			STACK_SIZE,      // Stack size
//			NULL,            // Pointer that will be used as parameter
//			1,               // Task priority
//			NULL);
//	vTaskStartScheduler();
//}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////qn 4 c
//#include <Arduino.h>
//#include <avr/io.h>
//#include <FreeRTOS.h>
//#include <task.h>
//
//#define STACK_SIZE   200
//#define LED_PIN_6      6
//#define LED_PIN_7      7
//#define LED_PIN_8      8
//#define LED_PIN_9      9
//
//const TickType_t task1TimeInterval = 5000;
//const TickType_t task2TimeInterval = 10000;
//const TickType_t task3TimeInterval = 10000;
//const TickType_t task4TimeInterval = 20000;
//
//
//void myDelay(int ms) {
//	for (int i = 0; i < ms; i++) {
//		delayMicroseconds(1000);
//	}
//}
//
//void task1(void *p) {
//	static TickType_t currentTime1 = 0;
//	for (;;) {
//		currentTime1 = xTaskGetTickCount();
//		int count = 0;
//		while (count < 1500) {
//			digitalWrite(LED_PIN_6, HIGH);
//			myDelay(50);
//			digitalWrite(LED_PIN_6, LOW);
//			myDelay(50);
//			count +=100;
//		}
//		vTaskDelayUntil( &currentTime1, task1TimeInterval );
//	}
//
//}
//
//void task2(void *p)
//{
//	static TickType_t currentTime2 = 0;
//	for (;;) {
//		currentTime2 = xTaskGetTickCount();
//		int count = 0;
//		while (count < 2500) {
//			digitalWrite(LED_PIN_7, HIGH);
//			myDelay(50);
//			digitalWrite(LED_PIN_7, LOW);
//			myDelay(50);
//			count +=100;
//		}
//		vTaskDelayUntil( &currentTime2, task2TimeInterval );
//	}
//}
//
//void task3(void *p)
//{
//	static TickType_t currentTime3 = 0;
//	for (;;) {
//		currentTime3 = xTaskGetTickCount();
//		int count = 0;
//		while (count < 1700) {
//			digitalWrite(LED_PIN_8, HIGH);
//			myDelay(50);
//			digitalWrite(LED_PIN_8, LOW);
//			myDelay(50);
//			count +=100;
//		}
//		vTaskDelayUntil( &currentTime3, task3TimeInterval );
//	}
//}
//
//void task4(void *p)
//{
//	static TickType_t currentTime4 = 0;
//	for (;;) {
//		int count = 0;
//		currentTime4 = xTaskGetTickCount();
//		while (count < 700) {
//			digitalWrite(LED_PIN_9, HIGH);
//			myDelay(50);
//			digitalWrite(LED_PIN_9, LOW);
//			myDelay(50);
//			count +=100;
//		}
//		vTaskDelayUntil( &currentTime4, task4TimeInterval );
//	}
//}
//
//void setup()
//{
//	pinMode(LED_PIN_6, OUTPUT);
//	pinMode(LED_PIN_7, OUTPUT);
//	pinMode(LED_PIN_8, OUTPUT);
//	pinMode(LED_PIN_9, OUTPUT);
//}
//
//void loop() {
//	xTaskCreate(task1,       // Pointer to the task entry function
//			"Task1",         // Task name
//			STACK_SIZE,      // Stack size
//			NULL,            // Pointer that will be used as parameter
//			3,               // Task priority
//			NULL);           // Used to pass back a handle by which the created task can be referenced.
//	xTaskCreate(task2,       // Pointer to the task entry function
//			"Task2",         // Task name
//			STACK_SIZE,      // Stack size
//			NULL,            // Pointer that will be used as parameter
//			2,               // Task priority
//			NULL);           // Used to pass back a handle by which the created task can be referenced.
//	xTaskCreate(task3,       // Pointer to the task entry function
//			"Task3",         // Task name
//			STACK_SIZE,      // Stack size
//			NULL,            // Pointer that will be used as parameter
//			2,               // Task priority
//			NULL);           // Used to pass back a handle by which the created task can be referenced.
//	xTaskCreate(task4,       // Pointer to the task entry function
//			"Task4",         // Task name
//			STACK_SIZE,      // Stack size
//			NULL,            // Pointer that will be used as parameter
//			1,               // Task priority
//			NULL);
//	vTaskStartScheduler();
//}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
