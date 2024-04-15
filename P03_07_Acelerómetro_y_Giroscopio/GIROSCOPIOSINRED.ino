#include <Wire.h>
#include <MPU6050.h>
MPU6050 mpu;
int pitch=0;
int roll=0;
void setup() {
  Serial.begin(9600);
  Wire.begin();
 
  // Inicializar el sensor MPU6050
  mpu.initialize();
 
  // Configurar el rango de escala del giroscopio y acelerómetro
  mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_250);
  mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);
}
void loop() {
  // Leer los datos del sensor
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
 
  // Convertir los datos en unidades de medida
  float accelX = ax / 16384.0; // Sensibilidad del acelerómetro para el rango de ±2g
  float accelY = ay / 16384.0;
  float accelZ = az / 16384.0;
 
  float gyroX = gx / 131.0; // Sensibilidad del giroscopio para el rango de ±250°/s
  float gyroY = gy / 131.0;
  float gyroZ = gz / 131.0;
 
  /*----- Angulos pich and roll a partir de un acelerometro*/
  pitch = -(atan2(accelX, sqrt(accelY*accelY + accelZ*accelZ))*180.0)/M_PI;
  roll = ((atan2(accelY, accelZ)*180.0)/M_PI);
  /* Pasamos los grados a valores de 0 a 1023 con la finalidad de no tener negativos*/
  roll=map(roll,-180,180,0,1023);
  pitch=map(pitch,-180,180,0,1023);
  /*---- agregamos ceros para que las cadenas tengan la misma longitud -----*/
  // Primero tomamos valores en cada intervalo y los declaramos en el siguiente codigo.
  if(((pitch>320)&&(pitch<365))&&((roll>278)&&(roll<320))){
    Serial.println("Izquierda");
  }else if(((pitch>335)&&(pitch<386))&&((roll>713)&&(roll<744))){
    Serial.println("Derecha");
  }else if(((pitch>265)&&(pitch<290))&&((roll>490)&&(roll<534))){
    Serial.println("Estatico");
  }else if(((pitch>430)&&(pitch<460))&&((roll>510)&&(roll<520))){
    Serial.println("atras");
  }
 
  delay(1000); // Esperar un poco antes de la próxima lectura
}

