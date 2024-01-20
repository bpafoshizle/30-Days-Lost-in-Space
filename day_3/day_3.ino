#define WS_CABIN_LIGHTS_PIN 12                      // Control our lander's lights using the HERO's pin 12
#define WS_CABIN_LIGHTS_SWITCH_PIN 2                // Connect our light switch to pin 2

void setup() {
  // put your setup code here, to run once:
  pinMode(WS_CABIN_LIGHTS_PIN, OUTPUT);             // Set light control pin as an OUTPUT     
  pinMode(WS_CABIN_LIGHTS_SWITCH_PIN, INPUT);       // Since we read from the switch, this pin is an INPUT
  pinMode(LED_BUILTIN, OUTPUT);                     // initialize digital pin LED_BUILTIN as an output.
}

void loop() {
  if(digitalRead(WS_CABIN_LIGHTS_SWITCH_PIN) == HIGH) {
    digitalWrite(WS_CABIN_LIGHTS_PIN, HIGH);    // Switch is ON, turn on our lander's light
    digitalWrite(LED_BUILTIN, HIGH);            
  } else {
    digitalWrite(WS_CABIN_LIGHTS_PIN, LOW); // Swithc is OFF, turn off lander's light
    digitalWrite(LED_BUILTIN, LOW);
  }
}
 