/*
  433 MHz RF Module Transmitter Demonstration 2
  RF-Xmit-Demo-2.ino
  Demonstrates 433 MHz RF Transmitter Module with DHT-22 Sensor
  Use with Receiver Demonstration 2

   adapted from
  https://dronebotworkshop.com/433mhz-rf-modules-arduino/
*/

// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>

// Global Variables

// Hard coded messages
char * message1 = "msg1";
char * message2 = "msg2";

// Create Amplitude Shift Keying Object
RH_ASK rf_driver;

void setup() {

  // Initialize ASK Object
  rf_driver.init();

  Serial.begin(9600);
  Serial.print("started serial at 9600...");

}

void loop()
{
  // Send message1 - hard message coded above
  rf_driver.send((uint8_t *)message1, strlen(message1));
  rf_driver.waitPacketSent();
  delay(500);
  
  // Send message2 - hard message coded above
  rf_driver.send((uint8_t *)message2, strlen(message2));
  rf_driver.waitPacketSent();
  delay(500);
}
