# 🔉 Infrared Distance Sensor

## 📌 Project Overview  
The GP2Y0A41SK0F sensor is commonly used in electronics and robotics projects to measure short distances easily and without physical contact. Using infrared triangulation technology, it is ideal for detecting nearby objects, avoiding obstacles, or counting items in motion—all without direct contact.


## 🛠️ Components Required  
- Arduino R3
- Jumpers
- TT Motor/Encoder Disk
- Interface Distance Sensor (gp2y0a41sk0f)

## Circuit with Tintercad
![Image](https://github.com/user-attachments/assets/3cfbb8ac-02f3-44d8-89b7-b5aab342cef9)

## 📝 Code  
```cpp
#define sensor A0 // Sharp IR GP2Y0A41SK0F (4-30cm, analog)

void setup() {
  Serial.begin(9600); // start the serial port
}

void loop() {
  
  // 5v
  float volts = analogRead(sensor)*0.0048828125;  // value from sensor * (5/1024)
  int distance = 13*pow(volts, -1); // worked out from datasheet graph
  delay(1000); // slow down serial port 
  
  if (distance <= 30){
    Serial.println(distance);   // print the distance
  }
}
