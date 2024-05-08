#define BOTON 2
int valor = 0;
void setup() {
  Serial.begin(115200);
  pinMode(BOTON, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  valor = digitalRead(BOTON);
  Serial.println(valor);
  delay(500);

}
