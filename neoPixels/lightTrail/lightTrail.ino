// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            0

// How many NeoPixels?
#define NUMPIXELS      30

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// starting point is the first "pixel"
int lightIndex = 0;

// how fast to chase down the strip
int delayTime = 50;

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.

}

void loop() {

  int lastLight = lightIndex;

  // increment and roll around to 0 when needed
  lightIndex++;
  if (lightIndex > NUMPIXELS){
    lightIndex = 0;
  }
  // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
  pixels.setPixelColor(lightIndex, pixels.Color(255, 255, 255));
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(delayTime); // Delay for a period of time (in milliseconds).


  // turn off:
  // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
  pixels.setPixelColor(lastLight , pixels.Color(0, 0, 0)); // Moderately bright green color.
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(delayTime); // Delay for a period of time (in milliseconds).

}
