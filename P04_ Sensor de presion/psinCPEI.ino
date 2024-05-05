#include <Wire.h>
#include <Adafruit_MPL3115A2.h>

Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();

void setup() {
  Serial.begin(9600);
  Serial.println("Adafruit_MPL3115A2 test!");
}

void loop() {
  if (! baro.begin()) {
    Serial.println("Couldnt find sensor");
    return;
  }
  
  float P = baro.getPressure()*100;
  Serial.print(P); Serial.println(" Pascales");

  //float altm = baro.getAltitude();
  //Serial.print(altm); Serial.println(" meters");
  
  float tempC = baro.getTemperature();
  Serial.print(tempC); Serial.println("°C");
  float tempk = tempC + 273.15;
  float tv= 1.01*tempk;
  float dens = P/(tv*287);
  Serial.print(dens); Serial.println(" kg/m^3");
  float E= 0.5*(dens)pow(4.2,3)(3.1416*pow(1,2));
  Serial.print(E);
  delay(10000);
}