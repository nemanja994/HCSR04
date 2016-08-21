// HCSR04.h
/* An Arduino library for HCSR04 Ultrasonic distance sensor*/

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
	volatile uint64_t start, end,resetTime,resetCount=50000;
	volatile bool finished,resetSignal=true;
	uint8_t trigger, echo,outputPrecision=0;
	uint16_t maxDistance=3800,lastDistance;
public:
	HCSR04(uint8_t, uint8_t);
	void initialise();
	void startListening();
	bool isFinished() {return finished; }
	bool isError();
	uint16_t getDistance();
	void printDistance();
	void interruptRoutine();
	uint8_t echoPosition(){ return echo; };
};


#endif

