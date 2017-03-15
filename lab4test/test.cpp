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
//		for(int i =0; i<10; i++){
			digitalWrite(LED_PIN, HIGH);
			vTaskDelay( counter );
			digitalWrite(LED_PIN, LOW);
			vTaskDelay( 20 - counter );
//		}
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

