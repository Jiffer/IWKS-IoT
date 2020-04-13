/*
* modified from: https://howtomechatronics.com/tutorials/arduino/arduino-wireless-communication-nrf24l01-tutorial/
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(0, 2); // CE, CSN

// address of the pipe
// TODO: make this a unique address:
const byte address[6] = "00001";

void setup() {
  // initialize RF24 object
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_HIGH);
  radio.setChannel(100);
  // this side will only transmit
  radio.stopListening();
}

// main loop 
void loop() {
  // send a message then wait a second
  const char text[] = "Hello World";
  radio.write(&text, sizeof(text));
  delay(1000);
}
