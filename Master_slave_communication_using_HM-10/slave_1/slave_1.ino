#include <WiFi.h>
#include <esp_now.h>

#define DIRECTION_PIN 19
#define STEP_PIN      18
#define ENABLE_PIN    21
#define LED_PIN       2

int stepsPer90Deg = 50;
int pulseWidthMicros = 20;
int millisBetweenSteps = 5;

typedef struct {
  char command;
} command_struct;

command_struct incomingCommand;

bool isActive = false;
bool continuous = false;

void rotate90() {
  for (int i = 0; i < stepsPer90Deg; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(pulseWidthMicros);
    digitalWrite(STEP_PIN, LOW);
    delay(millisBetweenSteps);
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  }
}

void onReceive(const esp_now_recv_info_t *info, const uint8_t *data, int len) {
  memcpy(&incomingCommand, data, sizeof(incomingCommand));
  char cmd = incomingCommand.command;

  if (cmd == 'A' || cmd == 'C') {
    isActive = true;
    continuous = false;
    Serial.println("ESP2 Activated");
  } else if (cmd == 'B' || cmd == 'D') {
    isActive = false;
    continuous = false;
    Serial.println("ESP2 Stopped");
  } else if (isActive) {
    if (cmd == '1') {
      Serial.println("ESP2: Rotate 90°");
      rotate90();
    } else if (cmd == '2') {
      continuous = true;
      Serial.println("ESP2: Start Continuous Rotation");
    } else if (cmd == '3') {
      continuous = false;
      Serial.println("ESP2: Stop Continuous Rotation");
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(DIRECTION_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(ENABLE_PIN, LOW);
  //digitalWrite(DIRECTION_PIN, HIGH);

  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed!");
    return;
  }

  esp_now_register_recv_cb(onReceive);
  Serial.println("ESP2 Ready");
}

void loop() {
  if (continuous && isActive) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(pulseWidthMicros);
    digitalWrite(STEP_PIN, LOW);
    delay(millisBetweenSteps);
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  }
}
