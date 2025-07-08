# ESP32 Multi-Slave Control using ESP-NOW + HM-10 Bluetooth Interface

This project demonstrates **multi-device wireless communication** using the ESP-NOW protocol, with Bluetooth HM-10 integration for manual command input from a smartphone or external controller.

---

## 📡 Overview

- **Master ESP32**
  - Receives sensor data (temperature + humidity) from multiple slave ESP32s via ESP-NOW.
  - Relays the received info to a mobile device via HM-10 Bluetooth.
  - Accepts commands from mobile (via Bluetooth) and broadcasts them to all slaves.

- **Slave ESP32s**
  - Control stepper motors based on received commands.
  - Support both **90° discrete** and **continuous rotation**.
  - LED toggles with motor steps for visual feedback.

---

## 🛠️ Hardware Used

### Master:
- ESP32 board
- HM-10 Bluetooth Module (connected to UART2: GPIO 16/17)
- Smartphone with a serial Bluetooth terminal (e.g. **Serial Bluetooth Terminal** app)

### Slaves (x2):
- ESP32 boards
- Stepper motor driver (e.g., A4988/DRV8825)
- Stepper motor
- Optional: LEDs for step indicator

---

## 📲 Commands via Bluetooth

You can send these characters from your mobile to the master through HM-10:

| Command | Description                             |
|---------|-----------------------------------------|
| `A`     | Activate Slave 1                        |
| `B`     | Deactivate Slave 1                      |
| `C`     | Activate Slave 2                        |
| `D`     | Deactivate Slave 2                      |
| `1`     | Rotate active slave by 90°              |
| `2`     | Start continuous rotation               |
| `3`     | Stop continuous rotation                |
| `E`     | Reserved for future use or more slaves  |

---

## 🔁 Communication Flow

[MOBILE APP]
↓ Bluetooth
[HM-10] ← UART → [ESP32 Master]
↓ ESP-NOW
[ESP32 Slave 1], [ESP32 Slave 2]

---

## 🧠 Data Structures

### Sent from Master to Slaves:

```cpp
typedef struct {
  char command;
} command_struct;

Sent from Slaves to Master (future expansion):
typedef struct {
  int deviceID;
  float temperature;
  float humidity;
} struct_message;
📂 Directory Tree
Master_slave_communication_using_HM-10/
├── Master/
│   └── master.ino
├── slave_1/
│   └── slave_1.ino
├── slave_2/
│   └── slave_2.ino
└── README.md
⚠️ Notes
All ESP32 devices must be on the same Wi-Fi channel (default works unless conflicting).

MAC addresses must be correct and unique for each peer in the master code.

The Serial2.begin() config (on the master) assumes your HM-10 is connected to GPIO 16 (RX) and GPIO 17 (TX). Adjust if needed.

rotate90() steps may need calibration depending on your motor driver and microstepping settings.
🧪 Example Serial Output
Master Serial Output:
ESP1 ready.
Receiver ready. Send command 1, 2, A, or 3...
Data received from: Sender 1 (ESP2)
Temperature: 26.5 °C, Humidity: 60.2 %
-----------------------------
Sending command: A
Sending command: 1
Slave Output (ESP2):
ESP2 Ready
ESP2 Activated
ESP2: Rotate 90°
