# ESP32 Master-Slave Communication using ESP-NOW

This project demonstrates **bidirectional wireless communication** between two ESP32 devices using **ESP-NOW**, a connectionless peer-to-peer protocol developed by Espressif.

## 📡 Overview

- The **Master ESP32** sends a message to the Slave every 5 seconds.
- The **Slave ESP32** responds with its own message every 5 seconds.
- Both devices print received messages via Serial Monitor.
- Useful for short-range, low-power IoT messaging without WiFi networks.

## 🧠 Features

- Peer-to-peer communication (no router or AP needed)
- Low latency and power-efficient
- Supports structured data exchange
- MAC address-based device pairing

---

## 🧰 Hardware Required

- 2× ESP32 development boards
- Micro USB cables
- Arduino IDE with ESP32 board support

---

## 🔌 Setup Instructions

### 🔧 1. Get MAC Addresses
Upload either code to both ESP32s and open **Serial Monitor**. You will see their MAC addresses printed:

Master MAC Address: CC:7B:5C:F2:2B:24
Slave MAC Address: 2C:BC:BB:93:3D:F8

### ✍️ 2. Set Peer MACs
- Copy the **Slave MAC** into the **Master's `peerAddress[]`**
- Copy the **Master MAC** into the **Slave's `peerAddress[]`**

✅ Done correctly in the provided code!

---


## 📟 Serial Output (Example)

### On Master:
Master MAC Address: CC:7B:5C:F2:2B:24
Sent to ESP32-B
Received from ESP32-B: Hi from Slave!

### On Slave:

---

## 🗨️ Communication Format

Both devices use the following data structure:

```cpp
typedef struct struct_message {
  char msg[32];
  int device_id;
} struct_message;

🧪 Notes
ESP-NOW is best for short-range (<200m) and low-bandwidth messaging.

Make sure both ESP32 boards use the same Wi-Fi channel.

Encryption is set to false here for simplicity.
