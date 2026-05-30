# 🚨 Smart Accident Detection System

![ESP32](https://img.shields.io/badge/ESP32-Microcontroller-blue?style=flat-square)
![Blynk](https://img.shields.io/badge/Blynk-IoT%20Platform-green?style=flat-square)
![Wokwi](https://img.shields.io/badge/Wokwi-Simulation-orange?style=flat-square)
![Arduino](https://img.shields.io/badge/Arduino-C%2B%2B-teal?style=flat-square)
![Status](https://img.shields.io/badge/Status-Active-brightgreen?style=flat-square)

---

## 📖 Project Description

The **Smart Accident Detection System** is an IoT-based embedded system that automatically detects road accidents and obstacles in real time using multiple sensors. The system monitors acceleration, vibration, and proximity data and triggers alerts (LED + Buzzer) while simultaneously sending live data to the **Blynk IoT dashboard** for remote monitoring.

This project is designed to improve road safety by enabling early detection of accidents and notifying relevant parties through an IoT interface.

---

## 🔗 Project Links

| Resource | Link |
|----------|------|
| 🔧 Circuit Simulation | [View on Wokwi](https://wokwi.com/projects/465315007087625217) |
| 📱 IoT Dashboard | [View on Blynk](https://blynk.cloud/dashboard/1064591/global/devices/287288/organization/1064591/devices/4040988/dashboard) |
| 💻 Source Code | *(Insert GitHub link here)* |

---

## 🎯 Objectives

- Detect sudden vehicle impacts using an **MPU6050 accelerometer**
- Detect high vibration levels using a **Potentiometer** (simulating a vibration sensor)
- Detect nearby obstacles using an **Ultrasonic Sensor (HC-SR04)**
- Trigger **LED** and **Buzzer** alerts upon accident detection
- Send real-time sensor data to **Blynk IoT Cloud**
- Display system status (NORMAL / ACCIDENT DETECTED) on the Blynk dashboard

---

## ⚙️ Features

- ✅ Real-time accident detection (sudden movement / high vibration)
- ✅ Obstacle detection within 15 cm range
- ✅ Live data streaming to Blynk dashboard via WiFi
- ✅ Visual alert (LED) and audio alert (Buzzer)
- ✅ Serial monitor logging for debugging
- ✅ Simulated and tested on Wokwi before hardware deployment

---

## 🛠️ Components Used

| Component | Quantity | Purpose |
|-----------|----------|---------|
| ESP32 | 1 | Main microcontroller / WiFi module |
| MPU6050 (Accelerometer/Gyroscope) | 1 | Detects sudden movement / impact |
| HC-SR04 Ultrasonic Sensor | 1 | Measures distance for obstacle detection |
| Potentiometer | 1 | Simulates vibration sensor input |
| LED | 1 | Visual accident alert indicator |
| Buzzer | 1 | Audio accident alert |

---

## 🔌 Pin Configuration

| ESP32 Pin | Component | Function |
|-----------|-----------|----------|
| GPIO 5 | HC-SR04 TRIG | Ultrasonic trigger output |
| GPIO 18 | HC-SR04 ECHO | Ultrasonic echo input |
| GPIO 4 | Potentiometer | Analog vibration input |
| GPIO 13 | LED | Visual alert output |
| GPIO 12 | Buzzer | Audio alert output |
| SDA / SCL | MPU6050 | I2C communication |

---

## 📡 Blynk Virtual Pin Mapping

| Virtual Pin | Sensor / Data | Description |
|-------------|---------------|-------------|
| V0 | System Status | "NORMAL" or "ACCIDENT DETECTED" |
| V1 | MPU6050 | Total acceleration value |
| V2 | HC-SR04 | Distance in centimeters |
| V3 | Potentiometer | Analog vibration value (0–4095) |

---

## 💻 Software & Libraries Used

| Library | Purpose |
|---------|---------|
| `WiFi.h` | ESP32 WiFi connection |
| `BlynkSimpleEsp32.h` | Blynk IoT integration |
| `Wire.h` | I2C communication |
| `Adafruit_MPU6050.h` | MPU6050 sensor driver |
| `Adafruit_Sensor.h` | Unified sensor abstraction |

---

## 🚀 How to Run / Setup Instructions

### 1. Simulation (Wokwi)
1. Open the [Wokwi Simulation](https://wokwi.com/projects/465315007087625217)
2. Click the **Play ▶** button to start the simulation
3. Observe the Serial Monitor for live sensor readings
4. Adjust the potentiometer or MPU6050 to trigger accident detection

### 2. Blynk Setup
1. Create a free account at [blynk.cloud](https://blynk.cloud)
2. Create a new template named **"Smart Accident Detection System Wokwi"**
3. Add the following datastreams:
   - V0 → String (System Status)
   - V1 → Double (Acceleration)
   - V2 → Integer (Distance)
   - V3 → Integer (Potentiometer)
4. Copy your **BLYNK_TEMPLATE_ID**, **BLYNK_TEMPLATE_NAME**, and **BLYNK_AUTH_TOKEN**
5. Replace the credentials in `sketch.ino`

### 3. Hardware Deployment
1. Install the required libraries in Arduino IDE
2. Select board: **ESP32 Dev Module**
3. Replace WiFi credentials with your network SSID and password
4. Upload `sketch.ino` to your ESP32
5. Open Serial Monitor at **115200 baud** to verify output
6. Check your Blynk dashboard for live data

---

## 🔍 Accident Detection Logic

```
if (potValue > 3000)       → High Vibration Detected → ACCIDENT
if (totalAcceleration > 18) → Sudden Movement Detected → ACCIDENT
if (distance < 15 cm)      → Obstacle Detected → LED Alert
```

---

## 📸 Screenshots 

<img width="382" height="641" alt="image" src="https://github.com/user-attachments/assets/36d495aa-b798-447f-bf6f-28b55d65d885" />


```
images/
<img width="940" height="409" alt="image" src="https://github.com/user-attachments/assets/5ebeb31a-dccb-450d-90e7-31543d7ab24a" />

<img width="382" height="641" alt="image" src="https://github.com/user-attachments/assets/5268d2d0-3b38-48bd-a184-240a884a0bb5" />


```

---


---

## 📄 License

This project is created for educational purposes.  
Feel free to use, modify, and share with proper attribution.

---

> 💡 *Built with ESP32 + Blynk IoT + Wokwi Simulation*

