/*
 * touch_sensor.cpp
 *
 *  Created on: 6 Feb 2017
 *      Author: user-pc
 */

#include <Arduino.h>
#define PIN_PTTM 0
#define PIN_TOUCH 1
void setup() {
// initialize serial communications at 115200 bps:
Serial.begin(115200);
}
void loop() {
int val, touch;
// read potentiometer's value
val = analogRead(PIN_PTTM);
// read touch sensor's value
touch = analogRead(PIN_TOUCH);
// dump them to serial port
Serial.print(val);
Serial.print(" ");
Serial.print(touch);
Serial.println();
// 200ms pause
delay(200);
}


