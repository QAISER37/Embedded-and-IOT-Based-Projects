// Pin assignments
const int ENA = 9;     // PWM pin connected to ENA on L298N
const int IN1 = 7;     // Direction pin 1
const int IN2 = 6;     // Direction pin 2
const int potPin = A0; // Analog pin connected to potentiometer

void setup() {
  // Initialize motor control pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Set motor direction (IN1 HIGH, IN2 LOW = Forward)
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // (Optional) Start serial monitor to debug
  Serial.begin(9600);
}

void loop() {
  // Read potentiometer value (0–1023)
  int potValue = analogRead(potPin);

  // Map potentiometer value to PWM range (0–255)
  int motorSpeed = map(potValue, 0, 1023, 0, 255);

  // Print values to Serial Monitor (optional)
  Serial.print("Pot: ");
  Serial.print(potValue);
  Serial.print("  Speed: ");
  Serial.println(motorSpeed);

  // Set motor speed via PWM
  analogWrite(ENA, motorSpeed);

  // Small delay for stability
  delay(100);
}
