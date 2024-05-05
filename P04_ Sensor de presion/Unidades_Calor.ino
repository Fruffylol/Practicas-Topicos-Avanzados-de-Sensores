#include <Wire.h>
#include <Adafruit_MPL3115A2.h>

Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();

  int a = 0;
  int b = 0;
  int count = 0;

  float tempMenor = 10000;
  float tempMayor = -10000;
  float UC=0;

void setup() {
  Serial.begin(9600);
  Serial.println("Adafruit_MPL3115A2 test!");
}

void loop() {
  Serial.println("///////Realizando medicion//////");
  if (! baro.begin()) {
    Serial.println("Couldnt find sensor");
    return;
  }
  
  //Temperatura en grados celcius
  
  float tempC = baro.getTemperature();
  Serial.print("Temperatura actual: ");
  Serial.print(tempC); Serial.println(" °C");

  
  //Maquina de estados para sistema de flujo vehicular
  if(tempC < tempMenor){
    tempMenor = tempC;
  }
  else if(tempC > tempMayor){
    tempMayor = tempC;
  }
  
  Serial.print("Temperatura menor: "); Serial.print(tempMenor); 
  Serial.println(" °C");
  Serial.print("Temperatura mayor: "); Serial.print(tempMayor); 
  Serial.println(" °C");
  UC = (tempMayor + tempMenor)/2 - 10;
  Serial.print("UC: "); Serial.print(UC); 
  Serial.println("");
  
  if(UC < 64.41){
    Serial.println("Emergencia");
  }
  else if(UC > 91.33){
    Serial.println("Formacion de guias");
  }
  else if(UC > 99.31){
    Serial.println("Floracion");
  }
  else if(UC > 112.77){
    Serial.println("Formacion de vainas");
  }
  else if(UC > 153.24){
    Serial.println("Llenado de vainas");
  }
  else{
    Serial.println("Maduracion");
  }
  delay(1000);
}