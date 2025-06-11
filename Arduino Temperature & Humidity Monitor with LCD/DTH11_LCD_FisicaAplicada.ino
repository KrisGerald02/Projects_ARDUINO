// Libreria DHT Sensor Library by Adafruit
// Libreria LiquidCrystal I2C by Frank de Brabander
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <math.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Función para convertir resistencia NTC (Ohm) a temperatura (°C)
double ntcResistanceToTemp(double R) {
  const double A = 1.009249522e-03;
  const double B = 2.378405444e-04;
  const double C = 2.019202697e-07;

  double logR = log(R);
  double tempK = 1.0 / (A + B * logR + C * pow(logR, 3)); // Temperatura en Kelvin
  double tempC = tempK - 273.15;                           // A °C
  return round(tempC * 2.0) / 2.0;                         // Redondear a pasos de 0.5
}

void setup() {
  Serial.begin(9600);
  dht.begin();  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Iniciando...");
  delay(2000);
  lcd.clear();
}

void loop() {
  delay(1000);
  
  // Leemos la humedad y temperatura del DHT11
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Error!...");
    return;
  }

  // Simulación de resistencia NTC para prueba
  double resistenciaNTC = 3000.0; // <-- Se mod por una lectura analógica real
  double temperaturaNTC = ntcResistanceToTemp(resistenciaNTC);

  // Imprimir en Serial Monitor
  Serial.print("DHT Temp: ");
  Serial.print(t);
  Serial.print("°C | Hum: ");
  Serial.print(h);
  Serial.print("% | NTC Temp: ");
  Serial.print(temperaturaNTC);
  Serial.println("°C");

  // Mostrar en pantalla
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DHT: ");
  lcd.print(t);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("NTC: ");
  lcd.print(temperaturaNTC);
  lcd.print("C");
}
