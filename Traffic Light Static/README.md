# 🚦 Arduino: Static Traffic Light

## 📌 Project Overview

This project involves turning on the three LEDs of a traffic light (red, yellow, and green) simultaneously and keeping them on. The LEDs are lit up at the same time and remain on statically.

## 🛠️ Components Required

- 1 Arduino R4 MINIMA
-  Traffic Light LEDs.
- Breadboard

## 📷 Demonstration  
https://github.com/user-attachments/assets/1dd9aacc-23fa-4e10-8b42-57b4fd149bff

## 📝 Code

```cpp
// Static Traffic Light
void setup() {
  // Set pins as output
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {
  // Turn on all three LEDs
  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(11, HIGH);
}
