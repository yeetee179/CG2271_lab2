#include <Arduino.h>
#include "prioq.h"
#define yellow_led_pin 7
#define red_led_pin 6
#define yellow_led_button 3
#define red_led_button 2

unsigned long current_interrupt_time;
static unsigned long previous_Interrupt_time = 0;

TPrioQueue *queue;

// Declares a new type called "funcptr"

void (*funcptr)();

// Flashes LED at pin 7: 5 times a 4 Hz
void int0task(){
	for(int i=0; i<5; i++){
	digitalWrite(yellow_led_pin, HIGH); // Set digital I/O pin to a 1
	delay(125); // Delay
	digitalWrite(yellow_led_pin, LOW); // Set digital I/O pin to a 0
	delay(125);
	}
}

// Flashes LED at pin 6: 5 times at 2HZ
void int1task(){
	for(int i=0; i<5; i++){
	digitalWrite(red_led_pin, HIGH); // Set digital I/O pin to a 1
	delay(250); // Delay
	digitalWrite(red_led_pin, LOW); // Set digital I/O pin to a 0
	delay(250);
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void int0ISR(){
	current_interrupt_time = millis();
	if((current_interrupt_time - previous_Interrupt_time) > 200){
		enq(queue, (void *)int0task, 0);
	}
	previous_Interrupt_time = current_interrupt_time;
}

void int1ISR(){
	current_interrupt_time = millis();
	if((current_interrupt_time - previous_Interrupt_time) > 200){
		enq(queue, (void *)int1task, 1);
	}
	previous_Interrupt_time = current_interrupt_time;

}

void setup(){
	attachInterrupt(digitalPinToInterrupt(3), int0ISR, FALLING); //deals with interrupt of pin 2
	attachInterrupt(digitalPinToInterrupt(2), int1ISR, FALLING); // deals with interrupt of pin 3
	pinMode(yellow_led_pin, OUTPUT);
	pinMode(red_led_pin, OUTPUT);

	queue = makeQueue();
}

// Dequeues and calls functions if the queue is not empty
void loop(){
    if(qlen(queue)>0){
    	void(*funcptr)(void) = (void (*)(void)) deq(queue);
    	funcptr();
    }
}


