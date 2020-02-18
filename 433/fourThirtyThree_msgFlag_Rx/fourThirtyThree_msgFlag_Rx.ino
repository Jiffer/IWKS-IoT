/*
  433 MHz RF Module Receiver Demonstration 1
  RF-Rcv-Demo-1.ino
  Demonstrates 433 MHz RF Receiver Module
  Use with Transmitter Demonstration 1

  adapted from
  https://dronebotworkshop.com/433mhz-rf-modules-arduino/
*/

// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>


// Create Amplitude Shift Keying Object
//RH_ASK rf_driver(rate, tx_pin, rx_pin)
RH_ASK rf_driver (2000, 2, 12);

// vars to hold output strings
String str_analogVal;
String str_digitalVal;
String str_out;

void setup()
{
  // Initialize ASK Object
  rf_driver.init();
  // Setup Serial Monitor
  Serial.begin(9600);
  Serial.println("waiting for received data...");
}

void loop()
{
  // buffer to capture incoming message
  uint8_t buf[20];

  uint8_t buflen = sizeof(buf);

  // Check if there is a received packet
  if (rf_driver.recv(buf, &buflen))
  {
    Serial.print("len: " );
    Serial.println(buflen);

    // Print Message received with valid checksum
    Serial.print("Message Received: ");
    Serial.println((char*)buf);

    String str_out = String((char*)buf);

    // compare the first four characters to see if they match "msg1"
    if (str_out.substring(0, 4) == "msg1") {
      Serial.println("got msg1");
    }

    // compare the first four characters to see if they match "msg2"
    if (str_out.substring(0, 4) == "msg2") {
      Serial.println("got msg2");
    }
  }
}
