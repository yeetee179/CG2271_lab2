/*
 * qn7.cpp
 *
 *  Created on: 7 Feb 2017
 *      Author: user-pc
 */

#include <Arduino.h>
unsigned char flag=0;

unsigned long current_interrupt_time;
static unsigned long previous_Interrupt_time = 0;

//interrupt service routine to handle button debouncing (pin 3 button)
//and set the flag to 1 if it is 0, and 0 if it is 1
void isr(){
	current_interrupt_time = millis();
	if((current_interrupt_time - previous_Interrupt_time) > 200){
		flag = !flag;
	}
	previous_Interrupt_time = current_interrupt_time;
}

void setup()
{
	attachInterrupt(0, isr, RISING);
	pinMode(6, OUTPUT);
}
void loop()
{
	digitalWrite(6, flag);
}
