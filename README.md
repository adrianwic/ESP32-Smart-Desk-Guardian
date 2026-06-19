# ESP32 Smart Desk Guardian

<img width="1000" height="750" alt="esp32_zdjecie" src="https://github.com/user-attachments/assets/3e46a8f7-7af4-47d7-8ab9-ac1ee2090e2d" />

## Overview
This is an embedded systems hardware project built on the ESP32 microcontroller, functioning as an automated proximity radar and desk security system. It actively monitors the physical environment using an ultrasonic sensor, visualizes the distance of approaching objects in real-time on a 10-segment LED bar graph, and triggers a physical reaction—raising a servo-driven barrier and flashing an alarm—when an object breaches the 12 cm security zone.

## Technical Highlights & Features
* **Hardware Integration:** Synchronizes multiple distinct hardware components, including an HC-SR04 ultrasonic sensor, a 74HC595 shift register, and an SG90 servo motor, into a single responsive system.
* **Power Management (Brownout Prevention):** Implements a software-level soft start (incremental for loops with delays) for the servo motor. This prevents sudden current spikes (inrush current) that typically cause voltage drops and microcontroller resets (brownouts).
* **Bitwise Operations:** Utilizes bit shifting (1 << numLeds) - 1 and hexadecimal data manipulation (0xFF, 0x00) to control the LED bar graph efficiently via the shift register.
* **State Management:** Uses boolean flags (isAlarmActive) to track the operational state of the system. This prevents redundant signals to the servo, ensuring smooth, stutter-free mechanical movements and preventing the loop from getting stuck.
* **Data Mapping & Constraints:** Dynamically translates raw physical distance data (cm) into a proportional visual representation (0-8 LEDs) using mathematical mapping and constraint functions.

## Project Structure
* Smart_Desk_Guardian.ino - The main Arduino sketch containing the setup, primary echolocation loop, state machine logic, and shift register helper functions.
* **Hardware Requirements:** ESP32 board, HC-SR04 Ultrasonic Sensor, 74HC595 Shift Register, 10-Segment LED Bar Graph, SG90 Servo Motor.

## How to Run
This project is written in standard C++ for Arduino. 
1. Open the .ino file in the Arduino IDE.
2. Go to **Tools -> Manage Libraries** and install the ESP32Servo library.
3. Connect your ESP32 to the computer, select the correct COM port and board type.
4. Click **Upload**. 

*Note: Ensure the SG90 servo is powered by a stable 5V pin (VIN/VBUS) and not the 3.3V logic pin to prevent system crashes during motor startup.*
