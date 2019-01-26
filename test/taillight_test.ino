/*
 * Test code for DIYNSXLED
 * Use with one side only
 * Insert the 3 wires into the passenger out
 * Add power to the ACC 2-pin port
 * Run this code and it will cycle through the lights in this order: Parking, brake, reverse, turn signal.
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

// brightness_levels
#define BRAKE_BRIGHTNESS    220
#define PARKING_BRIGHTNESS  100
#define TS_BRIGHTNESS       220
#define REVERSE_BRIGHTNESS  100

// default state
int pinState_passenger_ts = 0;
int pinState_reverse = 0;
int pinState_parking = 0;
int pinState_brake = 0;

// Matrix objects
Adafruit_NeoMatrix passenger_matrix = Adafruit_NeoMatrix(
  8, 8, // pixel width/height per matrix
  7,    // number of tiles
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
//  pinState_parking      = digitalRead(OPTO_IN_PARKING);
//  pinState_brake        = digitalRead(OPTO_IN_BRAKES);
//  pinState_reverse      = digitalRead(OPTO_IN_REVERSE);
//  pinState_passenger_ts = digitalRead(OPTO_IN_PASSENGER_TS);
//  delay(1); // delay in between reads for stability

  // parking and brake lights
  // brake lights take priority over parking lights.

  // brakes
  setParkingMatrix(PARKING_BRIGHTNESS);
  passenger_matrix.show();
  delay(2000);
  resetBrakes();

  setBrakeMatrix(BRAKE_BRIGHTNESS);
  passenger_matrix.show();
  delay(2000);
  resetBrakes();

  setReverse(REVERSE_BRIGHTNESS);
  passenger_matrix.show();
  delay(2000);
  resetReverse();
  
  setTurnSignal(TS_BRIGHTNESS);
  passenger_matrix.show();
  delay(2000);
  resetTurnSignal();
  
}

void setBrakeMatrix(int brightness) {
  // remove first one to match oem
  //passenger_matrix.fillRoundRect(8,  0, 12, 8, 1, passenger_matrix.Color(brightness, 0, 0));
  passenger_matrix.fillRoundRect(22, 0, 12, 8, 1, passenger_matrix.Color(brightness, 0, 0));
  passenger_matrix.fillRoundRect(36, 0, 12, 8, 1, passenger_matrix.Color(brightness, 0, 0));
}
// 0, 8, 16, 24, 32, 40, 48
// 8+12 = 20    8 to 20
// 2 gap
// 22+12 = 36   22 to 34
// 2 gap
// 38+12 = 50   36 to 48


void setParkingMatrix(int brightness) {
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
  passenger_matrix.fillRect(48, 0, 8, 8, passenger_matrix.Color(brightness, 0, 0));
}

void resetTurnSignal() {
  passenger_matrix.fillRect(48, 0, 8, 8, BLACK);
}
