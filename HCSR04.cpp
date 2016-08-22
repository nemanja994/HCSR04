#include "HCSR04.h"

HCSR04::HCSR04(uint8_t triggerPin, uint8_t echoPin){
	// Class constructor
	trigger = triggerPin;
	echo = echoPin;
	finished = resetSignal=true;
	currentPos = counter=0;
	pinMode(trigger, OUTPUT);
	digitalWrite(trigger, LOW);
	pinMode(echo, INPUT);
}

void HCSR04::startListening(){
	// this method sends the ultrasound signal from trigger pin
	if (micros()-end>resetCount || resetSignal) resetSignal=true;
	if (finished && resetSignal){
		finished=false;
		digitalWrite(trigger, HIGH);
		delayMicroseconds(10);
		digitalWrite(trigger, LOW);
	}
}

void HCSR04::calculateDistance(){
	// this method calculates the last measured distance
		finished = true;
		lastDistance=(end-start)/58.2;
}

bool HCSR04::checkDistanceError(){
	// this method checks if the last measured distance is larger than maxDistance or equals to 0
	if(lastDistance>maxDistance || lastDistance==0) return true;
	else return false;
}

void HCSR04::addToFilter(){
	calculateDistance();
	if (!checkDistanceError()){
		if(counter<windowSize) {
			counter +=1;
		}
		else{
				sum-=window[currentPos];
		}
		window[currentPos] = lastDistance;
		sum+=lastDistance;
		currentPos = (currentPos + 1) % windowSize;
		// the counter keeps track on window length
	}
}

uint16_t HCSR04::getDistance(){
	if (sum>0) return sum/counter;
	else return 0;
}

void HCSR04::printDistance(){
	// this method prints the measured distance
	if(!isError()){
	Serial.print("Distance: ");
	Serial.print(getDistance());
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
			resetSignal=false;
			addToFilter();
			break;
	}
}
