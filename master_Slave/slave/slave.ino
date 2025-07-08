#include <esp_now.h>
#include <WiFi.h>

typedef struct struct_message {
  char msg[32];
  int device_id;
} struct_message;

struct_message incomingData;
struct_message outgoingData;

uint8_t peerAddress[] = {0xCC, 0x7B, 0x5C, 0xF2, 0x2B, 0x24};  // Master MAC

void onDataRecv(const esp_now_recv_info_t *info, const uint8_t *data, int len) {
  memcpy(&incomingData, data, sizeof(incomingData));
  Serial.print("Received from ESP32-A: ");
  Serial.println(incomingData.msg);
}

void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Slave Send Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  Serial.print("Slave MAC Address: ");
  Serial.println(WiFi.macAddress());

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed!");
    return;
  }

  esp_now_register_recv_cb(onDataRecv);
  esp_now_register_send_cb(onDataSent);

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, peerAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (!esp_now_is_peer_exist(peerAddress)) {
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
      Serial.println(" Failed to add peer");
      return;
    }
  }
}

void loop() {
  strcpy(outgoingData.msg, "Hi from Slave!");
  outgoingData.device_id = 2;

  esp_err_t result = esp_now_send(peerAddress, (uint8_t *)&outgoingData, sizeof(outgoingData));
  if (result == ESP_OK) {
    Serial.println(" Sent to ESP32-A");
  } else {
    Serial.println(" Send failed");
  }
  delay(5000);
}
