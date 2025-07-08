#include <WiFi.h>
#include <esp_now.h>

// HM-10 Bluetooth Serial
#define RXD2 16
#define TXD2 17

// Structure from senders
typedef struct {
  int deviceID;
  float temperature;
  float humidity;
} struct_message;

typedef struct {
  char command;
} command_struct;

struct_message receivedData;
command_struct commandToSend;

// MAC addresses of ESP2 and ESP3
uint8_t esp2Mac[] = {0xCC, 0x7B, 0x5C, 0xF2, 0x2B, 0x24};
uint8_t esp3Mac[] = {0x34, 0x5F, 0x45, 0x12, 0xF8, 0x34};
uint8_t esp4Mac[] = {0x2C, 0xBC, 0xBB, 0x92, 0xB1, 0x18};
uint8_t esp5Mac[] = {0xC8, 0xf0, 0x9E, 0xB1, 0x38, 0x68};


bool compareMac(const uint8_t* mac1, const uint8_t* mac2) {
  for (int i = 0; i < 6; i++) {
    if (mac1[i] != mac2[i]) return false;
  }
  return true;
}

// ========== RECEIVE SENSOR DATA ==========
void onReceive(const esp_now_recv_info_t *info, const uint8_t *data, int len) {
  memcpy(&receivedData, data, sizeof(receivedData));
  String sender = "Unknown";

  if (compareMac(info->src_addr, esp2Mac)) sender = "Sender 1 (ESP2)";
  else if (compareMac(info->src_addr, esp3Mac)) sender = "Sender 2 (ESP3)";
  else if (compareMac(info->src_addr, esp4Mac)) sender = "Sender 3 (ESP4)";
  else if (compareMac(info->src_addr, esp4Mac)) sender = "Sender 3 (ESP5)";

  Serial.println("Data received from: " + sender);
  Serial.print("Temperature: "); Serial.print(receivedData.temperature);
  Serial.print(" °C, Humidity: "); Serial.print(receivedData.humidity);
  Serial.println(" %");
  Serial.println("-----------------------------");

  // Send to mobile via HM-10
  String btMessage = "From " + sender + " -> Temp: " +
                     String(receivedData.temperature, 1) + "°C, Hum: " +
                     String(receivedData.humidity, 1) + "%";
  Serial2.println(btMessage);  // Send via Bluetooth
}

// ========== SEND COMMAND ==========
void sendCommandToESP(char cmd) {
  commandToSend.command = cmd;
  Serial.print("Sending command: "); Serial.println(cmd);

  // Broadcast to both
  esp_now_send(esp2Mac, (uint8_t *)&commandToSend, sizeof(commandToSend));
  esp_now_send(esp3Mac, (uint8_t *)&commandToSend, sizeof(commandToSend));
  esp_now_send(esp4Mac, (uint8_t *)&commandToSend, sizeof(commandToSend));
  esp_now_send(esp5Mac, (uint8_t *)&commandToSend, sizeof(commandToSend));  
}

// ========== SETUP ==========
void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);  // HM-10 UART

  WiFi.mode(WIFI_STA);
  Serial.println("ESP1 ready.");

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Init Failed!");
    return;
  }

  esp_now_register_recv_cb(onReceive);

  // Add peers (ESP2 & ESP3)
  esp_now_peer_info_t peerInfo = {};
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  memcpy(peerInfo.peer_addr, esp2Mac, 6);
  esp_now_add_peer(&peerInfo);

  memcpy(peerInfo.peer_addr, esp3Mac, 6);
  esp_now_add_peer(&peerInfo);
  memcpy(peerInfo.peer_addr, esp4Mac, 6);
  esp_now_add_peer(&peerInfo);
  memcpy(peerInfo.peer_addr, esp5Mac, 6);
  esp_now_add_peer(&peerInfo);  

  Serial2.println("Receiver ready. Send command 1, 2, A, or 3...");
}

// ========== LOOP: READ COMMAND FROM HM-10 ==========
void loop() {
  if (Serial2.available()) {
    char cmd = Serial2.read();

    if (cmd == '1' || cmd == '2' || cmd == '3' || cmd == 'A' || cmd == 'B' || cmd == 'C' || cmd == 'D'|| cmd == 'E') {
      sendCommandToESP(cmd);
    } else {
      Serial.print("Invalid command received via HM-10: ");
      Serial.println(cmd);
    }
  }
}

