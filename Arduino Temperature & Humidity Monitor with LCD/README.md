# 🌡️ Arduino Temperature & Humidity Monitor with LCD  

## 📌 Project Overview  
This project uses an **Arduino**, a **DHT11 sensor**, and an **LCD display** to monitor temperature and humidity in real-time. The data is displayed on the LCD screen, making it an easy-to-use system for weather monitoring or indoor climate control.  

## 🛠️ Components Required  
- Arduino Uno (or compatible board)  
- DHT11 Temperature & Humidity Sensor  
- 16x2 LCD Display with I2C module  
- Jumper Wires  
- Breadboard  

## 🔗 Circuit Diagram  
(Insert circuit diagram here if available)  

## 📝 Code  
```cpp
//Libreria DTH Sensor Library by Adafruit
//Libreria LiquidCrystakl IC2 by Frank de Bradander
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


void setup() {
  // Declaracion de variables
  //pinMode(13, OUTPUT);
  //Serial.begin(9600);
  //Serial.println("Hola desde arduino");

  Serial.begin(9600);
  dht.begin();  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Iniciando...");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Bucle 
  //digitalWrite(13, HIGH);
  //Serial.println("Led on ");
  //delay(2000);
  //digitalWrite(13, LOW);
  //Serial.println("Led off ");
  //delay(1000);

  delay(1000);
// Leemos la humedad relativa
  float h = dht.readHumidity();
// Leemos la temperatura en grados centígrados (por defecto)
  float t = dht.readTemperature();
// Comprobamos si ha habido algún error en la lectura
  if(isnan(h)|| isnan(t)){
    Serial.println("Error obteniendo los datos del sensor DHT11");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Error!...");
    return;
  }

  // Imprimimos los valores en el Monitor Serie
  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.print("%  |  Temperatura: ");
  Serial.print(t);
  Serial.println("°C");  

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Humedad: ");
  lcd.print(h);
  lcd.print("%");
}

## ⚡ How to Use  
1. Connect the **DHT11 sensor** and **LCD display** to the Arduino as per the circuit diagram.  
2. Install the necessary libraries:  
   - `DHT sensor library` by Adafruit  
   - `LiquidCrystal I2C` library  
3. Upload the provided code to your Arduino.  
4. The LCD will display real-time temperature and humidity readings.  

## 📢 Notes  
- Ensure the **correct I2C address** for your LCD (default is `0x27`, but some modules use `0x3F`).  
- The DHT11 sensor has a slight delay; readings update every **2 seconds**.  

## 📸 Demo  
(Add a photo of your working project here)  

---

Let me know if you need any modifications! 🚀
