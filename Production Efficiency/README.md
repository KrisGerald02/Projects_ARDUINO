# 🏭 Production Efficiency Monitor

Este proyecto es un sistema de monitoreo de eficiencia para líneas de producción, utilizando un microcontrolador Arduino. Mide la cantidad de productos detectados en una cinta transportadora durante un período determinado (15 segundos) y calcula la eficiencia del proceso y la envia a la aplicacion web comunicandose por Bluetooth.

Además, he creado una aplicación llamada **EfiDuino**, que se conecta al módulo Bluetooth del sistema para mostrar las estadísticas en tiempo real, incluyendo gráficos, y permite exportar los resultados a formatos como PDF, PNG y Excel.

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

- Arduino UNO
- Sensor infrarrojo (IR)
- Motor DC con encoder
- Módulo Bluetooth HC06 (SoftwareSerial)
- Jumpers
- Bateria de 9V
- Modulo de Bateria
- Conector de Bateria 

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

- Sensor Infrarojo: Amarillo(GND),Negro(-),Rojo(+)
- Bluetooth: Naranja(State),Negro(RXD),Blanco(TXD),Azul(GND),Amarillo(VCC),Rojo(EV)
- LN9110s: B1-A(Azul),B1-B(Morado),GND(Verde),VCC(Gris),A1-A(Naranja),A1-B(Blanco)

---

## 🔍 Funcionamiento

1. **Inicio**: El sistema arranca y activa el motor.
2. **Conteo**: Durante 60 segundos, detecta los productos que pasan a menos de 30 cm del sensor IR.
3. **Encoder**: Cuenta los pulsos del encoder para monitorear la velocidad del motor.
4. **Comunicación**: Muestra los datos por el puerto Serial y los transmite también por Bluetooth.
5. **Eficiencia**: Al finalizar el minuto, muestra la cantidad de productos y calcula la eficiencia. 


---

## 📡 Comunicación Bluetooth

Puedes conectar la app **EfiDuino** con tu dispositivo móvil ios para ver las estadísticas en tiempo real, visualizar gráficos de productividad y exportar los resultados en formato PDF, PNG o Excel.

---

## 📱 EfiDuino: App Web

**EfiDuino** es una aplicación web que se conecta al sistema de monitoreo de eficiencia a través del módulo Bluetooth HC06. La app permite:

- Visualizar las estadísticas de producción por minuto. (El tiempo puede ser modificado).
- Ver gráficos en tiempo real sobre la eficiencia del proceso.
- Exportar los resultados en los siguientes formatos:
  - PDF
  - PNG
  - Excel
  - Word
 
---

## 💻 Simulación del Circuito con Fritzing
![Image](https://github.com/user-attachments/assets/4e3b24ed-ff4f-41df-be74-d8c944cbb4df)

---

## 🤖 Autor

Desarrollado por Kristel Geraldine Villalta Porras.

## 📝 Codigo
```cpp
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
