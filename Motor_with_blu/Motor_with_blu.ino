#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

// Motor pins
const int IN1 = 26;
const int IN2 = 27;

void setup() {
  Serial.begin(115200);              // Optional, for debugging
  SerialBT.begin("ESP32-Bluetooth"); // Bluetooth name

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Make sure motor is off at start
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void loop() {
  if (SerialBT.available()) {
    char c = SerialBT.read();
    Serial.println(c);  // Print received char for debugging

    if (c == '1') {
      // Turn motor ON (forward)
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
    } 
    else if (c == '0') {
      // Stop motor
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
    }
  }
}
