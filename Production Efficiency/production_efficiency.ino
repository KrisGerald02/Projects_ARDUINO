#include <SoftwareSerial.h>
// Pines del sensor infrarrojo 
#define sensorIR A0
int conteo = 0;
bool objetoDetectado = false;
// Aqui puedo ajustar el tiempo le puse 60seg
unsigned long tiempoInicio;
const unsigned long duracion = 60000;
bool enEjecucion = true;

//Bluetooth JDY-31
const int bluetoothTx = 3;
const int bluetoothRx = 4;
SoftwareSerial bleSerial(bluetoothTx, bluetoothRx);

// Encoder
const int motorA = 9;
const int motorB = 10;
const int encoderPin = 2;  // Uso pin 2 para interrumpir

volatile int pulsos = 0;

void contarPulsos() {
  pulsos++;
}

void setup() {
  // Iniciar serial y bluetooth
  Serial.begin(9600);
  bleSerial.begin(9600);

  // configuro el motor
  pinMode(motorA, OUTPUT);
  pinMode(motorB, OUTPUT);

  // configuro encoder
  pinMode(encoderPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderPin), contarPulsos, RISING);

  // Iniciar conteo
  tiempoInicio = millis();
  Serial.println("Iniciando conteo por 1 minuto...");
}

void loop() {
  // me comunico con el bluetooth
  if (bleSerial.available()) {
    Serial.write(bleSerial.read());
  }
  if (Serial.available()) {
    bleSerial.write(Serial.read());
  }

  // Motor gira en sentido horario
  digitalWrite(motorA, HIGH);
  digitalWrite(motorB, LOW);

  // Conteo por sensor infrarrojo
  if (enEjecucion) {
    unsigned long tiempoActual = millis();

    if (tiempoActual - tiempoInicio >= duracion) {
      enEjecucion = false;

      float eficiencia = (conteo / 20.0) * 100.0;

      Serial.println("\nTiempo finalizado.");
      Serial.print("Total de productos detectados: ");
      Serial.println(conteo);

      Serial.print("Eficiencia: ");
      Serial.print(eficiencia);
      Serial.println("%");

      return;
    }

    float volts = analogRead(sensorIR) * 0.0048828125;
    int distancia = 13 * pow(volts, -1);

    Serial.print("Distancia: ");
    Serial.print(distancia);
    Serial.println(" cm");

    if (distancia <= 15) {
      if (!objetoDetectado) {
        conteo++;
        objetoDetectado = true;
        Serial.print("Objeto detectado. Total: ");
        Serial.println(conteo);
      }
    } else {
      objetoDetectado = false;
    }

    // Mostrar pulsos por segundo del encoder
    Serial.print("Pulsos: ");
    Serial.println(pulsos);
    pulsos = 0;

    delay(200);  // evitar doble conteo y dar tiempo al motor
  }
}

