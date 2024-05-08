#define TRIG  19
#define ECHO  18

int tiempo, distancia;
void setup() {
  Serial.begin(115200);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  digitalWrite(TRIG, LOW);
}

void loop() {
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  tiempo = pulseIn(ECHO, HIGH);
  
  distancia = tiempo / 58.2; //ajustar el 58.2 para que sea mas exacta la distancia
  //Serial.println(distancia);
  Serial.println("d = " + 
  String(distancia) + ", t = " + 
  String(tiempo) );
  delay(1000);
}
