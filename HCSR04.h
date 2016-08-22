// HCSR04.h
// Arduino library for HCSR04 Ultrasonic distance sensor
// v1.3 Added a Moving Average filter for smoothing out the output

#ifndef _HCSR04_h
#define _HCSR04_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define windowSize 10 // The length of the moving average filter array. Increasing this variable will result in slower sensor response
#define resetCount 50000  // sleep time between two readings
#define maxDistance 400 // This is the maximum distance the sensor can measure

class HCSR04{
private:
/* Sensor Variables */
	uint8_t trigger, echo; // trigger and echo pin of the sensor
	volatile uint64_t start,end; // these variables keep the information about the duration of the echo pulse width
	volatile bool finished,resetSignal; // resetSignal is used for signalling that the resetCount time has passed
	uint16_t lastDistance; // last measured Distance
/* Moving Average Filter Variables */
	uint8_t currentPos,counter;  // counter stores the information about the current size of the array
	uint16_t window[windowSize]; // filter Array
	uint16_t sum=0; // the sum of the Array elements
/* Utility methods */ 
	void addToFilter();
	bool checkDistanceError();
	void calculateDistance();
public:
	HCSR04(uint8_t, uint8_t);
	void startListening();
	bool isError(){return counter==0?true:false;}; // if array filter is empty return an error
	uint16_t getDistance();
	void printDistance();
	void interruptRoutine();
	uint8_t echoPosition(){ return echo; }; // interrupt pin must be the same as echo pin
};

#endif

