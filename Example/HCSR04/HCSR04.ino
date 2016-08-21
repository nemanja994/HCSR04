/*
 Name:		HCSR04.ino
 Created:	8/15/2016 8:47:15 PM
 Author:	Nemanja
*/

// the setup function runs once when you press reset or power the board
#include "HCSR04.h"
HCSR04 sensor = HCSR04(2, 3);
int interrupt = sensor.echoPosition();

void echo_isr(){
	sensor.interruptRoutine();
}

void setup() {
	Serial.begin(9600);
	attachInterrupt(digitalPinToInterrupt(interrupt), echo_isr, CHANGE);
}

// the loop function runs over and over again until power down or reset
void loop() {
	sensor.startListening();
	if (sensor.isFinished()) sensor.printDistance();
}