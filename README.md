# ATtiny85-Proportional-IR-Thermostat 🌡️⚡

A compact, high-efficiency thermostat controller specifically designed for **Infrared Heating Panels**. Built around the **ATtiny85** MCU, this project uses **Time-Proportional Control (TPC)** and zero-cross switching to provide stable room temperatures and extend hardware longevity.

## 🚀 Key Features

- **Proportional Control Logic:** Unlike standard ON/OFF thermostats, this controller uses a dynamic duty cycle (within a 20s window) to prevent temperature overshoot.
- **Zero-Cross Switching:** Utilizes a MOC3041 optoisolator and BTA16 TRIAC to switch AC loads at the zero-voltage point, minimizing EMI and electrical noise.
- **Fail-Safe Design:** Automatically shuts down the heater if the DS18B20 temperature sensor is disconnected or malfunctions.
- **Optimized UI:** Lightweight OLED interface using the `Tiny4kOLED` library with an auto-off timer to prevent screen burn-in.
- **Compact Power:** Integrated Hi-Link AC-DC module for a transformerless, small footprint design.

## 🛠️ Hardware Stack

| Component | Description |
|---|---|
| **MCU** | ATtiny85 (8-bit AVR) |
| **Power Stage** | BTA16-600 TRIAC (16A) |
| **Driver** | MOC3041 Zero-Cross Optoisolator |
| **Sensor** | DS18B20 (OneWire) |
| **Display** | SSD1306 OLED (128x32) |
| **PSU** | Hi-Link 220V to 5V Module |

## 💻 Installation & Libraries

To compile the code, you will need the following libraries in your Arduino IDE:
1. `OneWire`
2. `DallasTemperature`
3. `Tiny4kOLED`

**Pinout Configuration:**
- `PB3`: OneWire Bus (DS18B20)
- `PB4`: Setpoint Adjustment Button (Input Pullup)
- `PB1`: MOC3041 Trigger Pin (Output)
- `I2C (PB0/PB2)`: OLED Display

## 🛡️ Safety Warning
> [!CAUTION]
> This project involves **mains voltage (230V AC)**. High voltage can be lethal. Ensure proper isolation, use a suitable enclosure, and do not work on the device while it is plugged in. Always use a fuse on the AC input.
