# PWM Controlled DC Motor using Potentiometer and L298N

This project controls the speed of a DC motor using PWM (Pulse Width Modulation) from an Arduino. The speed is adjusted via a potentiometer, and direction is hard-coded to forward using the L298N motor driver.

## 🧠 Features

- Real-time speed control of DC motor using a potentiometer
- Smooth acceleration/deceleration using PWM
- Compatible with L298N or similar H-bridge motor drivers
- Serial monitor output of speed and analog input for debugging

## 🧰 Hardware Required

- Arduino Uno/Nano (or compatible)
- L298N Motor Driver Module
- DC Motor
- 10k Potentiometer
- Breadboard and jumper wires
- Power supply (depending on motor specs)

## 🔌 Circuit Connections

| Component     | Arduino Pin |
|---------------|-------------|
| ENA (L298N)    | D9 (PWM)    |
| IN1            | D7          |
| IN2            | D6          |
| Potentiometer  | A0 (middle pin) |
| Pot VCC        | 5V          |
| Pot GND        | GND         |

> Connect motor to L298N OUT1 and OUT2. ENA controls speed, IN1/IN2 control direction.

## 🔄 Working Principle

- Potentiometer adjusts analog value from 0–1023
- Mapped to PWM output (0–255)
- PWM sent to ENA controls motor speed
- Motor runs **forward** by default (`IN1 HIGH`, `IN2 LOW`)

## 📟 Serial Monitor

Example output:
Pot: 512 Speed: 127
Pot: 1023 Speed: 255

## 🗂️ Files

- `PWM_controlled_DC_motor.ino`: Arduino code
- `circuit.png`: Wiring diagram *(if available)*

---

## 🧪 Notes

- You can reverse motor direction by swapping `IN1` and `IN2` logic.
- Works well as a beginner’s intro to motor control and PWM in embedded systems.

