//

#include <Arduino.h>
#include <avr/io.h>
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

#define STACK_SIZE 80

int desiredSpeed = 0;
int currentSpeed = 0;
int potentioValue = 0;
int distance = 0;
int redLedFlag = 0; //0 indicates no brake, 1 indicates brake
QueueHandle_t currentSpeedQueue = xQueueCreate(2, sizeof(int)); // queue for current speed
QueueHandle_t distanceQueue = xQueueCreate(2, sizeof(int));     //queue for distance value

//lights up the yellow LED given the current speed
//lights up the red LED if emergency braking is activated
//buzzes the buzzer according to the current speed value
void CurrentSpeedTask(void *p) {
	while(1){
		TickType_t redLedTime;
		if (currentSpeed == 0 ){
			digitalWrite(6, LOW);
			digitalWrite(7, LOW);
			digitalWrite(8, LOW);
			analogWrite(5,0);//buzzer is not buzzing
		}
		if (currentSpeed == 1 ){
			digitalWrite(6, HIGH);
			digitalWrite(7, LOW);
			digitalWrite(8, LOW);
			analogWrite(5, 5);//buzzer buzzes at volume 1
		}
		else if (currentSpeed == 2 ){
			digitalWrite(6, HIGH);
			digitalWrite(7, HIGH);
			digitalWrite(8, LOW);
			analogWrite(5,20);//buzzer buzzes at volume 2
		}
		else if (currentSpeed == 3){
			digitalWrite(6, HIGH);
			digitalWrite(7, HIGH);
			digitalWrite(8, HIGH);
			analogWrite(5, 55);// buzzer buzzes at volume 3
		}
		if (redLedFlag == 1){
			redLedTime = xTaskGetTickCount();
			digitalWrite(9, HIGH);
			vTaskDelayUntil(&redLedTime, 1000);
			digitalWrite(9, LOW);
			redLedFlag = 0;// buzzer buzzes at volume 4
		}
	}
}

//reads in the potentiometer value
void PotentiometerReadingTask(void *p) {
	while(1){
		TickType_t currentTime = xTaskGetTickCount();
		potentioValue = analogRead(0);

		//maps the potentiometer value  1 - 1023 to 4 distance values 1 - 4
		if (potentioValue <= 256){
			distance = 1; //distance = d
		}
		else if (potentioValue > 256 && potentioValue <=512 ){
			distance = 2; //distance = 2d
		}
		else if (potentioValue > 512 && potentioValue <= 768){
			distance = 3; //distance = 3d
		}
		else if (potentioValue > 768 && potentioValue <=1023){
			distance = 4; //distance = 4d
		}
		xQueueSendToBack(distanceQueue, &distance, (TickType_t) 5000);//send the distance value to the queue for UART printing

		//the following checks if given the desired speed whether the distance is within the safety distance or not
		if (desiredSpeed == 3 && distance <4){
			if (currentSpeed == distance){
				redLedFlag = 1;
			}
			//the relationship between current speed and its corresponding safety distance is current speed = distance - 1
			currentSpeed = distance - 1;
			//send the current speed value to the queue for UART printing
    		xQueueSendToBack(currentSpeedQueue, &currentSpeed, (TickType_t) 0);
		}
		else if(desiredSpeed == 3 && distance >= 4){
			currentSpeed = desiredSpeed;
    		xQueueSendToBack(currentSpeedQueue, &currentSpeed, (TickType_t) 0);
		}

		if (desiredSpeed == 2 && distance < 3){
			if (currentSpeed == distance){
				redLedFlag = 1;
			}
			currentSpeed = distance - 1;
    		xQueueSendToBack(currentSpeedQueue, &currentSpeed, (TickType_t) 0);
		}
		else if(desiredSpeed == 2 && distance >= 3){
			currentSpeed = desiredSpeed;
    		xQueueSendToBack(currentSpeedQueue, &currentSpeed, (TickType_t) 0);
		}

		if (desiredSpeed == 1 && distance < 2){
			if (currentSpeed == distance){
				redLedFlag = 1;
			}
			currentSpeed = distance - 1;
    		xQueueSendToBack(currentSpeedQueue, &currentSpeed, (TickType_t) 0);
		}
		else if(desiredSpeed == 1 && distance >= 2){
			currentSpeed = desiredSpeed;
    		xQueueSendToBack(currentSpeedQueue, &currentSpeed, (TickType_t) 0);
		}
		if (desiredSpeed == 0){
			currentSpeed = desiredSpeed;
    		xQueueSendToBack(currentSpeedQueue, &currentSpeed, (TickType_t) 0);
		}
        // this gives this task a period of 500ms
		vTaskDelayUntil(&currentTime, 500);
	}
}

void DisplayInfoTask(void *p){
    while(1){
		TickType_t DisplayPeriod = xTaskGetTickCount();
		int currentSpeedPrint;
		int distancePrint;

		Serial.print("desired speed is ");
		Serial.println(desiredSpeed);

		if(xQueueReceive(currentSpeedQueue, &currentSpeedPrint, (TickType_t) 0)){
			Serial.print("current speed is ");
			Serial.println(currentSpeedPrint);
		}
		if(xQueueReceive(distanceQueue, &distancePrint, (TickType_t) 0)){
			Serial.print("distance is ");
			Serial.println(distancePrint);
		}
		Serial.println();
		//this gives the task a period of 500
		vTaskDelayUntil(&DisplayPeriod, 500);
    }
}

void IncreaseSpeedISR(){
	static unsigned long previousInterruptTime = 0;
	unsigned long currentInterruptTime = millis();

	if((currentInterruptTime - previousInterruptTime) > 500){
		if (desiredSpeed < 3){
			desiredSpeed++;
		}
		previousInterruptTime = currentInterruptTime;
	}
}

void DecreaseSpeedISR(){
	static unsigned long previousInterruptTime = 0;
	unsigned long currentInterruptTime = millis();

	if((currentInterruptTime - previousInterruptTime) > 500){
		if (desiredSpeed > 0){
			desiredSpeed--;
		}
		previousInterruptTime = currentInterruptTime;
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
	xTaskCreate(CurrentSpeedTask,"CurrentSpeedTask",STACK_SIZE,NULL,1,NULL);
	xTaskCreate(PotentiometerReadingTask,"PotentiometerReadingTask",STACK_SIZE,NULL,3,NULL);
	xTaskCreate(DisplayInfoTask,"DisplayInforTask",STACK_SIZE,NULL,2,NULL);
	vTaskStartScheduler();
}
