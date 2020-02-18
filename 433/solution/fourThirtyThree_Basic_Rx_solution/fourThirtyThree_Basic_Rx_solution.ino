/*
  433 MHz RF Module Receiver Demonstration
  Demonstrates 433 MHz RF Receiver Module
  Use with fourThirtyThree_Basic_Tx

  adapted from
  https://dronebotworkshop.com/433mhz-rf-modules-arduino/
*/

// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>

// Create Amplitude Shift Keying Object
// To specify different pins:
// rf_driver(rate, rx, tx)
RH_ASK rf_driver (2000, 2, 12);

int LED_Pin = 5;
bool LED_State = LOW;

void setup()
{
  // Initialize ASK Object
  rf_driver.init();

  // Setup Serial Monitor
  Serial.begin(9600);
  Serial.println("waiting for received data...");

  pinMode(LED_Pin, OUTPUT);
}

void loop()
{
  // Set buffer to size of largest expected message
  uint8_t buf[20];

  uint8_t buflen = sizeof(buf);

  // Check if there is a received packet
  if (rf_driver.recv(buf, &buflen))
  {
    Serial.print("length: " );
    Serial.println(buflen);

    // Message received with valid checksum
    Serial.print("Message Received: ");
    Serial.println((char*)buf);
    Serial.println("");

    // TODO: any time a message is received toggle the LED.
    if (LED_State == LOW) {
      // set the pin high
      digitalWrite(LED_Pin, HIGH);
      // toggle the variable
      LED_State = HIGH;
    }
    else {
      // set the pin low
      digitalWrite(LED_Pin, LOW);
      // toggle the variable
      LED_State = LOW;
    }

  }

}
