#define BOTON 4
int valor = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(BOTON, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  valor = digitalRead(BOTON);
  Serial.println(valor);
  delay(500);
}
