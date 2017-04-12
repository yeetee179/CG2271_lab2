
#include <Arduino.h>
#include <avr/io.h>
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

#define STACK_SIZE 200

int speedValue = 0;



void myDelay(int ms) {
	for(int i = 0; i< ms; i++){
		delayMicroseconds(1000);
	}
}

int remapPotentialMeter(int val){
	int revised_val;
	revised_val = val/4;
	return revised_val;
}

void BuzzerTask(void *p) {
	while(1){
		if(xSemaphoreTake(semaphoreMutex, (TickType_t) 1) == pdTRUE){
			unsigned int count = 0;
			digitalWrite(9, HIGH);
			while(count < 3000){
				digitalWrite(6, HIGH);
				myDelay(50);
				digitalWrite(6, LOW);
				myDelay(50);
				count += 100;
			}
			xSemaphoreGive(semaphoreMutex);
			digitalWrite(9, LOW);
			vTaskDelayUntil(&currentTime1, 10000);
		}
	}
}

void ReadPotentioTask(void *p) {
	static int potentioMeterValue = 0;
	int rawPotentioMeterValue;
	while(1){
		rawPotentioMeterValue = analogRead(0); //this value is shared
		if (rawPotentioMeterValue <= 256 ){
			potentioMeterValue = 1;
		}
		else if (rawPotentioMeterValue <= 256 && rawPotentioMeterValue <= 512 ){
			potentioMeterValue = 2;
		}
		else if (rawPotentioMeterValue <= 512 && rawPotentioMeterValue < 768 ){
			potentioMeterValue = 3;
		}
		else if (rawPotentioMeterValue < 768 && rawPotentioMeterValue < 1023 ){
			potentioMeterValue = 4;
		}
	}
}


void CurrentSpeedTask(void *p) {
	while(1){

	}
}

void IncreaseSpeedISR(){
    speedValue++;
}

void DecreaseSpeedISR(){
    speedValue++;

}



void setup() {
	Serial.begin(115200);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);
	pinMode(8, OUTPUT);
	attachInterrupt(digitalPinToInterrupt(3), IncreaseSpeedISR, FALLING);
	attachInterrupt(digitalPinToInterrupt(2), DecreaseSpeedISR, FALLING);
}

void loop() {
	xTaskCreate(BuzzerTask,"BuzzerTask",STACK_SIZE,NULL,3,NULL);
	xTaskCreate(ReadPotentioTask,"ReadPotentioTask",STACK_SIZE,NULL,2,NULL);
	xTaskCreate(CurrentSpeedTask,"CurrentSpeedTask",STACK_SIZE,NULL,1,NULL);
	vTaskStartScheduler();
}

