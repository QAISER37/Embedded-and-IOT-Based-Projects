# Overload Alert System for DC Motor using WCS1700 and ESP32

This project monitors the current drawn by a DC motor using a WCS1700 current sensor. If the motor draws more than a safe threshold, a buzzer is activated to signal an overload condition.

## ⚙️ Features

- Real-time current monitoring via WCS1700 sensor
- Automatic motor control at startup
- Overload protection using buzzer alert
- Adjustable thresholds for safe operation

## 🧰 Hardware Required

- ESP32 development board  
- DC motor  
- WCS1700 current sensor  
- Buzzer  
- Power supply  
- Jumper wires  
- (Optional) L298N motor driver (if using high-power motor)

## 🔌 Circuit Connections

| Component        | ESP32 Pin |
|------------------|-----------|
| Motor IN1        | GPIO26    |
| Motor IN2        | GPIO27    |
| Buzzer           | GPIO14    |
| WCS1700 AOUT     | GPIO34 (Analog input) |
| VCC (Sensor)     | 5V        |
| GND              | GND       |

> Ensure the current sensor is wired properly around the motor’s power line.

## ⚙️ Parameters

- `Vcc`: Sensor voltage (5V)
- `sensitivity`: 1.7 V/A for WCS1700
- `offsetVoltage`: Adjust experimentally when motor is OFF
- `overloadThreshold`: Set based on safe motor current (e.g., 1.2A)

## 📟 Serial Monitor Output

Shows:
- Raw ADC value
- Calculated voltage from sensor
- Estimated motor current (in Amps)

### Example Output:
ADC: 2030 | Voltage: 2.48 V | Current: 0.61 A