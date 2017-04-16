
#include <Arduino.h>
#include <avr/io.h>
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

#define STACK_SIZE 100

int desiredSpeedValue = 0;
int speedValue = 0;
int potentioValue = 0;
int distance = 0;
int redLedFlag = 0; //0 is no brake, 1 is brake
SemaphoreHandle_t speedValueSemaphore = xSemaphoreCreateBinary();
QueueHandle_t speedMessageQueue = xQueueCreate(10, sizeof(int));


//
//void myDelay(int ms) {
//	for(int i = 0; i< ms; i++){
//		delayMicroseconds(1000);
//	}


void CurrentSpeedTask(void *p) {

	while(1){
		TickType_t redLedTime;
		if (speedValue == 0 && xSemaphoreTake(speedValueSemaphore,1)){
			digitalWrite(6, LOW);
			digitalWrite(7, LOW);
			digitalWrite(8, LOW);
//			analogWrite(5,0);
			xSemaphoreGive(speedValueSemaphore);
//			xQueueSendToBack(speedMessageQueue, &speedValue, (TickType_t) 5);
			Serial.print("current speed is ");
			Serial.println(speedValue);
			Serial.println(distance);
		}
		if (speedValue == 1 && xSemaphoreTake(speedValueSemaphore,1)){
			digitalWrite(6, HIGH);
			digitalWrite(7, LOW);
			digitalWrite(8, LOW);
//			analogWrite(5, 5);
			xSemaphoreGive(speedValueSemaphore);
//			xQueueSendToBack(speedMessageQueue, &speedValue, (TickType_t) 5);
			Serial.print("current speed is ");
			Serial.println(speedValue);
			Serial.println(distance);
		}
		else if (speedValue == 2 && xSemaphoreTake(speedValueSemaphore,1)){
			digitalWrite(6, HIGH);
			digitalWrite(7, HIGH);
			digitalWrite(8, LOW);
//			analogWrite(5,20);
			xSemaphoreGive(speedValueSemaphore);
//			xQueueSendToBack(speedMessageQueue, &speedValue, (TickType_t) 5);
			Serial.print("current speed is ");
			Serial.println(speedValue);
			Serial.println(distance);
		}
		else if (speedValue == 3 && xSemaphoreTake(speedValueSemaphore,1)){
			digitalWrite(6, HIGH);
			digitalWrite(7, HIGH);
			digitalWrite(8, HIGH);
//			analogWrite(5, 55);
			xSemaphoreGive(speedValueSemaphore);
			Serial.print("current speed is ");
			Serial.println(speedValue);
			Serial.println(distance);
		}
		if (redLedFlag == 1){
			redLedTime = xTaskGetTickCount();
			digitalWrite(9, HIGH);
			vTaskDelayUntil(&redLedTime, 1000);
			digitalWrite(9, LOW);
			redLedFlag = 0;
		}
	}
}

void PotentiometerReadingTask(void *p) {
	int desiredSpeedValue = 0;
	while(1){
		TickType_t currentTime = xTaskGetTickCount();
		potentioValue = analogRead(0);
		if (potentioValue < 200){
			distance = 1; //distance = d
			if (speedValue > 0){
				speedValue = 0;
				redLedFlag = 1;
			}
		}
		else if (potentioValue > 200 && potentioValue < 400){
			distance = 2; //distance = 2d
			if (speedValue > 1){
				speedValue = 1;
				redLedFlag = 1;
			}
		}
		else if (potentioValue > 400 && potentioValue < 600){
			distance = 3; //distance = 3d
			if (speedValue > 2){
				speedValue = 2;
				redLedFlag = 1;
			}
		}
		else if (potentioValue > 600 && potentioValue < 800){
			distance = 4; //distance = 4d
			if (speedValue > 3){
				speedValue = 3;
				redLedFlag = 1;
			}
		}
		else if (potentioValue > 800){
			distance = 5; //distance = 4d
		}
		vTaskDelayUntil(&currentTime, 1000);
	}
}

void CalculationTask (void *p){
	while(1){
        if(speedValue == 3 && distance < 4){
        	if(xSemaphoreTake(speedValueSemaphore,1)){
        	speedValue = 0;
        	xSemaphoreGive(speedValueSemaphore);
        	}
        }
//        if(speedValue == 2 && distance < 3 && xSemaphoreTake(speedValueSemaphore,1)){
//        	speedValue = 0;
//        	xSemaphoreGive(speedValueSemaphore);
//        }
//        if(speedValue == 1 && distance < 2 && xSemaphoreTake(speedValueSemaphore,1)){
//        	speedValue = 0;
//        	xSemaphoreGive(speedValueSemaphore);
//        }
////        if(speedValue == 0 && distance < 1 && xSemaphoreTake(speedValueSemaphore,1)){
////        	speedValue = 0;
////        	xSemaphoreGive(speedValueSemaphore);
////        }
	}
}


void IncreaseSpeedISR(){
	static unsigned long previousInterruptTime = 0;
	unsigned long currentInterruptTime = millis();
	static BaseType_t xHigherPriorityTaskWoken;

	if((currentInterruptTime - previousInterruptTime) > 500){
		if (speedValue < 3 && xSemaphoreTakeFromISR (speedValueSemaphore, &xHigherPriorityTaskWoken)){
			speedValue++;
		}
		previousInterruptTime = currentInterruptTime;
		xSemaphoreGiveFromISR(speedValueSemaphore, &xHigherPriorityTaskWoken);
	}
	if (xHigherPriorityTaskWoken == pdTRUE){
		taskYIELD();
	}
}

void DecreaseSpeedISR(){
	static unsigned long previousInterruptTime = 0;
	unsigned long currentInterruptTime = millis();
	static BaseType_t xHigherPriorityTaskWoken;

	if((currentInterruptTime - previousInterruptTime) > 500){
		if (speedValue >0 && xSemaphoreTakeFromISR (speedValueSemaphore, &xHigherPriorityTaskWoken)){
			speedValue--;
		}
		previousInterruptTime = currentInterruptTime;
		xSemaphoreGiveFromISR(speedValueSemaphore, &xHigherPriorityTaskWoken);
	}
	if (xHigherPriorityTaskWoken == pdTRUE){
		taskYIELD();
	}
}


void setup() {
	Serial.begin(115200);
	pinMode(5, OUTPUT);//buzzer
	pinMode(6, OUTPUT);//yellow led 1
	pinMode(7, OUTPUT);//yellow led 2
	pinMode(8, OUTPUT);//yellow led 3
	pinMode(9, OUTPUT);//red led
	attachInterrupt(digitalPinToInterrupt(3), IncreaseSpeedISR, FALLING);
	attachInterrupt(digitalPinToInterrupt(2), DecreaseSpeedISR, FALLING);
}

void loop() {
//	xTaskCreate(BuzzerTask,"BuzzerTask",STACK_SIZE,NULL,3,NULL);
//	xTaskCreate(ReadPotentioTask,"ReadPotentioTask",STACK_SIZE,NULL,2,NULL);
	xTaskCreate(CurrentSpeedTask,"CurrentSpeedTask",STACK_SIZE,NULL,2,NULL);
	xTaskCreate(PotentiometerReadingTask,"PotentiometerReadingTask",STACK_SIZE,NULL,3,NULL);
//	xTaskCreate(CalculationTask,"CalculationTask",STACK_SIZE,NULL,1,NULL);
	vTaskStartScheduler();
}

