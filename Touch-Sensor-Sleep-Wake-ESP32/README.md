# Touch Sensor Sleep-Wake System using ESP32 and MPR121

This project demonstrates a capacitive touch interface using an ESP32 and the Adafruit MPR121 capacitive touch sensor. The ESP32 can enter deep sleep mode and wake up based on touch input, conserving power in embedded and IoT applications.

## 🧠 Features

- Uses ESP32’s **touch pin (T4)** for deep sleep wake-up.
- Detects touches on **MPR121’s 12 capacitive inputs**.
- Enters deep sleep to save power and wakes up via touchpad.
- Debounce logic to avoid false triggers.

## 🔌 Hardware Required

- ESP32 development board  
- Adafruit MPR121 Capacitive Touch Sensor  
- Jumper wires  
- (Optional) Touch pads or conductive materials for sensing

## 🗂️ Pin Connections

| ESP32 Pin | MPR121 Pin |
|-----------|------------|
| GPIO21    | SDA        |
| GPIO22    | SCL        |
| 3.3V      | VCC        |
| GND       | GND        |

**ESP32 Touch Pin Used:** GPIO4 (T4)

## 💡 Working Principle

- On startup, the ESP32 checks if it was woken from sleep via the touchpad.
- Touching the ESP32 pad (GPIO4) toggles between sleep and wake modes.
- While awake, the MPR121 monitors all 12 touch channels and logs touches via Serial.
- Sleep mode ignores MPR121 until wake-up.

## 📂 Files

- `Touch-Sensor-Sleep-Wake-ESP32.ino`: Main source code
- `circuit_diagram.png`: Wiring diagram (if available)

## 🚀 How to Use

1. Upload the code to your ESP32 using the Arduino IDE.
2. Open the Serial Monitor at **115200 baud**.
3. Touch the ESP32 touch pad (GPIO4) to put it to sleep or wake it up.
4. Touch the MPR121 channels to see touch feedback when awake.

## 🧰 Libraries Used

- [`Adafruit_MPR121`](https://github.com/adafruit/Adafruit_MPR121)
- `Wire.h`

## 📸 Demo

*(Insert photo or video link if available)*

---
