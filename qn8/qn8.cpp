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

int flag_button2=0; //for button that is connected to pin 2
int flag_button3=0; //for button that is connected to pin 3

//interrupt service routine to handle button debouncing (pin 3 button)
//and set the flag to 1
void isrRed()
{
	unsigned long current_interrupt_time;
	static unsigned long previous_interrupt_ime = 0;
	current_interrupt_time = millis();
	if((current_interrupt_time - previous_interrupt_ime) > 200){
		flag_button2 = 1;
	}
	previous_interrupt_ime = current_interrupt_time;
}

//interrupt service routine to handle button debouncing (pin 3 button)
//and set the flag to 1
void isrYellow()
{
	unsigned long current_interrupt_time;
	static unsigned long previous_interrupt_ime = 0;
	current_interrupt_time = millis();
	if((current_interrupt_time - previous_interrupt_ime) > 200){
		flag_button3 = 1;
	}
	previous_interrupt_ime = current_interrupt_time;
}

void setup() {
	attachInterrupt(digitalPinToInterrupt(2), isrRed, RISING); //deals with interrupt of pin 2
	attachInterrupt(digitalPinToInterrupt(3), isrYellow, RISING); // deals with interrupt of pin 3
	pinMode(PIN_LED_RED, OUTPUT);
	pinMode(PIN_LED_YELLOW, OUTPUT);
	pinMode(PIN_POTENTIALMETER_INPUT, INPUT);
	pinMode(PIN_TOUCH_SENSOR_INPUT, INPUT);
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




