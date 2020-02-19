/*
   Modified from code at: https://howtomechatronics.com/tutorials/arduino/arduino-wireless-communication-nrf24l01-tutorial/
  Arduino Wireless Communication Tutorial
      Example 2 - Receiver Code

  by Dejan Nedelkovski, www.HowToMechatronics.com

  Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
//#include <Servo.h>

int buttonPin = 13;

// LEDC (LED Control) parameters
int ledPin = 25;
int ledChannel = 0;

// declar RF24 object
RF24 radio(0, 2); // radio(CE, CSN)
const byte addresses[][6] = {"00001", "00002"};
boolean buttonState = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  //  pinMode(led, OUTPUT);
  ledcSetup(ledChannel, 5000, 8); // 5000 Hz, 8 bits [0:255]
  ledcAttachPin(ledPin, ledChannel);

  radio.begin();
  radio.openWritingPipe(addresses[0]); // 00002
  radio.openReadingPipe(1, addresses[1]); // 00001
  // power levels: RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH and RF24_PA_MAX
  radio.setPALevel(RF24_PA_HIGH);
  radio.setChannel(2);  // number between 0-124

  Serial.begin(9600);
  Serial.println("Arduino 2");
}

void loop() {
  delay(5);
  radio.startListening();
  if ( radio.available()) {
    while (radio.available()) {
      int dataIn = 0;
      radio.read(&dataIn, sizeof(dataIn));
      Serial.println(dataIn);
      
      // PWM control of ESP 32 pins using ledc
      ledcWrite(ledChannel, dataIn);
    }

    delay(5);
    // going into Transmit mode
    radio.stopListening();
    // send the digital input pin value
    buttonState = digitalRead(buttonPin);
    radio.write(&buttonState, sizeof(buttonState));
  }
}
