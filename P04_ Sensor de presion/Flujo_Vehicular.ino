#include <Wire.h>
#include <Adafruit_MPL3115A2.h>

Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();

  int a = 0;
  int b = 0;
  int count = 0;


//Configuracion de sensor LM35
// Declaracion de variables globales
float tempC; // Variable para almacenar el valor obtenido del sensor (0 a 1023)
int pinLM35 = 0; // Variable del pin de entrada del sensor (A0)

//Fin de condiguracion de sensor LM35

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
  //Presion medida en pascales
  Serial.print(P); Serial.println(" Pascales");
  //Altura medida en metros
  float altm = baro.getAltitude();
  Serial.print(altm); Serial.println(" Meters");
  //Temperatura en grados celcius
  float tempC = baro.getTemperature();
  Serial.print(tempC); Serial.println(" °C");

  //Calculo de densidad en kg/m^3
  float tempk = tempC + 273.15; //Conversion a Kelvins
  float tv= 1.01*tempk;
  float dens = P/(tv*287);
  Serial.print(dens); Serial.println(" kg/m^3");

  //Maquina de estados para sistema de flujo vehicular
  if(a == 0 && b == 0){
    if( P  < 76700){

    }else{ //Aumenta la presion, pasa un auto
      a = 0;
      b = 1;
    }
  }
  else if(a == 0 && b == 1){
    if( P  < 76700){
      a = 1;
      b = 0;
    }
  }
  else if(a == 1 && b == 0){
    if( P  < 76700){
      a = 1;
      b = 0;
    }
    else{
      a = 1;
      b = 1;
      
    }
  }
  else if(a == 1 && b == 1){
    if( P  < 76700){
      a = 0;
      b = 0;
      count = count + 1;
    }
    else{
      a = 1;
      b = 1;
    }
  }
  //Fin de maquina de estados

  //Imprimir flujo veicular
  //Serial.print(count); Serial.println(" Autos");
  
  //Configuracion de sensor LM35
  // Con analogRead leemos el sensor
  tempC = analogRead(pinLM35); 
   
  // Calculamos la temperatura con la fórmula
  tempC = (5.0 * tempC * 100.0)/1024.0 ; 
 
  // Envia el dato al puerto serial
  //Serial.print("LM35: ");
  //Serial.println(tempC);
  // Salto de línea
  //Serial.print("\n");
  
  
  delay(10000);
}