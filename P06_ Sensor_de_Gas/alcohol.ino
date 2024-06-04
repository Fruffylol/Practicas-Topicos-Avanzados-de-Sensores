const int sensorPin = A0; // Pin analógico al que está conectado el sensor MQ-3
const int enablePin = 7; // Pin digital para habilitar el sensor (si aplica)

void setup() {
  Serial.begin(9600); // Inicializar la comunicación serial
  pinMode(enablePin, OUTPUT); // Configurar el pin de habilitación como salida
  digitalWrite(enablePin, HIGH); // Habilitar el sensor (si aplica)
}

void loop() {
  int sensorValue = analogRead(sensorPin); // Leer el valor del sensor
  float voltage = sensorValue * (5.0 / 1023.0); // Convertir el valor a voltaje
  float alcoholPPM = calculateAlcoholPPM(voltage); // Calcular la concentración de alcohol en ppm
  float bloodAlcoholPercentage = alcoholPPM / 250; // Calcular el porcentaje de alcohol en la sangre

  // Imprimir los valores en el monitor serial
  Serial.print("Concentracion de Alcohol: ");
  Serial.print(alcoholPPM);
  Serial.println(" ppm");

  Serial.print("Porcentaje de alcohol en la sangre: ");
  Serial.print(bloodAlcoholPercentage);
  Serial.println(" %");

  delay(1000); // Esperar un segundo antes de la siguiente lectura
}

// Función para calcular la concentración de alcohol en ppm
float calculateAlcoholPPM(float voltage) {
  // Asegúrate de ajustar estos cálculos según las especificaciones del sensor y las curvas de calibración
  // Ejemplo: ppm = (voltage - offset) / sensitivity;
  float ppm = (voltage - 0.1) * 2000; // Ajustar según la curva de calibración específica del MQ-3
  return ppm;
}
