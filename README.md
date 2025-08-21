# Automatic Room Lighting System (ATmega32 + IR)

This project implements an **automatic room light controller** using an **ATmega32 microcontroller**, **IR sensors**, and a **relay** to automate lighting based on room occupancy.

## Features

- Detects entry/exit using two IR sensors
- Controls lights/fans via relay
- Shows live count of people in room using a 7-segment display
- Energy-saving automation solution

## Hardware Used

- ATmega32
- IR Sensors × 2
- Relay Module
- 7-Segment Display (Common Cathode)
- 16MHz Crystal + Capacitors
- Resistors, Breadboard, Power Supply

## How It Works

- **Entry (Sensor1 → Sensor2):** Increment person count, turn on light/fan
- **Exit (Sensor2 → Sensor1):** Decrement person count
- **If Count = 0:** Turn off light/fan

## Wiring

| Pin | Function         |
|-----|------------------|
| PC0 | IR Sensor 1      |
| PC1 | IR Sensor 2      |
| PD0 | Relay Output     |
| PORTB | 7-Segment (a–g) |

## Tools Used (Windows)

| Tool             | Description                                                                 |
|------------------|-----------------------------------------------------------------------------|
| **Programmer**   | [USBasp](https://www.fischl.de/usbasp/) – USB In-System Programmer for AVR  |
| **IDE**          | [Atmel Studio 7/Microchip Studio for AVR® and SAM Devices](https://www.microchip.com/en-us/tools-resources/develop/microchip-studio) – Windows-based IDE for writing, compiling, and managing AVR projects |
| **Flashing Tool**| `avrdude` – Used for uploading `.hex` files to the ATmega32 via USBasp       |
| **Driver (for USBasp)** | [Zadig](https://zadig.akeo.ie/) – Use to install `libusbk` driver |
| **Debugger**     | Use LED indicators, 7-segment display output, or USART serial print for logic-level debugging |
