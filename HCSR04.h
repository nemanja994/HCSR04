// HCSR04.h
/* An Arduino library for HCSR04 Ultrasonic distance sensor*/

#pragma once
#ifndef _HCSR04_h
#define _HCSR04_h
// Ultrasonic HCSR04 sensor library
#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class HCSR04{
private:
	volatile uint64_t start,end; // this variables keeps the information about the duration of the Echo pulse
	uint32_t resetCount=50000; // adjust this variable for increased precision. This variable represent the duration between two readings
	volatile bool finished,resetSignal=true;
	uint8_t trigger, echo;
	uint16_t maxDistance=3800,lastDistance;
public:
	HCSR04(uint8_t, uint8_t);
	void startListening();
	bool isFinished() {return finished; }
	bool isError();
	uint16_t getDistance();
	void printDistance();
	void interruptRoutine();
	uint8_t echoPosition(){ return echo; };
};


#endif

