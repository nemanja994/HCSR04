// 
// 
// 

#include "HCSR04.h"

HCSR04::HCSR04(uint8_t triggerPin, uint8_t echoPin){
	// Class constructor
	trigger = triggerPin;
	echo = echoPin;
	finished = false;
	pinMode(trigger, OUTPUT);
	digitalWrite(trigger, LOW);
	pinMode(echo, INPUT);
}

void HCSR04::startListening(){
	// this method sends the signal from trigger pin
	if (micros()-end>resetCount) resetSignal=true;
	if (finished == false && resetSignal==true){
		digitalWrite(trigger, HIGH);
		delayMicroseconds(10);
		digitalWrite(trigger, LOW);
	}
}

uint16_t HCSR04::getDistance(){
	// this method returns the lastMeasured distance (if you use this method you must always check if measured distance is wrong with isError method afterwards)
		finished = false;
		lastDistance=(end-start)/58;
		return lastDistance;
}

bool HCSR04::isError(){
	// this method checks if last measured distance is larger than maxDistance or equals to 0
	if(lastDistance>maxDistance || lastDistance==0) return true;
	else return false;
}

void HCSR04::printDistance(){
	// this method prints the last measured distance or prints Error if the last measured distance is larger than maxDistance
	uint16_t tmp=getDistance();
	if (isError()) Serial.println("ERR");
	else {
	Serial.print("Distance: ");
	Serial.print(lastDistance);
	Serial.println(" cm");
	}
}

void HCSR04::interruptRoutine(){
	// this method is called whenever echo Pin state changes
	switch (digitalRead(echo)){
		case(HIGH) :
			start = micros();
			break;
		case(LOW) :
			end = micros();
			finished = true;
			resetSignal=false;
			break;
	}
}
