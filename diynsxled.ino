/*
   LED Tail lights for NSX
   All rights reserved
   Intended for off-road use only
*/

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <MemoryFree.h>
#ifndef PSTR
#define PSTR // Make Arduino Due happy
#endif

// Data output pins
#define PASSENGER_MATRIX_PIN  5   // passenger side
#define DRIVER_MATRIX_PIN     6   // passenger side

// Opto-isolator inputs
#define OPTO_IN_PARKING       7   // parking
#define OPTO_IN_BRAKES        8  // brakes
#define OPTO_IN_REVERSE       9  // reverse
#define OPTO_IN_PASSENGER_TS  11  // passenger turn signal
// driver side TS == 10

// Color definitions - only used for black because you can't set
// brightness on these without changing them all.
#define BLACK    0x0000
#define RED      0xF800
#define ORANGE   0xFC60
#define WHITE    0xFFFA
#define BLUE     0x001F

// brightness_levels
#define BRAKE_BRIGHTNESS    220
#define PARKING_BRIGHTNESS  125
#define TS_BRIGHTNESS       220
#define REVERSE_BRIGHTNESS  125

// default state of optocoupler inputs
int pinState_passenger_ts = 0;
int pinState_reverse = 0;
int pinState_parking = 0;
int pinState_brake = 0;

// for determining what leds to turn on
boolean brakesOn = false;
boolean parkingOn = false;
boolean turnsignalOn = false;
boolean reverseOn = false;

void setup() {
  pinMode(OPTO_IN_PARKING,      INPUT_PULLUP);
  pinMode(OPTO_IN_BRAKES,       INPUT_PULLUP);
  pinMode(OPTO_IN_REVERSE,      INPUT_PULLUP);
  pinMode(OPTO_IN_PASSENGER_TS, INPUT_PULLUP);
  pinMode(LED_BUILTIN,          OUTPUT);        // turn on if there's an error
  //Serial.begin(115200);
  Serial.println("starting");
}

void loop() {
  // get state of what lights should be on
  pinState_parking      = digitalRead(OPTO_IN_PARKING);
  pinState_brake        = digitalRead(OPTO_IN_BRAKES);
  pinState_reverse      = digitalRead(OPTO_IN_REVERSE);
  pinState_passenger_ts = digitalRead(OPTO_IN_PASSENGER_TS);
  delay(1); // delay in between reads for stability

  Serial.print("freeMemory()=");
  Serial.println(freeMemory());

  // analyze the state of lights
  // brake lights take priority over parking lights.
  if (pinState_brake == 1) {
    brakesOn = true;
    parkingOn = false;
  } else if (pinState_parking == 1) {
    parkingOn = true;
    brakesOn = false;
  } else {
    brakesOn = false;
    parkingOn = false;
  }

  //reverse lights
  if (pinState_reverse == 1) {
    reverseOn = true;
  } else {
    reverseOn = false;
  }

  //left turnsignal
  if (pinState_passenger_ts == 1) {
    turnsignalOn = true;
  } else {
    turnsignalOn = false;
  }

  // we do it this way because there isn't enough memory if you make the neopixels global.
  setLeds(brakesOn, parkingOn, reverseOn, turnsignalOn, PASSENGER_MATRIX_PIN);
  setLeds(brakesOn, parkingOn, reverseOn, turnsignalOn, DRIVER_MATRIX_PIN);
}

void setLeds(boolean brakesOn, boolean parkingOn, boolean reverseOn, boolean turnsignalOn, 
              int pin) {

  unsigned long startTime = millis();
  // Matrix objects
  Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(
                                8, 8, // pixel width/height per matrix
                                7,    // number of tiles
                                1,    // width of tiles
                                pin,
                                NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
                                NEO_MATRIX_ROWS    + NEO_MATRIX_PROGRESSIVE,
                                NEO_GRB            + NEO_KHZ800);
  matrix.begin(); // init matrix
  
  if (brakesOn) {
    // only show 2 beause that's how stock setup does it
    //matrix.fillRoundRect(8,  0, 12, 8, 1, matrix.Color(BRAKE_BRIGHTNESS, 0, 0));
    matrix.fillRoundRect(22, 0, 12, 8, 1, matrix.Color(BRAKE_BRIGHTNESS, 0, 0));
    matrix.fillRoundRect(36, 0, 12, 8, 1,matrix.Color(BRAKE_BRIGHTNESS, 0, 0));
  } else if(parkingOn) {
    matrix.fillRoundRect(8,  0, 12, 8, 1, matrix.Color(PARKING_BRIGHTNESS, 0, 0));
    matrix.fillRoundRect(22, 0, 12, 8, 1, matrix.Color(PARKING_BRIGHTNESS, 0, 0));
    matrix.fillRoundRect(36, 0, 12, 8, 1, matrix.Color(PARKING_BRIGHTNESS, 0, 0));
  }

  if (reverseOn) {
    matrix.fillRect(0, 0, 8, 8, matrix.Color(REVERSE_BRIGHTNESS, REVERSE_BRIGHTNESS, REVERSE_BRIGHTNESS));
  }

  if (turnsignalOn) {
    matrix.fillRoundRect(48, 0, 8, 8, 1, matrix.Color(TS_BRIGHTNESS, 0, 0));
  }

  matrix.show();
  Serial.print("P ");
  Serial.print(parkingOn);
  Serial.print(" B ");
  Serial.print(brakesOn);
  Serial.print(" R ");
  Serial.print(reverseOn);
  Serial.print(" TS ");
  Serial.print(turnsignalOn);
  Serial.print(" PIN ");
  Serial.print(pin);
  Serial.print(" Matrix: freeMemory()=");
  Serial.print(freeMemory());
  unsigned long currentTime = millis();
  unsigned long elapsedTime = currentTime - startTime;
  Serial.print("\t Time to calculate: ");
  Serial.println(elapsedTime);

  // if it takes more than 100ms to calculate what leds to show, then turn on the led!
  if (elapsedTime > 100) {
    digitalWrite(LED_BUILTIN, HIGH);
  }
}
