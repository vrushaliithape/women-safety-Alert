#  Women Safety Alert IoT System (ESP32)

## Project Overview
An automated safety system built on the **ESP32** platform that uses an **I2S microphone** to continuously monitor for sharp, abnormal sound events . Upon detection, the device immediately uses the Wi-Fi connection to:

1.  Flash an indicator LED.
2.  Determine its approximate **geographic location** (via IP Geolocation API).
3.  Send an **urgent email alert** to a designated recipient, including the location details.

## 🎥 Project Demo 


[Watch the Full Project Demo Here]
(https://drive.google.com/file/d/1wJDoBH7Qt-Dm3v584BKG1vMfavGcXAYN/view?usp=drive_link)

## ✨ Key Features & Technical Details
* **Real-time Audio Processing:** Utilizes the ESP32's I2S peripheral for efficient digital audio capture.
* **Network Integration:** Connects to Wi-Fi and uses `HTTPClient` to communicate with a public geolocation API (`ip-api.com/json`).
* **Secure Alerting:** Implements the SMTP protocol via the `ESP_Mail_Client` library for reliable email delivery.
* **Security Best Practice:** Credentials (passwords/emails) are managed using a local `config.h` file.

## 🛠 Hardware and Setup

This project, "WomenSafetyAlert," is built around the ESP32 microcontroller for real-time sensing and communication. The primary input is an I2S microphone for acoustic event detection.

### 🔌 Component Breakdown

| Component | Purpose | Configured Pins (ESP32 GPIO) |
| :--- | :--- | :--- |
| **Microcontroller** | Core processing, Wi-Fi connectivity, and I/O control. | **N/A** (Standard Power/Debug Pins) |
| **I2S Microphone** | Captures high-quality digital audio for processing and alert triggering. | **WS** (15), **SD** (32), **SCK** (14) |
| **Libraries** | Handles external services like email alerts and network communication. | **N/A** (Software-based) |

> **Note on I2S Pin Names:**
> * **WS** (Word Select / LRCLK) is connected to **GPIO 15**.
> * **SD** (Serial Data / DOUT) is connected to **GPIO 32**.
> * **SCK** (Serial Clock / BCLK) is connected to **GPIO 34**.





### How to Configure Credentials
1.  Copy the template file `src/config.example.h` and rename the copy to `src/config.h`.
2.  Fill in your actual Wi-Fi and **Gmail App Password** in `src/config.h`.

### 3. Compilation and Upload
1.  Open the `src/main.cpp` file in the Arduino IDE or VS Code (with PlatformIO).
2.  Select your ESP32 board and click **Upload**.

## 👥 Team / Contributors

This project was developed as a collaborative effort by the following team members:


---

## 👥 Team / Contributors

This project was developed as a collaborative effort by the following team members:

| Name | Role / Primary Contributions | Reference (e.g., GitHub, Email) |
| :--- | :--- | :--- |
| **Srushti Ingle** | Project Lead, I2S Integration, Hardware Prototyping | ** |
| **Vrushali Ithape** | Alert Logic (Sound Detection), Email Integration, Testing | 
| **Gurav Prachi** | Geolocation API Implementation, Documentation, Backend Review | *
| **Ghode Vaishnavi** | Email Alert System using ESP_Mail_Client, managing SMTP credentials, drafting the README.md and Documentation.




---a** | 

---