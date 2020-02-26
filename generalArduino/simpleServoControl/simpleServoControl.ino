/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald

 modified for the ESP32 on March 2017
 by John Bennett

 * see  http://www.arduino.cc/en/Tutorial/Knob for a description of the original code
 * uses ESP32Servo library
 */

// Include the ESP32 Arduino Servo Library instead of the original Arduino Servo Library
#include <ESP32Servo.h> 

Servo myservo;  // create servo object to control a servo

int servoPin = 14;      // GPIO pin used to connect the servo control (digital out)
// Possible ADC pins on the ESP32: 0,2,4,12-15,32-39; // 34-39 are recommended for analog input
int potPin = 36;        // GPIO pin used to connect the potentiometer (analog in)
int ADC_Max = 4095;     // This is the default ADC max value on the ESP32 (12 bit ADC width);
  
int val;    // variable to read the value from the analog pin

void setup()
{
  myservo.setPeriodHertz(50);// Standard 50hz servo
  myservo.attach(servoPin, 500, 2400);   // attaches the servo on pin 14 to the servo object
                                         // using SG90 servo min/max of 500us and 2400us
                                         // for MG995 large servo, use 1000us and 2000us,
                                         // which are the defaults, so this line could be
                                         // "myservo.attach(servoPin);"
}

void loop() {
  val = analogRead(potPin);            // read the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, ADC_Max, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  myservo.write(val);                  // set the servo position according to the scaled value
  delay(2);                          
}
