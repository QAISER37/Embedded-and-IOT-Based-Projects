#include <Wire.h>
#include <Adafruit_MPR121.h>
#include "esp_sleep.h"

#define SDA_PIN 21
#define SCL_PIN 22
#define ESP32_TOUCH_PIN T4  // GPIO4 - for sleep/wake control
#define TOUCH_THRESHOLD 40  // Adjust based on your touch sensitivity

Adafruit_MPR121 cap = Adafruit_MPR121();

// Retained through deep sleep
RTC_DATA_ATTR bool isInSleepMode = false;  // Start in wake mode
RTC_DATA_ATTR int bootCount = 0;

bool wasPreviouslyTouched[12] = {false}; // Track all 12 MPR121 pins
unsigned long lastTouchTime = 0;
const unsigned long DEBOUNCE_DELAY = 300;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  bootCount++;
  Serial.println("Boot number: " + String(bootCount));

  // Initialize I2C for MPR121
  Wire.begin(SDA_PIN, SCL_PIN);

  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found. Check wiring.");
    while (1);
  }

  Serial.println("MPR121 initialized.");
  
  // Clear any existing touch states
  cap.touched();
  delay(100);

  // Check if we woke up from deep sleep
  esp_sleep_wakeup_cause_t wakeup_reason = esp_sleep_get_wakeup_cause();
  
  if (wakeup_reason == ESP_SLEEP_WAKEUP_TOUCHPAD) {
    Serial.println("Woke up from deep sleep due to ESP32 touch!");
    Serial.println("Now in WAKE mode.");
    isInSleepMode = false; // Now in wake mode
    
    // Wait for ESP32 touch to be released
    Serial.println("Please release ESP32 touch pad...");
    while (touchRead(ESP32_TOUCH_PIN) < TOUCH_THRESHOLD) {
      delay(50);
    }
    Serial.println("ESP32 touch released. Ready!");
    Serial.println("- Touch ESP32 pad again to sleep");
    Serial.println("- Touch MPR121 pads 0-11 for detection");
    
  } else {
    // Normal startup
    if (isInSleepMode) {
      Serial.println("In SLEEP mode. Touch ESP32 pad to wake up.");
    } else {
      Serial.println("In WAKE mode.");
      Serial.println("- Touch ESP32 pad to sleep");
      Serial.println("- Touch MPR121 pads 0-11 for detection");
    }
  }
  
  Serial.println("ESP32 Touch pin: GPIO4 (T4)");
  //Serial.print("Current touch value: ");
  //Serial.println(touchRead(ESP32_TOUCH_PIN));
}

void loop() {
  unsigned long currentTime = millis();
  
  // Check ESP32 capacitive touch for sleep/wake control
  int touchValue = touchRead(ESP32_TOUCH_PIN);
  bool esp32Touched = (touchValue < TOUCH_THRESHOLD);
  
  static bool wasESP32Touched = false;
  
  // Detect ESP32 touch with debounce
  if (esp32Touched && !wasESP32Touched && 
      (currentTime - lastTouchTime > DEBOUNCE_DELAY)) {
    
    lastTouchTime = currentTime;
    
    if (!isInSleepMode) {
      // Currently awake - go to sleep
      Serial.println("ESP32 touch detected. Going to SLEEP mode...");
      Serial.println("Release ESP32 touch pad now!");
      
      // Wait for ESP32 touch to be released
      unsigned long waitStart = millis();
      while (touchRead(ESP32_TOUCH_PIN) < TOUCH_THRESHOLD && 
             (millis() - waitStart < 3000)) {
        delay(50);
      }
      
      if (touchRead(ESP32_TOUCH_PIN) < TOUCH_THRESHOLD) {
        Serial.println("Please release ESP32 touch pad first!");
        wasESP32Touched = esp32Touched;
        return;
      }
      
      Serial.println("Going to sleep... Touch ESP32 pad to wake up.");
      ///Serial.println("MPR121 will be ignored during sleep.");
      isInSleepMode = true;
      delay(500);
      
      // Configure ESP32 touch wakeup
      touchSleepWakeUpEnable(ESP32_TOUCH_PIN, TOUCH_THRESHOLD);
      Serial.flush();
      delay(100);
      esp_deep_sleep_start();
      
    } else {
      // This shouldn't happen in normal flow, but handle it
      Serial.println("ESP32 touch detected. Going to WAKE mode...");
      isInSleepMode = false;
    }
    
  }
  
  wasESP32Touched = esp32Touched;
  
  // Only process MPR121 touches when in wake mode
  if (!isInSleepMode) {
    uint16_t touched = cap.touched();
    
    // Check all 12 MPR121 pins
    for (int i = 0; i < 12; i++) {
      bool isTouching = touched & (1 << i);
      
      // Detect touch with debounce
      if (isTouching && !wasPreviouslyTouched[i] && 
          (currentTime - lastTouchTime > DEBOUNCE_DELAY)) {
        
        Serial.print("MPR121 Pin ");
        Serial.print(i);
        Serial.println(" touched!");
        lastTouchTime = currentTime;
      }
      
      wasPreviouslyTouched[i] = isTouching;
    }
  }
  
  delay(50);
}