/*
  BlinkPattern
  short short long...

  This example code is in the public domain.
*/


// give it a name:
int led = 5;
int buttonIn = 36;

// used for no delay blink pattern:
int stepCounter = 0;
double timer = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  pinMode(buttonIn, INPUT_PULLUP);
}

// the loop routine runs over and over again forever:
void loop() {

  // check the input
  int buttonPressed = digitalRead(buttonIn);

  // blink a pattern when button is not pressed
  // stop and set to low when button is pressed.
  if (buttonPressed == HIGH) {
    blinkPattern(); 
    // blinkPatternNoDelay();
  }
  else{
    digitalWrite(led, LOW);
  }

}

// On / off pattern
void blinkPattern() {
  // short
  digitalWrite(led, HIGH);
  delay(100);
  digitalWrite(led, LOW);
  delay(200);

  // short
  digitalWrite(led, HIGH);
  delay(100);
  digitalWrite(led, LOW);
  delay(200);

  // long:
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(200);
}


// blink the same pattern but do not use the delay function
// instead uses millis() to create a timer.
void blinkPatternNoDelay() {
  if (millis() > timer) {
    if (stepCounter == 0) {
      digitalWrite(led, HIGH);
      timer = millis() + 100;
    }
    else if (stepCounter == 1) {
      digitalWrite(led, LOW);
      timer = millis() + 200;
    }
    else if (stepCounter == 2) {
      digitalWrite(led, HIGH);
      timer = millis() + 100;
    }
    else if (stepCounter == 3) {
      digitalWrite(led, LOW);
      timer = millis() + 200;
    }
    if (stepCounter == 4) {
      digitalWrite(led, HIGH);
      timer = millis() + 1000;

    }
    else if (stepCounter == 5) {
      digitalWrite(led, LOW);
      timer = millis() + 200;

    }

    // increment step counter
    stepCounter++;
    
    // if greater than 5 reset to 0 
    if (stepCounter > 5) {
      stepCounter = 0;
    }
  }
}
