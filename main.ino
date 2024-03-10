#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() {
  Serial.begin(115200);


  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  
  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // power 
  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
}


void loop() {
  VL53L0X_RangingMeasurementData_t measure;
  float alpha = .988;
  float Anm = 0;
  float An = 0;
  float M = 0;
    
  Serial.print("Reading a measurement...,");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data 

    //Filtro EMA
    //Guradamos el valor que nos arroja el sensor
    M = measure.RangeMilliMeter;
    //Aplicamos el filtro EMA
    An = (alpha * M) + ((1 - alpha)*Anm);
    //Se imprime el valor de el filtro
    Serial.print(""); Serial.print(An);
    //Salto de linea para que lo identifique exel
    Serial.print("\n");
    Anm = An;

  } else {
    Serial.println("8092.71");
  }
    
  delay(1000);
}