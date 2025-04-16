# 🎛️ Rotation Motor with Bluetooth & Infrared Distance Sensor

## 📌 Project Overview  
This circuit uses a Bluetooth module (HM-10) and a microcontroller (Arduino R4 MINIMA) to wirelessly control two DC motors with encoder disks. The motors are driven by an H-bridge (L9110s), while encoder signals are read to monitor speed and direction. Additionally, an infrared distance sensor (GP2Y0A21YK0F) is included for object detection or distance measurement. This setup is ideal for robotics or mobile vehicles that require real-time feedback and remote control.

## 🛠️ Components Required  
- Arduino R4 MINIMA  
- Jumper wires  
- L9110 H-bridge driver  
- TT Motor with Encoder Disk  
- Bluetooth 4.0 Module HM-10 (compatible with iOS & Android)  
- Infrared Distance Sensor GP2Y0A21YK0F

## ⚡ Circuit with Fritzing  
![Image](https://github.com/user-attachments/assets/d8d75307-9241-4991-9913-4cba81a7e21f)

## 📷 Demonstration  
[Video](https://github.com/user-attachments/assets/094789ea-9dd0-48c0-bfd1-7745186b18ff)

## 📝 Code  
```cpp
#include <SoftwareSerial.h>
#include <math.h>

// Pines motores L9110S
const int motorA_IA = 9;
const int motorA_IB = 10;
const int motorB_IA = 5;
const int motorB_IB = 6;

// Pines encoder
const int encoder1Pin = 2;  // Interrupt 0
const int encoder2Pin = 3;  // Interrupt 1

// Pines Bluetooth JDY-31
const int bluetoothTx = 11;  // TX del Arduino (a RX del módulo)
const int bluetoothRx = 4;   // RX del Arduino (a TX del módulo)
SoftwareSerial bleSerial(bluetoothTx, bluetoothRx);

// Pines sensor IR
#define sensorIR A0

// Variables conteo sensor IR
int conteo = 0;
bool objetoDetectado = false;

// Tiempo de ejecución
unsigned long tiempoInicio;
const unsigned long duracion = 30000; // 30 segundos
bool enEjecucion = true;

// Variables encoder
volatile int pulsos1 = 0;
volatile int pulsos2 = 0;

void contarPulsos1() {
  pulsos1++;
}

void contarPulsos2() {
  pulsos2++;
}

void detenerMotores() {
  digitalWrite(motorA_IA, LOW);
  digitalWrite(motorA_IB, LOW);
  digitalWrite(motorB_IA, LOW);
  digitalWrite(motorB_IB, LOW);
}

void iniciarMotores() {
  digitalWrite(motorA_IA, HIGH);
  digitalWrite(motorA_IB, LOW);
  digitalWrite(motorB_IA, HIGH);
  digitalWrite(motorB_IB, LOW);
}

void reiniciarProceso() {
  conteo = 0;
  pulsos1 = 0;
  pulsos2 = 0;
  objetoDetectado = false;
  tiempoInicio = millis();
  enEjecucion = true;
  iniciarMotores();

  Serial.println("\nReinicio solicitado por Bluetooth.");
  Serial.println("Iniciando nuevo conteo de 30 segundos...");
  bleSerial.println("\nReinicio solicitado por Bluetooth.");
  bleSerial.println("Iniciando nuevo conteo de 30 segundos...");
}

void setup() {
  Serial.begin(9600);
  bleSerial.begin(9600);

  // Configurar pines de motores
  pinMode(motorA_IA, OUTPUT);
  pinMode(motorA_IB, OUTPUT);
  pinMode(motorB_IA, OUTPUT);
  pinMode(motorB_IB, OUTPUT);

  iniciarMotores();

  // Configurar pines encoder
  pinMode(encoder1Pin, INPUT_PULLUP);
  pinMode(encoder2Pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoder1Pin), contarPulsos1, RISING);
  attachInterrupt(digitalPinToInterrupt(encoder2Pin), contarPulsos2, RISING);

  Serial.println("Iniciando conteo por 30 segundos...");
  bleSerial.println("Iniciando conteo por 30 segundos...");
}

void loop() {
  if (enEjecucion) {
    unsigned long tiempoActual = millis();

    // Lectura del sensor IR
    float volts = analogRead(sensorIR) * 0.0048828125;
    int distancia = 13 * pow(volts, -1);

    if (distancia <= 15) {
      if (!objetoDetectado) {
        conteo++;
        objetoDetectado = true;

        Serial.print("Objeto detectado. Total: ");
        Serial.println(conteo);
        bleSerial.print("Objeto detectado. Total: ");
        bleSerial.println(conteo);
      }
    } else {
      objetoDetectado = false;
    }

    // Mostrar pulsos por Serial y Bluetooth
    Serial.print("Pulsos Motor A: ");
    Serial.print(pulsos1);
    Serial.print(" | Pulsos Motor B: ");
    Serial.println(pulsos2);

    bleSerial.print("Pulsos Motor A: ");
    bleSerial.print(pulsos1);
    bleSerial.print(" | Pulsos Motor B: ");
    bleSerial.println(pulsos2);

    pulsos1 = 0;
    pulsos2 = 0;

    // Verificar si terminó el tiempo
    if (tiempoActual - tiempoInicio >= duracion) {
      enEjecucion = false;
      detenerMotores();

      float eficiencia = (conteo / 20.0) * 100.0;

      Serial.println("\nTiempo finalizado.");
      Serial.print("Total de productos detectados: ");
      Serial.println(conteo);
      Serial.print("Eficiencia: ");
      Serial.print(eficiencia);
      Serial.println("%");

      bleSerial.println("\nTiempo finalizado.");
      bleSerial.print("Total de productos detectados: ");
      bleSerial.println(conteo);
      bleSerial.print("Eficiencia: ");
      bleSerial.print(eficiencia);
      bleSerial.println("%");

      Serial.println("Envía 'r' por Bluetooth para reiniciar.");
      bleSerial.println("Envía 'r' por Bluetooth para reiniciar.");
    }

    delay(200); // Retardo para lectura IR
  }

  // Comunicación Serial <-> Bluetooth
  if (bleSerial.available()) {
    char comando = bleSerial.read();

    // También reflejar por serial
    Serial.write(comando);

    // Reinicio por comando
    if (!enEjecucion && comando == 'r') {
      reiniciarProceso();
    }
  }

  if (Serial.available()) {
    char entrada = Serial.read();
    bleSerial.write(entrada);
  }
}
