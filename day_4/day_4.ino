#include "Arduino.h"


// alternative to #define CABIN_LIGHS_PIN 10. 
// #define is deprecated
// May also see uint8_t or unsigned char, which are
// the same as byte.
const byte CABIN_LIGHTS_PIN = 10;
const byte STORAGE_LIGHTS_PIN = 11;
const byte COCKPIT_LIGHTS_PIN = 12;

const byte CABIN_LIGHTS_SWITCH_PIN = 2;
const byte STORAGE_LIGHTS_SWITCH_PIN = 3;
const byte COCKPIT_LIGHTS_SWITCH_PIN = 4;

void setup() {
  // put your setup code here, to run once:
  pinMode(CABIN_LIGHTS_PIN, OUTPUT); 
  pinMode(STORAGE_LIGHTS_PIN, OUTPUT);
  pinMode(COCKPIT_LIGHTS_PIN, OUTPUT);

  pinMode(CABIN_LIGHTS_SWITCH_PIN, INPUT);
  pinMode(STORAGE_LIGHTS_SWITCH_PIN, INPUT);
  pinMode(COCKPIT_LIGHTS_SWITCH_PIN, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  // if(digitalRead(CABIN_LIGHTS_SWITCH_PIN) == HIGH) {
  //   digitalWrite(CABIN_LIGHTS_PIN, HIGH);
  // } else {
  //   digitalWrite(CABIN_LIGHTS_PIN, LOW);
  // }

  // if(digitalRead(STORAGE_LIGHTS_SWITCH_PIN) == HIGH) {
  //   digitalWrite(STORAGE_LIGHTS_PIN, HIGH);
  // } else {
  //   digitalWrite(STORAGE_LIGHTS_PIN, LOW);
  // }

  // if(digitalRead(COCKPIT_LIGHTS_SWITCH_PIN) == HIGH) {
  //   digitalWrite(COCKPIT_LIGHTS_PIN, HIGH);
  // } else {
  //   digitalWrite(COCKPIT_LIGHTS_PIN, LOW);
  // }

  digitalWrite(CABIN_LIGHTS_PIN, digitalRead(CABIN_LIGHTS_SWITCH_PIN));
  digitalWrite(STORAGE_LIGHTS_PIN, digitalRead(STORAGE_LIGHTS_SWITCH_PIN));
  digitalWrite(COCKPIT_LIGHTS_PIN, digitalRead(COCKPIT_LIGHTS_SWITCH_PIN));


}
