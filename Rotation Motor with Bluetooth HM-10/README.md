# 🎛️ Rotation Motor with Bluetooth HM-10

## 📌 Project Overview  
This circuit uses a Bluetooth module (HM-10) and a microcontroller to wirelessly control two DC motors with encoder disks. The motors are driven by an H-bridge (L9110s), while encoder signals are read to monitor speed and direction. Ideal for robotics or mobile vehicles with real-time feedback and remote control.
## 🛠️ Components Required  
- Arduino R4 MINIMA
- Jumpers
- L9110
- TT Motor/Encoder Disk
- Bluetooth 4.0 Module HM-10 (iOS & Android)

## ⚡ Circuit with Fritzing  
![Image](https://github.com/user-attachments/assets/c44bee71-d00e-4a3a-9b27-788e1b1667a4)

## 📷 Demonstration  
[Video](https://github.com/user-attachments/assets/cf0fef01-a3b1-49c2-8a3e-75476ba32e8e)


## 📝 Code  
```cpp
/![Image](https://github.com/user-attachments/assets/54e52405-3f65-4a3c-8b37-f1023256f0ed)
#include <SoftwareSerial.h>

// Pines motores L9110S
const int motorA_IA = 9;
const int motorA_IB = 10;
const int motorB_IA = 5;
const int motorB_IB = 6;

// Pines encoder
const int encoder1Pin = 2;  // Interrupt 0
const int encoder2Pin = 3;  // Interrupt 1

// Pines Bluetooth JDY-31
const int bluetoothTx = 3;  // TX del Arduino (a RX del módulo)
const int bluetoothRx = 4;  // RX del Arduino (a TX del módulo)
SoftwareSerial bleSerial(bluetoothTx, bluetoothRx);

// Variables pulsos
volatile int pulsos1 = 0;
volatile int pulsos2 = 0;

void contarPulsos1() {
  pulsos1++;
}

void contarPulsos2() {
  pulsos2++;
}

void setup() {
  Serial.begin(9600);
  bleSerial.begin(9600);

  // Configurar pines de motores
  pinMode(motorA_IA, OUTPUT);
  pinMode(motorA_IB, OUTPUT);
  pinMode(motorB_IA, OUTPUT);
  pinMode(motorB_IB, OUTPUT);

  // Iniciar motores hacia adelante
  digitalWrite(motorA_IA, HIGH);
  digitalWrite(motorA_IB, LOW);
  digitalWrite(motorB_IA, HIGH);
  digitalWrite(motorB_IB, LOW);

  // Configurar pines encoder
  pinMode(encoder1Pin, INPUT_PULLUP);
  pinMode(encoder2Pin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(encoder1Pin), contarPulsos1, RISING);
  attachInterrupt(digitalPinToInterrupt(encoder2Pin), contarPulsos2, RISING);
}

void loop() {
  // Mostrar pulsos por Serial
  Serial.print("Pulsos Motor A: ");
  Serial.print(pulsos1);
  Serial.print(" | Pulsos Motor B: ");
  Serial.println(pulsos2);

  // Mostrar pulsos por Bluetooth
  bleSerial.print("Pulsos Motor A: ");
  bleSerial.print(pulsos1);
  bleSerial.print(" | Pulsos Motor B: ");
  bleSerial.println(pulsos2);

  pulsos1 = 0;
  pulsos2 = 0;

  delay(1000);

  // Comunicación bidireccional entre Serial y Bluetooth
  if (bleSerial.available()) {
    Serial.write(bleSerial.read());
  }
  if (Serial.available()) {
    bleSerial.write(Serial.read());
  }
}
