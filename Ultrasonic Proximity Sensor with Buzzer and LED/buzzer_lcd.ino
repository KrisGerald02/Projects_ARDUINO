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
