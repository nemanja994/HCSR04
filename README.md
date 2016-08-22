Arduino library for Ultrasonic HCSR04 sensor

This library is using a hardware interrupt to monitor Echo pin state change instead of using pulseIn function which pauses code execution. The library enables the user to use this sensor with only 2-3 lines of code like in the example sketch. A moving average filter was also implemented to smooth out the output. 

The user can change the number of points in filter array and the time between two sensor readings if they want to fine tune the sensor for their own need.


This library can also be used with multiple Ultransonic sensors connected but each sensor must have its own isr function e.g.
void isr_function(){
  sensor1.interruptRoutine();
}
