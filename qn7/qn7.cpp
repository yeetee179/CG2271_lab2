/*
 * qn7.cpp
 *
 *  Created on: 7 Feb 2017
 *      Author: user-pc
 */

#include <Arduino.h>
unsigned char flag=0;

unsigned long currentInterruptTime;
static unsigned long previousInterruptTime = 0;

void isr()
{
//	unsigned long currentInterruptTime;
//	static unsigned long previousInterruptTime = 0;
	currentInterruptTime = millis();
	if((previousInterruptTime - currentInterruptTime) > 100){
		flag = !flag;
	}
	previousInterruptTime = currentInterruptTime;

}
void setup()
{
//	attachInterrupt(0, isr, RISING);
	attachInterrupt(digitalPinToInterrupt(2), isr, RISING);
	pinMode(6, OUTPUT);
}
void loop()
{
	digitalWrite(6, flag);
}
