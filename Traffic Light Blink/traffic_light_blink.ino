// Semáforo Parpadeante
// Definir pines del módulo semáforo
#define LED_ROJO 13
#define LED_AMARILLO 12
#define LED_VERDE 11

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

    // Volver a ROJO
}
