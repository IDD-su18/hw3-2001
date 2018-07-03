/*
 * Glove FPS Controller
 */
#include <Filters.h>
#include <Keyboard.h>
#include <Bounce2.h>
#include "macros.h"

void setup() {
  Serial.begin(BAUD_RATE);
  setupPins();
  Keyboard.begin();
}

void setupPins() {
  int i;
  for (i = 0; i < NUM_DIGINPUTS; i++) {
    buttons[i].attach(dig_pins[i], INPUT_PULLUP);
    buttons[i].interval(DEBOUNCE_INTVERVAL);
  }
  pinMode(LED, OUTPUT);
}

void loop() {
  if (photor(analogRead(PHOTOR))) {
    digitalWrite(LED, HIGH);
    if (millis() % UPDATE_PERIOD == 0) {
      Keyboard.releaseAll();
      accelKey();
      forceKey(THUMB);
      forceKey(PALM);
      controlpadKey();
    }
  } else {
    digitalWrite(LED, LOW);
  }
}

void controlpadKey() {
  int i;
  for (i = 0; i < NUM_DIGINPUTS; i++) {
    buttons[i].update();
    if (buttons[i].fell())
      Keyboard.press(special[i]);
  }
}

int force(int vraw) {
  if (vraw > FSR_PRESS) {
    return 1;
  }
  return 0;
}

void forceKey(int which) {
  if (force(analogRead(which))) {
    if (which == THUMB)
      Keyboard.press(Z_TRIG);
    if (which == PALM)
      Keyboard.press(C_RIGHT);
  }
}

int photor(int vraw) {
  if (vraw < PHOTOR_DARK) {
    return 1;
  }
  return 0;
}

float getPitch(float xa, float ya, float za) {
  float pitch = atan(xa/sqrt(pow(ya,2) + pow(za,2)));
  pitch *= 180.0/PI;
  return pitch;
}

float getRoll(float xa, float ya, float za) {
  float roll = atan2(-za, ya);
  roll *= 180.0/PI;
  return roll;
}

void accelKey() {
  float xa = analogRead(X);
  float ya = analogRead(Y);
  float za = analogRead(Z);
  xa = map(xa, 0, 1023, -3000, 3000);
  ya = map(ya, 0, 1023, -3000, 3000);
  za = map(za, 0, 1023, -3000, 3000);
  lpfx.input(xa);
  lpfy.input(ya);
  lpfz.input(za);
  xa = lpfx.output();
  ya = lpfy.output();
  za = lpfz.output();
  float ro = getRoll(xa, ya, za);
  float p = getPitch(xa, ya, za);
  if (ro < TH_LEFT) {
    if (force(analogRead(PALM)))
      Keyboard.press(L_TRIG);
    else
      Keyboard.press(LEFT);
  }
  if (ro > TH_RIGHT) {
    if (force(analogRead(PALM)))
      Keyboard.press(R_TRIG);
    else
      Keyboard.press(RIGHT);
  }
  if (p < TH_UP) {
    Keyboard.press(UP);
  }
  if (p > TH_DOWN) {
    Keyboard.press(DOWN);
  }
}
