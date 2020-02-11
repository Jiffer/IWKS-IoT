/*
  433 MHz RF Module Transmitter Demonstration
  Demonstrates 433 MHz RF Transmitter Module
  Use with fourThirtythree_Basic_Rx

adapted from:
  https://dronebotworkshop.com/433mhz-rf-modules-arduino/
*/

// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>

// Create Amplitude Shift Keying Object
RH_ASK rf_driver;

void setup()
{
    // Initialize ASK Object
    rf_driver.init();
}

void loop()
{
  // change the message here so you can confirm it is from 
  // your transmit module and not a neighbors
    char *msg = "Hello World"; 
    rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();
    delay(1000);
}
