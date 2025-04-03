# 💡 Arduino: Adjustable LED Brightness with Rotation Sensor

## 📌 Project Overview

This project uses an **Arduino** to control the brightness of an LED based on the input from a **rotation sensor** (e.g., a potentiometer). The LED's brightness is adjusted by rotating the sensor, and the Arduino reads the sensor’s value to change the brightness of the connected LED.

## 🛠️ Components Required

- 1 Arduino R4 MINIMA
- 1 LED
- 1 Potentiometer (or rotation sensor)
- 1 Resistor (220Ω for the LED)
- Jumper wires
- Breadboard

## 🔗 Circuit Diagram

### Connections

- **LED**: Connected to pin 9 of the Arduino.
- **Potentiometer/Sensor**: Connected to analog pin A0.

Ensure the potentiometer has one leg connected to **5V**, another to **GND**, and the middle leg to **A0** on the Arduino for the sensor reading.

## 📷 Demonstration  
!https://github.com/user-attachments/assets/f424ab64-1817-4234-b7df-ddb81012aca8
!https://github.com/user-attachments/assets/d00e1b8b-fd04-44bc-b2d7-47b656c7b5df

## 📝 Code

```cpp
#define LED 9        // Pin del LED
#define SENSOR A0   // Pin del sensor de rotación

void setup() {
    pinMode(LED, OUTPUT);
    pinMode(SENSOR, INPUT);
}

void loop() {
    int valorSensor = analogRead(SENSOR);  // Leer el valor del potenciómetro (0-1023)
    int brillo = map(valorSensor, 0, 1023, 255, 0);  // Convertir a rango de brillo (255=máximo, 0=mínimo)

    analogWrite(LED, brillo);  // Ajustar el brillo del LED
    delay(10);  // Pequeña pausa para estabilidad
}
