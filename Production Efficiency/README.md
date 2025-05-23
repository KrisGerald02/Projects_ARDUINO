# 🏭 Production Efficiency Monitor

Este proyecto es un sistema de monitoreo de eficiencia para líneas de producción, utilizando un microcontrolador Arduino. Mide la cantidad de productos detectados en una cinta transportadora durante un período determinado (60 segundos) y calcula la eficiencia del proceso. También registra la velocidad del motor mediante un encoder y se comunica por Bluetooth.

Además, he creado una aplicación llamada **EfiDuino**, desarrollada en Swift, que se conecta al módulo Bluetooth del sistema para mostrar las estadísticas en tiempo real, incluyendo gráficos, y permite exportar los resultados a formatos como PDF, PNG y Excel.

## ⚙️ Características

- 🚥 **Detección de productos** mediante un sensor infrarrojo (IR)
- ⏱️ **Conteo de producción durante 60 segundos**
- ⚡ **Cálculo de eficiencia** en base a una meta de 20 productos por minuto
- 🔄 **Lectura de velocidad del motor** usando un encoder
- 📶 **Comunicación Bluetooth** con un módulo HC06 para enviar/recibir datos
- 📱 **App móvil EfiDuino** desarrollada en Swift para mostrar estadísticas en tiempo real
- 🧠 **Simulación posible en Tinkercad**

---

## 🧰 Componentes utilizados

- Arduino R4 MINIMA
- Sensor infrarrojo (IR)
- Motor DC con encoder
- Módulo Bluetooth HC06 (SoftwareSerial)
- Jumpers y resistencias
- Fuente de alimentación externa 

---

## 🔌 Conexiones

| Componente           | Pin Arduino     |
|----------------------|-----------------|
| Sensor IR            | A0              |
| Encoder (señal)      | D2 (interrupción) |
| Motor A              | D9              |
| Motor B              | D10             |
| JDY-31 TX            | D4 (Rx Arduino) |
| JDY-31 RX            | D3 (Tx Arduino) |

---

## 🔍 Funcionamiento

1. **Inicio**: El sistema arranca y activa el motor.
2. **Conteo**: Durante 60 segundos, detecta los productos que pasan a menos de 30 cm del sensor IR.
3. **Encoder**: Cuenta los pulsos del encoder para monitorear la velocidad del motor.
4. **Comunicación**: Muestra los datos por el puerto Serial y los transmite también por Bluetooth.
5. **Eficiencia**: Al finalizar el minuto, muestra la cantidad de productos y calcula la eficiencia. 


---

## 📡 Comunicación Bluetooth

Puedes conectar la app **EfiDuino** (desarrollada en Swift) con tu dispositivo móvil ios para ver las estadísticas en tiempo real, visualizar gráficos de productividad y exportar los resultados en formato PDF, PNG o Excel.

---

## 📱 EfiDuino: App Móvil IOS

**EfiDuino** es una aplicación desarrollada en Swift que se conecta al sistema de monitoreo de eficiencia a través del módulo Bluetooth HC06. La app permite:

- Visualizar las estadísticas de producción por minuto. (El tiempo puede ser modificado).
- Ver gráficos en tiempo real sobre la eficiencia del proceso.
- Exportar los resultados en los siguientes formatos:
  - PDF
  - PNG
  - Excel
 
---

## Circuito


---

---

## 💻 Simulación

Este proyecto puede ser simulado en [Tinkercad](https://www.tinkercad.com) usando sensores simulados y el Serial Monitor en lugar de Bluetooth.

---

## 🤖 Autor

Desarrollado por Kristel Geraldine Villalta Porras.

## 📝 Codigo
```cpp
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
