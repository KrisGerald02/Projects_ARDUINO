#define sensorIR A0
int conteo = 0;
bool objetoDetectado = false;

// Tiempo de ejecución
unsigned long tiempoInicio;
const unsigned long duracion = 30000;
bool enEjecucion = true;

void setup() {
  Serial.begin(9600);
  tiempoInicio = millis();
  Serial.println("Iniciando conteo por 1 minuto...");
}

void loop() {
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

    //Serial.print("Distancia: ");
   // Serial.print(distancia);
    ///Serial.println(" cm");

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

    delay(200);
  }
}
