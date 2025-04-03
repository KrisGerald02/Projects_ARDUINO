# 💡 Arduino Project: Turn on the LED on Pin 13  

## 📌 Project Overview 
This project demonstrates how to turn on the built-in LED on pin 13 of an Arduino. It is a basic project for beginners to understand the use of digital outputs on an Arduino board.  

## 🛠️ Components Required
- Arduino R4 Minima board  
- USB cable for programming and power  

## 📷 Demonstration  
https://github.com/user-attachments/assets/a1fcfd14-8372-411e-926a-1884595f3528

## 📝 Code  
```cpp
void setup() {
  //Declaracion de Variables
  //Aqui se trabaja que pin es de entrada/salida
  pinMode(13, OUTPUT); //Salida
  Serial.begin(9600); //Tiempo por cada proceso
}

void loop() {
  // Formamos Bucles
  Serial.write("Luz Encendida\n");
  digitalWrite(13, HIGH); //High = Voltaje 5
  delay(2000); //Se mantiene encendido 2000 milisegundos = 2 segundos
  Serial.write("Luz Apagada\n");
  digitalWrite(13, LOW); //Low= Apagar
  delay(2000); //1000 milisegundos = 1 segundos
}
