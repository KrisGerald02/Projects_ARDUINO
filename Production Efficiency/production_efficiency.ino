#include <SoftwareSerial.h>
#include <math.h>

// Pines motores L9110S
const int motorA_IA = 9;
const int motorA_IB = 10;
const int motorB_IA = 5;
const int motorB_IB = 6;

// Pines Bluetooth JDY-31
const int bluetoothRx = 4;   // RX del Arduino (conectado a TX del módulo)
const int bluetoothTx = 11;  // TX del Arduino (conectado a RX del módulo)
SoftwareSerial bleSerial(bluetoothRx, bluetoothTx); // (RX, TX)

// Sensor IR
#define sensorIR A0

// Variables de conteo
int conteo = 0;
bool objetoDetectado = false;

// Tiempo
unsigned long tiempoInicio;
const unsigned long duracion = 15000; // 15 segundos
bool enEjecucion = true;

// Meta esperada
const int cantidadEsperada = 20;

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
  objetoDetectado = false;
  tiempoInicio = millis();
  enEjecucion = true;
  iniciarMotores();

  Serial.println("\nReinicio solicitado por Bluetooth.");
  Serial.println("Iniciando nuevo conteo de 15 segundos...");
  bleSerial.println("\nReinicio solicitado por Bluetooth.");
  bleSerial.println("Iniciando nuevo conteo de 15 segundos...");
}

void setup() {
  Serial.begin(9600);
  bleSerial.begin(9600);

  pinMode(motorA_IA, OUTPUT);
  pinMode(motorA_IB, OUTPUT);
  pinMode(motorB_IA, OUTPUT);
  pinMode(motorB_IB, OUTPUT);

  iniciarMotores();

  tiempoInicio = millis();

  Serial.println("Iniciando conteo por 15 segundos...");
  bleSerial.println("Iniciando conteo por 15 segundos...");
}

void loop() {
  if (enEjecucion) {
    unsigned long tiempoActual = millis();

    // Leer sensor IR
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

    // Verificar si terminó el tiempo
    if (tiempoActual - tiempoInicio >= duracion) {
      enEjecucion = false;
      detenerMotores();

      float eficiencia = (conteo / (float)cantidadEsperada) * 100.0;

      Serial.println("\n--- RESULTADOS ---");
      Serial.print("Productos esperados: ");
      Serial.println(cantidadEsperada);
      Serial.print("Productos detectados: ");
      Serial.println(conteo);
      Serial.print("Eficiencia: ");
      Serial.print(eficiencia);
      Serial.println("%");

      bleSerial.println("\n--- RESULTADOS ---");
      bleSerial.print("Productos esperados: ");
      bleSerial.println(cantidadEsperada);
      bleSerial.print("Productos detectados: ");
      bleSerial.println(conteo);
      bleSerial.print("Eficiencia: ");
      bleSerial.print(eficiencia);
      bleSerial.println("%");

      bleSerial.println("Envía 'r' para reiniciar.");
    }

    delay(200); // Para evitar múltiples detecciones
  }

  // Comando de reinicio desde Bluetooth
  if (bleSerial.available()) {
    char comando = bleSerial.read();
    if (!enEjecucion && comando == 'r') {
      reiniciarProceso();
    }
  }
}
