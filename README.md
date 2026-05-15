<div align="center">

# 🚗 Automatic Parking Lift using Arduino Uno

### *A Smart Space-Saving Automated Vehicle Elevator System*

![Arduino](https://img.shields.io/badge/Arduino-UNO-blue?style=for-the-badge&logo=arduino)
![C++](https://img.shields.io/badge/C++-Embedded-green?style=for-the-badge&logo=c%2B%2B)
![IoT](https://img.shields.io/badge/IoT-Sensors%20%26%20Motors-orange?style=for-the-badge)
![Smart City](https://img.shields.io/badge/Type-Smart%20City%20Solution-red?style=for-the-badge)
![Real Time Public Problem Solution](https://img.shields.io/badge/Real--Time%20Public%20Problem%20Solution-Active-brightgreen?style=for-the-badge)

> 🚀 **This project is titled "Automatic Parking Lift using Arduino Uno" and focuses on addressing urban parking space shortages by automating vehicle vertical transport and smart slot management.**

</div>

---

## 📋 Table of Contents

- [📌 Abstract](#-abstract)
- [🎯 Objectives](#-objectives)
- [🔴 Problem Statement](#-problem-statement)
- [✅ Solution & Approach](#-solution--approach)
- [🔧 How the Project Works](#-how-the-project-works)
- [📋 Project Pseudocode](#-project-pseudocode)
- [📐 Project Flowchart](#-project-flowchart)
- [🌐 Hardware Components](#-hardware-components)
- [💡 Impact](#-impact)
- [🛠️ Technology Stack](#️-technology-stack)
- [📁 Project Structure](#-project-structure)
- [🗺️ System Architecture & Block Diagram](#️-system-architecture--block-diagram)
- [💻 Main Program](#-main-program)
- [🔍 Code Analysis](#-code-analysis)
- [🚀 Installation & Usage](#-installation--usage)
- [📁 Project Files](#-project-files)
- [🌟 Scope of Future Implementation](#-scope-of-future-implementation)
- [🤝 Open Source Contribution](#-open-source-contribution)
- [📄 License](#-license)

---

## 📌 Abstract

The **"Automatic Parking Lift using Arduino Uno"** is an embedded system project designed to optimize parking space utilization in crowded urban environments. By employing a vertical parking mechanism, the system minimizes the land footprint required for parking vehicles. 

An **Arduino Uno** serves as the central brain of the system, processing real-time sensor data. The system uses an **IR Sensor** to detect the arrival of a vehicle. A motorized elevator platform, driven by an **L298N Motor Driver**, transports the vehicle vertically. **Ultrasonic Sensors** are strategically placed to monitor the elevator's floor level and verify the availability of an empty parking slot. Finally, a **Servo Motor** controls the barrier gate, ensuring vehicles only enter when a space is verified to be empty.

This project delivers an automated, efficient, and scalable approach to modern vehicle parking.

---

## 🎯 Objectives

- ✅ **Detect vehicle arrival** automatically using Infrared (IR) sensors.
- ✅ **Automate vertical transport** using DC motors and an L298N driver module.
- ✅ **Track elevator floor position** precisely using Ultrasonic distance measurement.
- ✅ **Verify parking slot availability** using secondary Ultrasonic sensors.
- ✅ **Control entry barriers** dynamically using a Servo Motor.
- ✅ **Provide real-time serial feedback** for monitoring the parking status.

---

## 🔴 Problem Statement

With rapid urbanization and the continuous increase in vehicle ownership, modern cities face severe parking infrastructure challenges:

- 🏙️ **Space Scarcity**: Horizontal parking lots consume vast amounts of expensive urban real estate.
- ⏳ **Time Inefficiency**: Drivers spend significant time searching for empty parking spots, leading to traffic congestion.
- 👨‍🔧 **Manual Dependency**: Traditional parking lifts often require manual operation and supervision.
- 🚗 **High Risk of Scrapes & Accidents**: Tight conventional parking spaces increase the risk of minor collisions.

> **"Traditional horizontal parking is unsustainable in growing smart cities. Automated vertical parking systems offer a necessary solution, but they must be smart enough to detect vehicles and manage slots autonomously."**

---

## ✅ Solution & Approach

The proposed solution is a **Smart Automatic Parking Lift** that operates via:

1. **IR Detection** — Identifies when a vehicle is stationed on the lift platform.
2. **Motorized Lifting** — L298N Motor Driver activates the lift mechanism to move the car upward.
3. **Height/Floor Tracking** — An Ultrasonic Sensor measures the lift height, stopping the motor exactly at the target floor (e.g., 172 cm threshold).
4. **Slot Space Verification** — A second Ultrasonic Sensor scans the parking slot. If space is available (> 50 cm), it triggers the parking sequence.
5. **Servo Gate Operation** — The barrier gate opens (rotates to 0 degrees) to allow the car to enter the slot, and conveyor motors move the vehicle into place.

---

## 🔧 How the Project Works

### Step 1 — Vehicle Arrival
The car approaches the lift platform. An **IR Sensor (Pin 9)** reads `HIGH`, indicating a vehicle is detected.
- The system prints `"Car is detected!"` to the serial monitor.
- The main lift motors are enabled.

### Step 2 — Vertical Lifting
The **L298N Motor Driver** drives the DC motor to lift the platform.
- `motorDirectionPin1` is set `HIGH`, `motorDirectionPin2` is set `LOW`.

### Step 3 — Floor Level Reached
The **First Ultrasonic Sensor (Trig: 6, Echo: 7)** continuously measures the distance.
- Once `distance < 172 cm` (representing the first floor), the lift motors are commanded to **STOP**.

### Step 4 — Slot Availability Check
The **Second Ultrasonic Sensor (Trig: 1, Echo: 2)** measures the depth of the parking slot.
- If `distance > 50 cm`, the slot is **FREE**.
- If `distance < 50 cm`, the slot is **OCCUPIED**.

### Step 5 — Vehicle Parking
If the slot is free:
- The **Servo Motor** rotates to `0 degrees` (Gate Open).
- The forward conveyor motor is activated for a set duration to push the car into the slot.
- After parking, the system prepares to move backward/reset.

If the slot is occupied:
- The **Servo Motor** remains at `90 degrees` (Gate Closed).

---

## 📋 Project Pseudocode

```
START

INITIALIZE Sensors (IR, Ultrasonic x2)
INITIALIZE Motors (DC via L298N, Servo)
SET Servo to 0 degrees (Closed)

LOOP:
    READ IR_Sensor
    
    IF IR_Sensor == HIGH (Car Detected):
        START Lift Motor (Upward)
        DELAY
        
        WHILE Lift is moving:
            distance1 = READ Ultrasonic_1
            IF distance1 < 172cm:
                STOP Lift Motor
                PRINT "First Floor Reached"
                BREAK
                
        distance2 = READ Ultrasonic_2
        IF distance2 > 50cm (Free Space):
            ROTATE Servo to 0 degrees (Open Gate)
            PRINT "Free Space Available"
            START Conveyor Motor (Forward) to park car
            DELAY for parking duration
            STOP Conveyor Motor
        ELSE:
            ROTATE Servo to 90 degrees (Keep Gate Closed)
            
    ELSE:
        STOP ALL Motors

END LOOP
```

---

## 📐 Project Flowchart

```
┌─────────────────────────────────────┐
│              START                  │
└────────────────┬────────────────────┘
                 │
                 ▼
┌─────────────────────────────────────┐
│      Car arrives at the lift?       │
│        (IR Sensor == HIGH)          │
└───┬─────────────────────────────┬───┘
   YES                            NO → STOP MOTORS
    │
    ▼
┌─────────────────────────────────────┐
│  Activate Lift Motor (Move UP)      │
└────────────────┬────────────────────┘
                 │
                 ▼
┌─────────────────────────────────────┐
│    Ultrasonic 1 Distance < 172cm?   │
│         (Floor Reached?)            │
└───┬─────────────────────────────┬───┘
   YES                            NO → CONTINUE LIFTING
    │
    ▼
┌─────────────────────────────────────┐
│        Stop Lift Motor              │
└────────────────┬────────────────────┘
                 │
                 ▼
┌─────────────────────────────────────┐
│    Ultrasonic 2 Distance > 50cm?    │
│        (Slot Available?)            │
└───┬─────────────────────────────┬───┘
   YES                            NO 
    │                              │
    ▼                              ▼
┌─────────────────────────┐  ┌─────────────────────────┐
│ Open Gate (Servo = 0°)  │  │ Close Gate (Servo = 90°)│
│ Start Conveyor Motor    │  └─────────────────────────┘
│ Park Vehicle            │
└─────────────────────────┘
```

---

## 🌐 Hardware Components

| Component | Function / Purpose |
|-----------|--------------------|
| **Arduino Uno** | Main microcontroller for logic processing |
| **IR Sensor** | Detects the presence of a car at the entrance |
| **Ultrasonic Sensor (HC-SR04) x2** | Measures vertical floor distance and parking slot availability |
| **L298N Motor Driver** | Controls the high-current DC motors for lifting and conveying |
| **DC Gear Motors** | Provides physical movement for the elevator and parking platform |
| **Servo Motor (SG90)** | Acts as the security barrier/gate for the parking slot |
| **Jumper Wires & Breadboard** | Circuit connections |
| **Power Supply** | Provides adequate voltage/current for motors and Arduino |

![Project Image](./2.jpeg)

*(Hardware prototype illustration)*

---

## 💡 Impact

| Beneficiary | Impact |
|-------------|--------|
| 🏢 **Building Owners** | Maximizes vehicle capacity in minimal square footage |
| 🚗 **Drivers** | Eliminates time spent searching for parking; automates the process |
| 🌍 **Environment** | Reduces emissions caused by vehicles circling to find parking |
| 🏙️ **Smart Cities** | Integrates seamlessly into modern automated urban infrastructure |

---

## 🛠️ Technology Stack

| Technology | Purpose |
|-----------|----------|
| **C++ / Arduino** | Core firmware embedded on the microcontroller |
| **Python** | Secondary serial monitoring and logic extension script |
| **Servo.h** | Arduino library for controlling the barrier gate |
| **NewPing.h** | Optimized library for precise ultrasonic sensor readings |

---

## 📁 Project Structure

```text
Automatic-Parking-Lift-using-Ardino-Uno/
│
├── Automatic Parking Lift using Ardino Uno.ino   # 🟢 Main Arduino firmware
├── Automatic Parking Lift using Ardino Uno.cpp   # 📄 C++ source reference
├── Automatic Parking Lift using Ardino Uno.py    # 🐍 Python serial monitoring script
├── 1.pdf                                         # 📚 Comprehensive Project Report
├── 2.jpeg                                        # 🖼️ Project Prototype Image
└── README.md                                     # 📖 This documentation
```

---

## 💻 Main Program

**File:** [`Automatic Parking Lift using Ardino Uno.ino`](./Automatic%20Parking%20Lift%20using%20Ardino%20Uno.ino)

```cpp
#include <Servo.h>
#include <NewPing.h> 

const int IRSensor = 9; 
const int ultrasonicTrigPin = 6; 
const int ultrasonicEchoPin = 7; 
const int DISTANCE_THRESHOLD1 = 172; 
const int DISTANCE_THRESHOLD2 = 50; 

Servo servo; 

void setup() {
    pinMode(IRSensor, INPUT); 
    pinMode(ultrasonicTrigPin, OUTPUT); 
    pinMode(ultrasonicEchoPin, INPUT); 
    servo.attach(3); 
    servo.write(0); 
    Serial.begin(9600); 
}

void loop() {
    if (digitalRead(IRSensor) == HIGH) {
        Serial.println("Car is detected!");
        // Motor logic to lift car goes here...
    } 
    
    // Check floor distance
    if (distance_cm < DISTANCE_THRESHOLD1) {
        // Stop lift motors
        Serial.print("First floor reached!");
    }
    
    // Check space availability
    if (distance_cm2 > DISTANCE_THRESHOLD2) {
        servo.write(0); // Open gate
        Serial.print("There is Free Space!");
        // Conveyor motor logic to move car into space...
    } else {
        servo.write(90); // Close gate
    }
}
```

---

## 🔍 Code Analysis

| Decision | Rationale |
|----------|-----------|
| **IR for Presence** | IR sensors provide immediate, reliable, and cost-effective binary detection for a car's arrival. |
| **Dual Ultrasonic Sensors** | Splitting responsibilities: one sensor dedicated to vertical lift positioning, the other to deep-slot scanning. |
| **NewPing Library** | Faster and more reliable than standard `pulseIn()` methods for ultrasonic distance calculation. |
| **Python Companion Script** | Allows for extending the system to a PC dashboard, logging arrival times, and processing external triggers. |

---

## 🚀 Installation & Usage

### Prerequisites
1. Download and install the [Arduino IDE](https://www.arduino.cc/en/software).
2. Install the **NewPing** library via the Arduino Library Manager (`Sketch` -> `Include Library` -> `Manage Libraries`).
3. (Optional) Install Python 3.x and the `pyserial` library if you intend to run the Python monitoring script.

### Setup Instructions
1. **Hardware Wiring**: Connect all sensors, the L298N module, motors, and the servo to the Arduino as defined in the `.ino` pin declarations.
2. **Upload Code**: 
   - Connect the Arduino Uno to your PC via USB.
   - Open `Automatic Parking Lift using Ardino Uno.ino`.
   - Select your COM port and board (`Arduino Uno`).
   - Click **Upload**.
3. **Monitor System**:
   - Open the **Serial Monitor** (set baud rate to `9600`).
   - Place an object in front of the IR sensor to simulate a vehicle.
   - Observe the lift mechanism logic activating and stopping based on ultrasonic sensor feedback.

---

## 🌟 Scope of Future Implementation

- **RFID Integration**: Automate user authentication and billing using RFID tags on the vehicles.
- **IoT Cloud Dashboard**: Use an ESP8266/ESP32 to push parking data (available slots, lift status) to a web application or mobile app.
- **Multi-Floor Scaling**: Expand the logic to support an array of ultrasonic sensors and specific floor heights for a multi-level parking tower.
- **Computer Vision (YOLO)**: Upgrade vehicle detection from basic IR to camera-based AI object detection to prevent false positives (e.g., humans triggering the lift).

---

## 🤝 Open Source Contribution

Contributions are welcome! If you have ideas to improve the motor efficiency, enhance the Python tracking script, or add IoT capabilities:
1. Fork the project.
2. Create your feature branch (`git checkout -b feature/AmazingFeature`).
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`).
4. Push to the branch (`git push origin feature/AmazingFeature`).
5. Open a Pull Request.

---


## 👨‍💻 Team Members & Author

**Arokiya Nithish J (Head and Ml Engineer)**
- 🎓 Department of AI & Data Science — Vel Tech University
- 💼 Domain: Deep Learning | Computer Vision | IoT | Community Service
- 🌐 GitHub: [@ArokiyaNithish](https://github.com/ArokiyaNithish)
- 💼 LinkedIn: [@Arokiya Nithish J](https://www.linkedin.com/in/arokiya-nithishj/)
- 📧 Email: arokiyanithishj@gmail.com
- 🌐 Portfolio: [arokiyanithish.github.io/portfolio/](https://arokiyanithish.github.io/portfolio/)

## 📄 License

> This is an open-source released under the Apache License to encourage learning, research, and social impact in road safety systems.
 you are free to use, modify, and distribute this code with attribution.

```
📄 License
This project is licensed under the Apache License 2.0 — you are free to use, modify, and distribute this code with proper attribution and compliance with the license terms.

Apache License
Version 2.0, January 2004
http://www.apache.org/licenses/

Copyright (c) 2026 Arokiya Nithish J 

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

```
http://www.apache.org/licenses/LICENSE-2.0  
```

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

```


See [LICENSE](LICENSE) for full details.


---
```
NOTICE

Project Name: 
Copyright (c) 2026 Arokiya Nithish J

This product includes software developed by Arokiya Nithish J.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at:

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

---

Modifications

If you have modified this project, you should add a statement here such as:

"This project has been modified by <Your Name/Organization> on <Date>.
Changes include: <brief description of changes>"

---

END OF NOTICE
```



<div align="center">

**⭐ If this project helped you or inspired your work, please give it a star! ⭐**

*Made with ❤️ for Community Service | Redhills, Chennai, India 🇮🇳*

*© 2025 — Arokiya Nithish J *

</div>

