# 🚦 Arduino: Flashing Traffic Light

## 📌 Project Overview

This project simulates a flashing traffic light system using **Arduino** and three LEDs (red, yellow, and green). The LEDs turn on in sequence: red → yellow → green, and back to red. Each LED stays on for a set amount of time to represent a typical traffic light cycle.

## 🛠️ Components Required

- 1 Arduino R4 Minima
- Traffic Light LED
- Breadboard

## 🔗 Circuit Diagram

### LEDs

- Red LED: digital pin 13
- Yellow LED: digital pin 12
- Green LED: digital pin 11

Each LED should be connected to its respective pin on the Arduino board, using a 220-ohm resistor in series to protect the LEDs from potential damage due to overcurrent.

## 📷 Demonstration  
[Demo Video](https://github.com/user-attachments/assets/fb412331-d15f-4a29-9267-cd789ba54e75)

## 📝 Code

```cpp
// Semáforo Parpadeante
// Definir pines del módulo semáforo
#define LED_ROJO 13
#define LED_AMARILLO 12
#define LED_VERDE 11

void setup() {
    pinMode(LED_ROJO, OUTPUT);
    pinMode(LED_AMARILLO, OUTPUT);
    pinMode(LED_VERDE, OUTPUT);
}

void loop() {
    // Encender ROJO (detener)
    digitalWrite(LED_ROJO, HIGH);
    digitalWrite(LED_AMARILLO, LOW);
    digitalWrite(LED_VERDE, LOW);
    delay(5000);  // Mantener el rojo encendido 5 segundos

    // Encender AMARILLO (precaución)
    digitalWrite(LED_ROJO, LOW);
    digitalWrite(LED_AMARILLO, HIGH);
    digitalWrite(LED_VERDE, LOW);
    delay(2000);  // Mantener el amarillo encendido 2 segundos

    // Encender VERDE (avanzar)
    digitalWrite(LED_ROJO, LOW);
    digitalWrite(LED_AMARILLO, LOW);
    digitalWrite(LED_VERDE, HIGH);
    delay(5000);  // Mantener el verde encendido 5 segundos

    // Volver a ROJO
}
