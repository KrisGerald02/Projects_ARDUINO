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
