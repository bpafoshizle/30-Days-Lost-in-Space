/*
 * 30 Days - Lost in Space
 * Day 20 - Creative Day. RGB Adjuster
 *
 * Learn more at https://learn.inventr.io/adventure
 *
 */

/*
 * Arduino concepts introduced/documented in this lesson.
 * - integer percentages without using floating point
 *
 * Parts and electronics concepts introduced in this lesson.
 * - 
 */

// Explicitly include Arduino.h
#include "Arduino.h"

// Include Keypad library
#include <Keypad.h>

// Include BasicEncoder library file
#include <BasicEncoder.h>

// Our HERO keypad has 3 rows, with 1 column.
const byte ROWS = 3;
const byte COLS = 1;

// Define what characters will be returned by each button
const char BUTTONS[ROWS][COLS] = {
  { 'R' },
  { 'G' },
  { 'B' }
};

// Define row and column pins connected to the keypad
const byte ROW_PINS[ROWS] = { 7, 6, 5 };
const byte COL_PINS[COLS] = { 13 }; 

// Create our keypad object from the keypad configuration above
Keypad keypad = Keypad(makeKeymap(BUTTONS), ROW_PINS, COL_PINS, ROWS, COLS);

const byte RED_PIN = 11;    // PWM pin controlling the red leg of our RGB LED
const byte GREEN_PIN = 10;  // PWM pin ccontrolling the green leg of our RGB LED
const byte BLUE_PIN = 9;    // PWM pin ccontrolling the blue leg of our RGB LED


// The Rotary Encoder will be used to control our lander's depth underwater using
// interrupts (explained below).  Since the HERO board only supports interrupts on
// pins 2 and 3, we MUST use those pins for rotary encoder inputs.
const byte RGB_CONTROL_CLK_PIN = 2;  // HERO interrupt pin connected to encoder CLK input
const byte RGB_CONTROL_DT_PIN = 3;   // HERO interrupt pin connected to encoder DT input

// Create BasicEncoder instance for our depth control (which initializes counter to 0)
BasicEncoder rgb_control(RGB_CONTROL_CLK_PIN, RGB_CONTROL_DT_PIN);

const int INITIAL_RGB = 0;
const int MAX_RGB = 255;    // Maximum value for RGB values

static char current_rgb_switch = 'R';
int r_value = INITIAL_RGB;
int g_value = INITIAL_RGB;
int b_value = INITIAL_RGB;

void setup() {

  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // Initially display RGB 000 or off
  displayColor(0, 0, 0);
  
  // Call Interrupt Service Routine (ISR) updateEncoder() when any high/low change
  // is seen on A (RGB_CONTROL_CLK_PIN) interrupt  (pin 2), or B (RGB_CONTROL_DT_PIN) interrupt (pin 3)
  attachInterrupt(digitalPinToInterrupt(RGB_CONTROL_CLK_PIN), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(RGB_CONTROL_DT_PIN), updateEncoder, CHANGE);

  keypad.addEventListener(keypadEvent); // Add an event listener for this keypad

  // Setup Serial Monitor
  Serial.begin(9600);
}

const unsigned int LOOP_DELAY = 200;  // Delay in ms between loop() executions.

void loop() {
  delay(LOOP_DELAY);
  char key = keypad.getKey();
  // Serial.print("keypad.getKey: ");
  // Serial.println(key);
  // Serial.print("Current RGB Switch: ");
  // Serial.println(current_rgb_switch);

  if (rgb_control.get_change()) {  // If the rgb control value has changed since last check
    // The rotary encoder library always sets the initial counter to 0, so we will always
    // add our initial value to the counter.
    // multiply by -1 to get right rotation positive, left negative (righty tighty, lefty loosey)
    int current_encoder_value = -1 * rgb_control.get_count();
    rgb_control.reset(); 

    switch (current_rgb_switch) {
      case 'R':
        r_value = clampRgbValue(r_value + current_encoder_value);
        break;
      case 'G':
        g_value = clampRgbValue(g_value + current_encoder_value);
        break;
      case 'B':
        b_value = clampRgbValue(b_value + current_encoder_value);
        break;
    }

    Serial.print("Current encoder value: ");
    Serial.println(current_encoder_value);
    Serial.print("Displaying: ");
    Serial.println(String(r_value) + ", " + String(g_value) + ", " + String(b_value));
    displayColor(r_value, g_value, b_value);

  }
}

// Interrupt Service Routine (ISR).  Let BasicEncoder library handle the rotator changes
void updateEncoder() {
  rgb_control.service();  // Call BasicEncoder library .service()
}

// Display a color by providing Red, Green and Blue intensities (0-255)
void displayColor(byte red_intensity, byte green_intensity, byte blue_intensity) {
  analogWrite(RED_PIN, red_intensity);      // Set red LED intensity using PWM
  analogWrite(GREEN_PIN, green_intensity);  // Set green LED intensity using PWM
  analogWrite(BLUE_PIN, blue_intensity);    // Set blue LED intensity using PWM
}

// Taking care of some special events.
void keypadEvent(KeypadEvent key){
    Serial.print("Keypad state: ");
    Serial.println(keypad.getState());
    Serial.print("Key pressed: ");
    Serial.println(key);
    current_rgb_switch = key;
    rgb_control.reset();
}

/**
 * Ensures the current RGB value is within valid bounds.
 * 
 * @param rgb_value The current RGB value to check.
 * @return The clamped RGB value.
 */
int clampRgbValue(int rgb_value) {
  if (rgb_value < INITIAL_RGB) {
    return INITIAL_RGB;
  } else if (rgb_value >= MAX_RGB) {
    return MAX_RGB;
  }
  return rgb_value;
}