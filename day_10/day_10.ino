/*
 * 30 Days - Lost in Space
 * Day 10 - Switchable Night Light
 */

// Explicitly include Arduino.h
#include "Arduino.h"

// Our photoresistor will give us a reading of the current light level on this analog pin
const byte PHOTORESISTOR_PIN = A0;  // Photoresistor analog pin
const byte CABIN_LIGHTS_SWITCH_PIN = 2; // pin associated with switch 1

// RGB LED pins
const byte RED_PIN = 11;    // pin controlling the red leg of our RGB LED
const byte GREEN_PIN = 10;  // pin ccontrolling the green leg of our RGB LED
const byte BLUE_PIN = 9;    // pin ccontrolling the blue leg of our RGB LED

const int NIGHTLIGHT_THRESHOLD = 100;

/*
 * Display a color on our RGB LED by providing an intensity for
 * our red, green and blue LEDs.
 */
void displayColor(
  byte red_intensity,    // red LED intensity (0-255)
  byte green_intensity,  // green LED intensity (0-255)
  byte blue_intensity    // blue LED intensity (0-255)
) {
  analogWrite(RED_PIN, red_intensity);      // write red LED intensity using PWM
  analogWrite(GREEN_PIN, green_intensity);  // write green LED intensity using PWM
  analogWrite(BLUE_PIN, blue_intensity);    // write blue LED intensity using PWM
}

void setup() {
  // Declare the RGB LED pins as outputs:
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // Start serial monitor
  Serial.begin(9600);
}

void loop() {
  /*
   * Each time through our loop() we will read the current value of our photoresistor.  When
   * the voltage goes above a threshold from more light we turn off .
   *
   * The photoresistor will produce a voltage that is not a simple digitial (on/off, HIGH/LOW)
   * value.  Because of this we cannot use a digital pin on our HERO.  Luckily our HERO board
   * provides six "analog" pins, named A0-A5.
   *
   * These pins will convert a voltage from 0V to 5V to a number from 0 to 1023, giving us
   * a full range of values.  Because we are reading an analog value instead of a digital
   * value, we use the analogRead() function.
   *
   * Here we use the reading from the PHOTORESISTOR_PIN and turn the LED off or on based on it.
   */
  unsigned int light_value = analogRead(PHOTORESISTOR_PIN);   // light value from 0 to 1024

  /*
   * Our HERO board doesn't have a text display, so the Arduino IDE has provided us a way to
   * for the HERO to send messages that are displayed in a window in the Arduino IDE.  To open
   * the Serial Monitor on the Arduino IDE you can select Tools/Serial Monitor from the Arduino
   * IDE menu, use the shortcut keys listed in the menu or click the "magnifying glass" icon in
   * the upper right of the IDE window.
   *
   * We initialized the Serial functions in setup and now we will use Serial.print() and
   * Serial.println() to send messages to the Arduino IDE Serial Monitor.  Both functions
   * take a single value which can be either a constant or a variable.  The only difference
   * between the two functions is that Serial.print() leaves the cursor at the end of the
   * current line.  Any additional output will be appended to the current line.  Serial.println()
   * prints the value and THEN adds a "newline", so that any following messages will appear
   * on the following line.
   */
  Serial.print("Light value: ");  // Display label string to serial monitor
  Serial.print(light_value);      // display the value read from our photoresistor
  Serial.print(" Swith PIN Value: ");
  Serial.println(digitalRead(CABIN_LIGHTS_SWITCH_PIN));

  if (light_value < NIGHTLIGHT_THRESHOLD && digitalRead(CABIN_LIGHTS_SWITCH_PIN) == HIGH) {
    displayColor(255,255,255);
  }
  else {
    displayColor(0,0,0);
  }

  delay(500);

}
