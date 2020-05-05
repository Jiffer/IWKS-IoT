// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the LED Strip
#define PIN            0

// How many NeoPixels
#define NUMPIXELS      30

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// blink Rate
int blinkRate = 1000;

void setup() {
  // begin serial communications
  Serial.begin(115200);

  // initialize the NeoPixel Library
  pixels.begin();
}

void loop() {

  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
  for (int i = 0; i < NUMPIXELS; i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(250, 193, 48));
    
    // This sends the updated pixel color to the hardware.
    pixels.show(); // nothing happens until this is called

    delay(20);
  }


  // pause for a moment
  delay(blinkRate);

  // turn off:
  for (int i = 0; i < NUMPIXELS; i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));

  }
  pixels.show(); // This sends the updated pixel color to the hardware.

  // pause for a moment
  delay(blinkRate);
}
