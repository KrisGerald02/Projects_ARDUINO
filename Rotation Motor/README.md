# 🎛️ Rotation Motor

## 📌 Project Overview  
This project focuses on controlling the rotation direction and speed feedback of a DC motor with encoder using an Arduino R4 MINIMA, a L9110 motor driver, and a TT motor with encoder disk. The motor alternates between clockwise and counterclockwise rotation, while measuring the number of pulses per second from the encoder for feedback.


## 🛠️ Components Required  
- Arduino R4 MINIMA
- Jumpers
- L9110
- TT Motor/Encoder Disk

## ⚡ How to Use  
1. Connect the **DHT11 sensor** and **LCD display** to the Arduino as per the circuit diagram.  
2. Install the necessary libraries:  
   - `Encoder` by Paul
3. Upload the provided code to your Arduino.  

## 📷 Demonstration  
![Video](https://github.com/user-attachments/assets/c8c5f09c-f527-4cd4-be84-b745afc836f2)
![Image](https://github.com/user-attachments/assets/54e52405-3f65-4a3c-8b37-f1023256f0ed)


## 📝 Code  
```cpp
// Pines del motor
const int motorA = 9;  // Dirección A
const int motorB = 10; // Dirección B

// Encoder (sensor de pulsos)
const int encoderPin = 3;  // Interrupt 1 en Arduino UNO

volatile int pulsos = 0;  // Pulsos contados del encoder

void contarPulsos() {
  pulsos++;  // Se llama cada vez que el encoder genera un pulso
}

void setup() {
  // Configurar motor
  pinMode(motorA, OUTPUT);
  pinMode(motorB, OUTPUT);

  // Configurar encoder
  pinMode(encoderPin, INPUT_PULLUP);  // Pull-up para evitar ruido
  attachInterrupt(digitalPinToInterrupt(encoderPin), contarPulsos, RISING);

  Serial.begin(9600);
}

void loop() {
  // Mover el motor hacia una dirección
  // Gira al sentido horario
  digitalWrite(motorA, HIGH);
  digitalWrite(motorB, LOW);
  delay(2000);

  // Gira al sentido antihorario
  digitalWrite(motorA, LOW);
  digitalWrite(motorB, HIGH);
  delay(2000);


  // Esperar un segundo para contar pulsos
  delay(1000);

  // Mostrar cuántos pulsos se detectaron en 1 segundo
  Serial.print("Pulsos por segundo: ");
  Serial.println(pulsos);

  // Reiniciar contador
  pulsos = 0;

  // Si querés parar el motor después de cierto tiempo:
  // digitalWrite(motorA, LOW);
  // digitalWrite(motorB, LOW);
}
