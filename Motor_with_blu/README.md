# Motor Control via Bluetooth using ESP32 and MIT App

This project demonstrates controlling a DC motor using an ESP32 and a custom mobile app created with **MIT App Inventor**. Communication is handled via Bluetooth, allowing wireless motor control from an Android phone.

## 🧠 Features

- Start and stop a motor wirelessly.
- Uses ESP32’s built-in Bluetooth (`BluetoothSerial` library).
- MIT App Inventor-based Android app for easy control.

## 🧰 Hardware Required

- ESP32 development board  
- L298N motor driver or direct transistor-based motor driver  
- DC Motor  
- Power supply  
- Android phone  
- Jumper wires

## ⚡ Circuit Connection

| ESP32 Pin | Motor Driver Pin |
|-----------|------------------|
| GPIO26    | IN1              |
| GPIO27    | IN2              |

> Connect motor driver outputs to a DC motor. Ensure you have common ground between ESP32 and motor power.

## 📱 MIT App Control

The mobile app sends:
- `'1'` → to turn the motor **ON**
- `'0'` → to turn the motor **OFF**

You can customize the app using MIT App Inventor.  
App file provided:
- `MotorControl.apk` (ready-to-install)
- *(or)* `.aia` project file (if you want to edit in MIT App Inventor)

## 🗂️ Files

- `Motor_with_blu.ino`: ESP32 source code
- `circuit.png`: Wiring diagram
- `MotorControl.apk`: Android app

## 🔧 Setup Instructions

1. Upload `.ino` file to ESP32.
2. Install the APK on your Android device.
3. Pair your phone with **ESP32-Bluetooth**.
4. Use the app to send '1' or '0' to control the motor.

## 🔌 Serial Debugging

Serial monitor (115200 baud) shows received Bluetooth commands for troubleshooting.

---

