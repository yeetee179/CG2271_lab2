/*
 * qn6.cpp
 *
 *  Created on: 7 Feb 2017
 *      Author: user-pc
 */
#include <Arduino.h>
#define PIN_LED_RED 6
#define PIN_LED_YELLOW 7
#define PIN_POTENTIALMETER_INPUT 0
#define PIN_TOUCH_SENSOR_INPUT 1

int remapPotentialMeter(int val);
int remapTouchSensor(int val);

void setup() {
	pinMode(PIN_LED_RED, OUTPUT);
	pinMode(PIN_LED_YELLOW, OUTPUT);
	pinMode(PIN_POTENTIALMETER_INPUT, INPUT);
	pinMode(PIN_TOUCH_SENSOR_INPUT, INPUT);
}

//controls the brightness of the red LED
void potential_red_control(){
	int val;
	val = analogRead(PIN_POTENTIALMETER_INPUT);
	analogWrite(PIN_LED_RED, remapPotentialMeter(val));
}

//controls the blinking speed of the yellow LED
void touch_sensor_yellow_control(){
	int val;
	val = analogRead(PIN_TOUCH_SENSOR_INPUT);
	digitalWrite(PIN_LED_YELLOW, HIGH); // Set digital I/O pin to a 1
	delay(remapTouchSensor(val)); // Delay
	digitalWrite(PIN_LED_YELLOW, LOW); // Set digital I/O pin to a 0
	delay(remapTouchSensor(val));
}

//remaps the potential meter value of 0 - 1023 to 0 - 255
int remapPotentialMeter(int val){
	int revised_val;
	revised_val = val/4;
	return revised_val;
}

//remaps the touch sensor value of 0 - 1005 to 125 - 500
int remapTouchSensor(int val){
	int remappedValue;
	remappedValue = (double)val/1005.0 * 375.0 +125;
	return remappedValue;
}

void loop() {
	potential_red_control();
	touch_sensor_yellow_control();
}


