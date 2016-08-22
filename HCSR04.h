// HCSR04.h
// Arduino library for HCSR04 Ultrasonic distance sensor

#pragma once
#ifndef _HCSR04_h
#define _HCSR04_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class HCSR04{
private:
	volatile uint64_t start,end; // this variables keeps the information about the travel time of and ultrasound impulse
	uint32_t resetCount=50000; // adjust this variable for increased precision. This variable represent the duration of the pause between two readings
	volatile bool finished, resetSignal;
	uint8_t trigger, echo; 
	uint16_t maxDistance=3800,lastDistance;
public:
	HCSR04(uint8_t, uint8_t);
	HCSR04(uint8_t); // one pin mode constructor
	void startListening();
	bool isFinished() {return finished; }
	bool isError();
	uint16_t getDistance();
	void printDistance();
	void interruptRoutine();
	uint8_t echoPosition(){ return echo; };
};

#endif

