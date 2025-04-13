/ Pines motores
const int motorA_IA = 9;
const int motorA_IB = 10;
const int motorB_IA = 5;
const int motorB_IB = 6;

// Pines encoder
const int encoder1Pin = 2;  // Interrupt 0
const int encoder2Pin = 3;  // Interrupt 1

volatile int pulsos1 = 0;
volatile int pulsos2 = 0;

void contarPulsos1() {
  pulsos1++;
}

void contarPulsos2() {
  pulsos2++;
}

void setup() {
  Serial.begin(9600);

  // Configurar pines del L9110S
  pinMode(motorA_IA, OUTPUT);
  pinMode(motorA_IB, OUTPUT);
  pinMode(motorB_IA, OUTPUT);
  pinMode(motorB_IB, OUTPUT);

  // Configurar pines encoder
  pinMode(encoder1Pin, INPUT_PULLUP);
  pinMode(encoder2Pin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(encoder1Pin), contarPulsos1, RISING);
  attachInterrupt(digitalPinToInterrupt(encoder2Pin), contarPulsos2, RISING);

  // Iniciar motores hacia adelante
  digitalWrite(motorA_IA, HIGH);
  digitalWrite(motorA_IB, LOW);

  digitalWrite(motorB_IA, HIGH);
  digitalWrite(motorB_IB, LOW);
}

void loop() {
  Serial.print("Pulsos Motor A: ");
  Serial.print(pulsos1);
  Serial.print(" | Pulsos Motor B: ");
  Serial.println(pulsos2);

  delay(1000); // Imprime cada segundo
}
