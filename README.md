# 🔆 Automatic Room Lighting System (ATmega32 + IR)

This project implements an **automatic room light controller** using an **ATmega32 microcontroller**, **IR sensors**, and a **relay** to automate lighting based on room occupancy.

## 🚀 Features

- Detects entry/exit using two IR sensors
- Controls lights/fans via relay
- Shows live count of people in room using a 7-segment display
- Energy-saving automation solution

## 🧰 Hardware Used

- ATmega32
- IR Sensors × 2
- Relay Module
- 7-Segment Display (Common Cathode)
- 16MHz Crystal + Capacitors
- Resistors, Breadboard, Power Supply

## 🛠 How It Works

- **Entry (Sensor1 → Sensor2):** Increment person count, turn on light/fan
- **Exit (Sensor2 → Sensor1):** Decrement person count
- **If Count = 0:** Turn off light/fan

## 💡 Wiring

| Pin | Function         |
|-----|------------------|
| PC0 | IR Sensor 1      |
| PC1 | IR Sensor 2      |
| PD0 | Relay Output     |
| PORTB | 7-Segment (a–g) |
