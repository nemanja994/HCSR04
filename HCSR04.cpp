// 
// 
// 

#include "HCSR04.h"

HCSR04::HCSR04(uint8_t triggerPin, uint8_t echoPin){
	trigger = triggerPin;
	echo = echoPin;
}

void HCSR04::initialise(){
	finished = false;
	pinMode(trigger, OUTPUT);
	digitalWrite(trigger, LOW);
	pinMode(echo, INPUT);
}

void HCSR04::startListening(){
	if (micros()-resetTime>resetCount) resetSignal=true;
	if (finished == false && resetSignal==true){
		digitalWrite(trigger, HIGH);
		delayMicroseconds(10);
		digitalWrite(trigger, LOW);
	}
}

uint16_t HCSR04::getDistance(){
		finished = false;
		lastDistance=(end-start)/58;
		return lastDistance;
}

bool HCSR04::isError(){
	if(lastDistance>maxDistance || lastDistance==0) return true;
	else return false;
}

void HCSR04::printDistance(){
	uint16_t tmp=getDistance();
	if (isError()) Serial.println("ERR");
	else {
	Serial.print("Distance: ");
	Serial.print(lastDistance);
	Serial.println(" cm");
	}
}

void HCSR04::interruptRoutine(){
	switch (digitalRead(echo)){
		case(HIGH) :
			start = micros();
			break;
		case(LOW) :
			end = micros();
			finished = true;
			resetSignal=false;
			resetTime=end;
			break;
	}
}
