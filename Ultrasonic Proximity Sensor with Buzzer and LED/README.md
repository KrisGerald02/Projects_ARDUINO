# 💡 Arduino: Ultrasonic Proximity Sensor with Buzzer and LCD Display

## 📌 Project Overview

This project uses an **Arduino**, an **ultrasonic sensor**, a **buzzer**, and two **LEDs** (red and green) to measure the distance to an object. When an object is detected within 50 cm, the red LED lights up, and a buzzer sounds at a reduced volume. When the object is farther than 50 cm, the green LED lights up and the buzzer stops.

## 🛠️ Components Required

- 1 Arduino R4 MINIMA
- 1 HC-SR04 Ultrasonic Sensor
- 1 Passive Buzzer
- 1 LED
- 1 Resistors 
- Jumper wires
- Breadboard
- 16x2 LCD Display with I2C module

## 🔗 Circuit Diagram

### Connections

- **HC-SR04 Ultrasonic Sensor**:
  - **VCC** to 5V on Arduino
  - **GND** to GND on Arduino
  - **Trig** to Pin A0 on Arduino
  - **Echo** to Pin A1 on Arduino

- **Buzzer**:
  - **Positive** to Pin 7 on Arduino
  - **Negative** to GND on Arduino

- **LEDs**:
  - **Red LED**: Pin 13 on Arduino
  - **Green LED**: Pin 11 on Arduino

- **LCD Display (with I2C)**:
  - **VCC** to 5V on Arduino
  - **GND** to GND on Arduino
  - **SDA** to A4 on Arduino
  - **SCL** to A5 on Arduino

Ensure that the **VCC**, **GND**, **SDA**, and **SCL** are correctly connected to the Arduino board.

## 📷 Demonstration  

[Video 1: Project Demonstration](https://github.com/user-attachments/assets/ea3c9951-1a28-4830-a195-5b68f4c5e07b)  
[Video 2: Project in Action](https://github.com/user-attachments/assets/aec03b70-1019-45c7-aa3d-2b10a44c811a)

![Project Image](https://github.com/user-attachments/assets/c9a0cb3a-f4b2-4a2d-a7f2-9950d79be0f9)

## 📝 Code

```cpp
#include <LiquidCrystal_I2C.h>

#define TRIG_PIN A0  // Cambiado a A0
#define ECHO_PIN A1  // Cambiado a A1
#define BUZZER_PIN 7  
#define LED_ROJO 13
#define LED_VERDE 11

// Declaración del LCD (dirección 0x27, 16 columnas, 2 filas)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Función para reducir volumen del buzzer pasivo
void bajarVolumenBuzzer(int pin, int frecuencia, int porcentaje) {
    int amplitud = map(porcentaje, 0, 100, 0, 255); // Convertir porcentaje a PWM
    for (int i = 0; i < 100; i++) { // Generar tono con menor amplitud
        analogWrite(pin, amplitud);
        delayMicroseconds(500000 / frecuencia); // Mitad del periodo
        analogWrite(pin, 0);
        delayMicroseconds(500000 / frecuencia);
    }
}

void setup() {
    Serial.begin(9600);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(LED_ROJO, OUTPUT);
    pinMode(LED_VERDE, OUTPUT);

    // Inicializar LCD
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("FUNCIONANDO");
}

void loop() {
    // Enviar pulso ultrasónico
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Medir el eco
    long duration = pulseIn(ECHO_PIN, HIGH);
    float distance = duration * 0.034 / 2;  // Convertir a cm

    Serial.print("Distancia: ");
    Serial.print(distance);
    Serial.println(" cm");

    lcd.clear();  // Mover fuera del if para evitar parpadeos
    lcd.setCursor(0,0);
    lcd.print("Distancia:");
    lcd.setCursor(0,1);
    lcd.print(distance);
    lcd.print(" cm");

    // Si está a 50 cm o menos, activar el buzzer con volumen reducido
    if (distance <= 50.0) {
        bajarVolumenBuzzer(BUZZER_PIN, 2000, 50);  // 50% de volumen a 2kHz
        digitalWrite(LED_ROJO, HIGH);
        digitalWrite(LED_VERDE, LOW);
    } else {
        digitalWrite(BUZZER_PIN, LOW);
        digitalWrite(LED_ROJO, LOW);
        digitalWrite(LED_VERDE, HIGH);
    }

    delay(250);  // Reducir el retardo para mejorar la respuesta
}

