Arduino library for Ultrasonic HCSR04 sensor
This library is using a hardware interrupt to monitor Echo pin state change instead of using pulseIn function which pauses code execution. 

If you want to use the sensor with only one pin on the Arduino board, you must connect the Echo and Trigger pin together and then call adequate constructor for one pin mode e.g. sensor=HCSR04(2);

This library can also be used with multiple Ultransonic sensors connected but each sensor must have its own isr function e.g.
void isr_function(){
  sensor1.interruptRoutine();
}
