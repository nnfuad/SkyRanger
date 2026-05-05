# SkyRanger Drone Project (RUET ECE 2200)

## Overview
SkyRanger is a manually built quadcopter flight controller system developed as part of **Electronic Shop Practice (ECE 2200)** at **Rajshahi University of Engineering & Technology (RUET)**.

The project implements a low-level flight controller using:
- Arduino-based embedded control
- MPU6050 IMU sensor
- PID stabilization algorithm
- ESC calibration and motor control pipeline

This system is inspired by the YMFC-AL architecture and adapted for academic prototyping and learning.

---

## Academic Context

- **Department:** Electrical & Computer Engineering, RUET  
- **Course:** ECE 2200 – Electronic Shop Practice  
- **Semester:** 2nd Year, Even Semester  
- **Submitted To:**  
  - (Md. Omaer Faruq Goni) [https://www.ruet.ac.bd/omaerfaruq] (Assistant Professor, Department of ECE, RUET)  
  - (Oishi Jyoti) [https://www.ruet.ac.bd/ojruet] (Assistant Professor, Department of ECE, RUET)  
- **Submission Date:** January 10, 2026  

The full structured report follows RUET academic guidelines :contentReference[oaicite:0]{index=0}

---

## Repository Structure

```

SkyRanger/
│
├── EEPROM/
├── SkyRanger_AL_setup_FINAL/
├── SkyRanger-AL_esc_calibrate/
├── SkyRanger-AL_Flight_controller/
├── SkyRanger_schematic.pdf
├── SkyRangerReport.pdf

```

### Description

| Folder/File | Purpose |
|------------|--------|
| `EEPROM/` | EEPROM clearing utilities |
| `SkyRanger_AL_setup_FINAL/` | Sensor calibration & initial setup |
| `SkyRanger-AL_esc_calibrate/` | ESC calibration program |
| `SkyRanger-AL_Flight_controller/` | Main flight control firmware |
| `SkyRanger_schematic.pdf` | Circuit diagram |
| `SkyRangerReport.pdf` | Full academic report |

---

## System Architecture

The system follows a standard quadcopter control loop:

```

MPU6050 → Sensor Fusion → PID Controller → ESC Signals → Motors

```

Core concepts implemented:
- IMU-based orientation estimation
- Complementary filtering
- PID stabilization (Roll, Pitch, Yaw)
- PWM-based ESC control

The implementation is based on YMFC-AL firmware principles :contentReference[oaicite:1]{index=1}

---

## Hardware Components

- Arduino (Uno / Nano)
- MPU6050 (Gyroscope + Accelerometer)
- Brushless motors (x4)
- ESCs (Electronic Speed Controllers)
- Li-Po Battery
- Frame + Propellers

---

## Software Workflow (CRITICAL)

The order of execution is **strict**. Skipping steps will cause instability or failure.

### Step 1: Clear EEPROM
- Upload EEPROM clearing code
- Ensures no residual calibration data

### Step 2: Setup (Calibration)
- Upload `SkyRanger_AL_setup_FINAL`
- Performs:
  - Gyro calibration
  - Sensor bias correction
  - Initial parameter storage

### Step 3: ESC Calibration
- Upload `SkyRanger-AL_esc_calibrate`
- Calibrate throttle range of all ESCs

⚠️ Known issue (from YMFC):
Serial input buffering must be handled carefully to avoid program halt :contentReference[oaicite:2]{index=2}

### Step 4: Flight Controller
- Upload `SkyRanger-AL_Flight_controller.ino`
- Final system ready for flight

---

## Key Features

- Fully manual flight controller (no autopilot)
- PID-based stabilization
- Low-cost implementation
- Educational focus on control systems and embedded design

---

## PID Control

The drone stability relies on:

```

PID = Kp * error + Ki * ∫error dt + Kd * d(error)/dt

```

Where:
- **Kp** → Responsiveness
- **Ki** → Drift correction
- **Kd** → Oscillation damping

Improper tuning leads to:
- Oscillation (high Kp)
- Drift (low Ki)
- Noise sensitivity (high Kd)

---

## Limitations

This is not a production-grade system. Key constraints:

- No GPS / autonomous navigation
- No altitude hold
- No failsafe system
- Sensitive to tuning errors
- Limited robustness under aggressive maneuvers (NaN issue noted in YMFC logs :contentReference[oaicite:3]{index=3})

---

## Safety Notes

- Always remove propellers during testing
- Calibrate ESCs carefully
- Use stable power supply
- Avoid aggressive throttle changes during initial tests

---

## Results Summary

- Successful stabilization achieved
- Controlled hover possible after tuning
- System demonstrates practical implementation of control theory

Full testing and analysis available in:
```

SkyRangerReport.pdf

```

---

## Future Improvements

Based on project limitations:

- Add altitude hold (barometer)
- Implement GPS-based navigation
- Add wireless telemetry
- Improve filtering (Kalman filter)
- Integrate failsafe mechanisms

---

## Learning Outcomes

This project demonstrates:

- Embedded systems design
- Sensor interfacing (MPU6050)
- Real-time control systems (PID)
- Power electronics (ESC control)
- Debugging under hardware constraints

---


## Author

**SkyRanger Team**  
Project and Software Lead: (Nur Nafis Fuad) [https://github.com/nnfuad]
Project and Hardware Lead: (Gulam Gilani Hassan) [https://github.com/xilanihasan]
Logistics Management: (Kifayat Mashud Nitol) [https://web.facebook.com/kifayat.nitol?mibextid=ZbWKwL&_rdc=1&_rdr#]
Finance and Creative Support: (Huzayfa Bin Jamal) [https://www.linkedin.com/in/md-hujayfa-bin-jamal-992359281?utm_source=share_via&utm_content=profile&utm_medium=member_android]

Department of Electrical & Computer Engineering  
Rajshahi University of Engineering & Technology (RUET)

---

## Final Note

This project prioritizes **learning over abstraction**.  
Every instability, bug, and calibration issue is part of the engineering process.

```

---
