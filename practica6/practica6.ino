#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

#include <ESP32Servo.h>

#define TRIG  19
#define ECHO  18
#define S1 23
#define LED 2

double tiempo, distancia;
Servo servo;
WiFiMulti wm; 
String jwt;  
bool sesion = false;

void setup() {
  Serial.begin(115200);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(TRIG, LOW);
  servo.attach(S1);
  servo.write(0);
  digitalWrite(LED, LOW);
  sesion = false;
  //conexion wifi
  Serial.println("MAC:" + WiFi.macAddress());
  wm.addAP("IOT","A3o6HhLw");
}

void loop() {
  if((wm.run() == WL_CONNECTED)) {
    digitalWrite(LED, HIGH);
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    if(!sesion)login();
    else{
      //enviar datos de sensores al servidor
      ultrasonico();
      registrar ();
      actualiza(21);
    }
    }else{
      digitalWrite(LED, LOW);
    }
  delay(1000);
}

void ultrasonico(){
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  tiempo = pulseIn(ECHO, HIGH);
  distancia = tiempo / 58.2; //ajustar el 58.2 para que sea mas exacta la distancia
  Serial.println(distancia);
}

void login (){
   HTTPClient http;
    http.begin("https://iotrest.itsch.kyared.com/");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    int httpCode = http.POST("username=admin&password=123");
    if(httpCode == HTTP_CODE_OK){ //200OK
      jwt = http.getString();
      Serial.println(jwt);
      sesion = true;
    }else{
      Serial.println("Error de Conexion.Codigo:" + httpCode);
    }
    http.end();
}

void registrar (){
   HTTPClient http;
    http.begin("https://iotrest.itsch.kyared.com/sensors");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    http.addHeader("Authorization-Type", "Bearer " + jwt);

    int httpCode = http.POST("name=isa&type=ultrasonic&value=" + String(distancia));
    if(httpCode == HTTP_CODE_OK){ //200OK
      String result = http.getString();
      Serial.println(result);
    }else{
      Serial.println("Error de Conexion. Codigo:" + httpCode);
    }
    http.end();
}

void actualiza(int id){
   HTTPClient http;
    http.begin("https://iotrest.itsch.kyared.com/sensors/" + String(id));
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    http.addHeader("Authorization-Type", "Bearer" + jwt);

    int httpCode = http.PUT("name=isa&type=ultrasonic&value=" + String(distancia));
    if(httpCode == HTTP_CODE_OK){ //200OK
      String result = http.getString();
      Serial.println(result);
    }else{
      Serial.println("Error de Conexion. Codigo:" + httpCode);
    }
    http.end();
}


