/*
 * qn8.cpp
 *
 *  Created on: 8 Feb 2017
 *      Author: user-pc
 */

#include <Arduino.h>
#define PIN_LED_RED 6
#define PIN_LED_YELLOW 7
#define PIN_POTENTIALMETER_INPUT 0
#define PIN_TOUCH_SENSOR_INPUT 1

int flag_button2=0;
int flag_button3=0;

void isr_red()
{
	unsigned long currentInterruptTime;
	static unsigned long previousInterruptTime = 0;
	currentInterruptTime = millis();
	if((currentInterruptTime - previousInterruptTime) > 200){
		flag_button2 = 1;
	}
	previousInterruptTime = currentInterruptTime;
}

void isr_yellow()
{
	unsigned long currentInterruptTime;
	static unsigned long previousInterruptTime = 0;
	currentInterruptTime = millis();
	if((currentInterruptTime - previousInterruptTime) > 200){
		flag_button3 = 1;
	}
	previousInterruptTime = currentInterruptTime;
}

void setup() {
	attachInterrupt(digitalPinToInterrupt(2), isr_red, FALLING);
	attachInterrupt(digitalPinToInterrupt(3), isr_yellow, FALLING);
	pinMode(PIN_LED_RED, OUTPUT);
	pinMode(PIN_LED_YELLOW, OUTPUT);
	pinMode(PIN_POTENTIALMETER_INPUT, INPUT);
	pinMode(PIN_TOUCH_SENSOR_INPUT, INPUT);
}


//void potential_red_control(){
//	int val;
//	if(flag_button2 == 1){
//		val = analogRead(PIN_POTENTIALMETER_INPUT);
//		analogWrite(PIN_LED_RED, remapPotentialMeter(val));
//	}
//	else if (flag_button2 == 0){
//		analogWrite(PIN_LED_RED, 300);
//	}
//}


//void isr_red()
//{
//	unsigned long currentInterruptTime;
//	static unsigned long previousInterruptTime = 0;
//	currentInterruptTime = millis();
//	if((currentInterruptTime - previousInterruptTime) > 200){
//		flag_button2 = 1;
//	}
//	previousInterruptTime = currentInterruptTime;
//}

//void touch_sensor_yellow_control(){
//	int val;
//	val = analogRead(PIN_TOUCH_SENSOR_INPUT);
//	digitalWrite(PIN_LED_YELLOW, HIGH); // Set digital I/O pin to a 1
//	delay(remapTouchSensor(val)); // Delay
//	digitalWrite(PIN_LED_YELLOW, LOW); // Set digital I/O pin to a 0
//	delay(remapTouchSensor(val));
//}

int remapPotentialMeter(int val){
	int revised_val;
	revised_val = val/4;
	return revised_val;
}

int remapTouchSensor(int val){
	int remappedValue;
	remappedValue = (double)val/600.0 * 375.0 +125;
	return remappedValue;
}


void loop() {

//	potential_red_control();
//	touch_sensor_yellow_control();

	int val_red;
	if(flag_button2 == 1){
		val_red= analogRead(PIN_POTENTIALMETER_INPUT);
		analogWrite(PIN_LED_RED, remapPotentialMeter(val_red));
	}


	int val_yellow;
	if(flag_button3 == 1){
		val_yellow = analogRead(PIN_TOUCH_SENSOR_INPUT);
		digitalWrite(PIN_LED_YELLOW, HIGH); // Set digital I/O pin to a 1
		delay(remapTouchSensor(val_yellow)); // Delay
		digitalWrite(PIN_LED_YELLOW, LOW); // Set digital I/O pin to a 0
		delay(remapTouchSensor(val_yellow));
	}
}




