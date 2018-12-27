/*
 * LED Tail lights for NSX
 * Uses eight 8x8 neopixel matrixes
 * Code is only for one side at the moment.
 */

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
  #define PSTR // Make Arduino Due happy
#endif

// Data output pins
#define PASSENGER_MATRIX_PIN  5   // passenger side

// Opto-isolator inputs
#define OPTO_IN_PARKING       7   // parking
#define OPTO_IN_BRAKES        8  // brakes
#define OPTO_IN_REVERSE       9  // reverse
#define OPTO_IN_PASSENGER_TS  10  // passenger turn signal

// Color definitions - only used for black because you can't set 
// brightness on these without changing them all. 
#define BLACK    0x0000
#define RED      0xF800
#define ORANGE   0xFC60
#define WHITE    0xFFFA
#define BLUE     0x001F

// default state
int pinState_passenger_ts = 0;
int pinState_reverse = 0;
int pinState_parking = 0;
int pinState_brake = 0;

// Matrix objects
Adafruit_NeoMatrix passenger_matrix = Adafruit_NeoMatrix(
  8, 8, // pixel width/height per matrix
  8,    // number of tiles
  1,    // width of tiles
  PASSENGER_MATRIX_PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS    + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

void setup() {
  pinMode(OPTO_IN_PARKING,      INPUT_PULLUP);
  pinMode(OPTO_IN_BRAKES,       INPUT_PULLUP);
  pinMode(OPTO_IN_REVERSE,      INPUT_PULLUP);
  pinMode(OPTO_IN_PASSENGER_TS, INPUT_PULLUP);
  passenger_matrix.begin();
  passenger_matrix.show();
}

void loop() {
  pinState_parking      = digitalRead(OPTO_IN_PARKING);
  pinState_brake        = digitalRead(OPTO_IN_BRAKES);
  pinState_reverse      = digitalRead(OPTO_IN_REVERSE);
  pinState_passenger_ts = digitalRead(OPTO_IN_PASSENGER_TS);
  delay(1); // delay in between reads for stability

  // parking and brake lights
  // brake lights take priority over parking lights.
  if (pinState_brake == 1) {
    setBrakeMatrix(240);
  } else if (pinState_parking == 1) {
    setBrakeMatrix(150);
  } else {
    resetBrakes();
  }

  //reverse lights
  if (pinState_reverse == 1) {
    setReverse(150);
  } else {
    resetReverse();
  }

  //left turnsignal
  if (pinState_passenger_ts == 1) {
    setTurnSignal(200);
  } else {
    resetTurnSignal();
  }

  passenger_matrix.show();
}

void setBrakeMatrix(int brightness) {
  passenger_matrix.fillRoundRect(8,  0, 12, 8, 1, passenger_matrix.Color(brightness, 0, 0));
  passenger_matrix.fillRoundRect(22, 0, 12, 8, 1, passenger_matrix.Color(brightness, 0, 0));
  passenger_matrix.fillRoundRect(36, 0, 12, 8, 1, passenger_matrix.Color(brightness, 0, 0));
}

void resetBrakes() {
  passenger_matrix.fillRect(8, 0, 40, 8, BLACK);
}

void setReverse(int brightness) {
  passenger_matrix.fillRect(0, 0, 8, 8, passenger_matrix.Color(brightness, brightness, brightness));
}

void resetReverse() {
  passenger_matrix.fillRect(0, 0, 8, 8, BLACK);
}

void setTurnSignal(int brightness) {
  passenger_matrix.fillRect(48, 0, 5, 8, passenger_matrix.Color(brightness, 0, 0));
  passenger_matrix.fillRect(56, 0, 8, 8, passenger_matrix.Color(brightness, 0, 0));
}

void resetTurnSignal() {
  passenger_matrix.fillRect(48, 0, 16, 8, BLACK);
}
