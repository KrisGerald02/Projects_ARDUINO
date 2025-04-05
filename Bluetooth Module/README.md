# 🛜 Bluetooth Module

## 📌 Project Overview  
This project uses an **Arduino**, involves developing a wireless communication system that allows controlling a device via Bluetooth technology. The HC-05 Bluetooth module is connected to a development board (such as an Arduino R4 MINIMA), which receives commands from a mobile application developed for Android (Called Serial Bluetooth).

## 🛠️ Components Required  
- Arduino R4 MINIMA
- Jumpers
- Bluetooth Module
- Breadboard

## 🛠️ Software Required
- Serial Bluetooth (Android/PlayStore)
- IDE Arduino

## 👣 Steps
- The computer isnt conected to bluetooth
- Go to Serial Monitor with the command Command + Shift + M
- Select the options Both NL & CR and 9600 baud
- Enter the command AT+NAME, AT+NAME+nameofdevice, AT+BAUD
- Install in Android the software Serial Bluetooth
- Connect Bluetooth to JDY-31-SPP (password:1234)
- Connect Bluetooth to namedevice
- Open Serial terminal, go to Menu/Devices and check if your device is connected
- Them enter a message in the pc or smartphone

## ⚡ How to Use  
1. Connect the **DHT11 sensor** and **LCD display** to the Arduino as per the circuit diagram.  
2. Install the necessary libraries:  
   - `Sotware Serial` by Jueff
3. Upload the provided code to your Arduino.  

## Circuit with Tintercad
![Image](https://github.com/user-attachments/assets/71a8dec8-8860-49fa-914f-ef0dfd7f92d8)

## 📷 Demonstration  
![Image](https://github.com/user-attachments/assets/0c4ae8a7-318f-4201-ae95-53aec51e8e55)
![Image](https://github.com/user-attachments/assets/039912be-8f27-4c29-a480-46ad07e46770)
![Image](https://github.com/user-attachments/assets/ca3cc615-10a1-4df9-9270-12d1696057f9)

## + Resources
https://docs.sunfounder.com/projects/umsk/en/latest/02_arduino/uno_lesson36_bluetooth.html

## 📝 Code  
```cpp
/*
  The code establishes a software serial communication using Arduino’s 
  SoftwareSerial library, allowing the Arduino to communicate with the 
  JDY-31 Bluetooth module through its digital pins 3 and 4 (as Rx and Tx). It 
  checks for data transfer between them, forwarding received messages from one 
  to the other at a baud rate of 9600. With this code, you can use the 
  Arduino’s serial monitor to send AT firmware commands to the JDY-31 Bluetooth 
  module and receive its responses.
*/

// Set up Bluetooth module communication
#include <SoftwareSerial.h>
const int bluetoothTx = 3;                           // bluetooth tx to 3 pin
const int bluetoothRx = 4;                           // bluetooth rx to 4 pin
SoftwareSerial bleSerial(bluetoothTx, bluetoothRx);  // Declare SoftwareSerial object for Bluetooth communication

void setup() {
  Serial.begin(9600);
  bleSerial.begin(9600);
}

void loop() {
  if (bleSerial.available()) {
    Serial.write(bleSerial.read());
  }
  if (Serial.available()) {
    bleSerial.write(Serial.read());
  }
}
