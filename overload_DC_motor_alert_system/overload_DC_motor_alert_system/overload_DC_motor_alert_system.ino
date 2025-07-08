// Pin definitions
const int motorIN1 = 26;
const int motorIN2 = 27;
const int buzzerPin = 14;
const int currentSensorPin = 34; // AOUT from WCS1700

// Calibration values
const float Vcc = 5.0;              // Sensor powered by 5V
const float sensitivity = 1.7;      // WCS1700: ~1.7 V per Amp
const float offsetVoltage = 1.45;   // Adjust this after testing when motor is off
const float overloadThreshold = 1.2; // Amps — set based on your motor

void setup() {
  Serial.begin(115200);

  pinMode(motorIN1, OUTPUT);
  pinMode(motorIN2, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // Turn motor ON automatically
  digitalWrite(motorIN1, HIGH);
  digitalWrite(motorIN2, LOW);
}

void loop() {
  float current = readCurrent();

  Serial.print("Current: ");
  Serial.print(current, 2);
  Serial.println(" A");

  if (current > overloadThreshold) {
    digitalWrite(buzzerPin, HIGH);  // Sound buzzer
  } else {
    digitalWrite(buzzerPin, LOW);   // No alert
  }

  delay(200);
}

// Function to read current in Amps from WCS1700 sensor
float readCurrent() {
  int adcValue = analogRead(currentSensorPin);
  float voltage = (adcValue / 4095.0) * Vcc;
  float current = (voltage - offsetVoltage) / sensitivity;

  // Debugging info
  Serial.print("ADC: "); Serial.print(adcValue);
  Serial.print(" | Voltage: "); Serial.print(voltage, 2);
  Serial.print(" V | Current: "); Serial.print(current, 2);
  Serial.println(" A");

  return abs(current); // Ensure it's positive
}
