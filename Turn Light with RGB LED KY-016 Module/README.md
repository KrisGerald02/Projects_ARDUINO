# 🚦 Arduino: Flashing Traffic Light with RGB LED KY-016

## 📌 Project Overview

This project simulates a flashing traffic light using an **Arduino** and the **RGB LED KY-016 module**. The LEDs will turn on and off in sequence: red → yellow → green, and back to red. The RGB LED module is used to control the color of the traffic light.

## 🛠️ Components Required

- 1 Arduino R4 MINIMA
- 1 RGB LED KY-016 Module
- Breadboard

## 🔗 Circuit Diagram

### RGB LED Module (KY-016)

- **Red pin**: digital pin 8
- **Green pin**: digital pin 10
- **Blue pin**: digital pin 9

Each of these pins connects to the corresponding pins of the RGB LED module.

## 📷 Demonstration  
[Demo Video](https://github.com/user-attachments/assets/9ebf5906-7f20-418a-9526-22202c94bb8a)

## 📝 Code

```cpp
// Semáforo Parpadeante con RGB LED KY-016
// Definir pines del módulo RGB LED
#define LED_ROJO 8
#define LED_AMARILLO 9
#define LED_VERDE 10

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

    // Encender los tres LEDs (rojo, amarillo, verde) a la vez
    digitalWrite(LED_ROJO, HIGH);
    digitalWrite(LED_AMARILLO, HIGH);
    digitalWrite(LED_VERDE, HIGH);
    delay(2000);  // Mantener los tres LEDs encendidos 2 segundos

    // Volver a ROJO
}
