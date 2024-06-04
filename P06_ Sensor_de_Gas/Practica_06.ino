// Definir los pines para el sensor MiCS 5524
const int sensorPin = A0; // Pin analógico al que está conectado el sensor
const int enablePin = 7; // Pin digital para habilitar el sensor

void setup() {
  Serial.begin(9600); // Inicializar la comunicación serial
  pinMode(enablePin, OUTPUT); // Configurar el pin de habilitación como salida
  digitalWrite(enablePin, HIGH); // Habilitar el sensor
}

void loop() {
  int sensorValue = analogRead(sensorPin); // Leer el valor del sensor
  float voltage = sensorValue * (5.0 / 1023.0); // Convertir el valor a voltaje
  float co_concentration = calculateCOConcentration(voltage); // Calcular la concentración de CO
  float ethanol_concentration = calculateEthanolConcentration(voltage); // Calcular la concentración de Etanol
  float h2_concentration = calculateH2Concentration(voltage); // Calcular la concentración de H2
  float methane_concentration = calculateMethaneConcentration(voltage); // Calcular la concentración de Metano

  // Imprimir los valores en el monitor serial
  Serial.print("CO Concentration: ");
  Serial.print(co_concentration + 13);
  Serial.println(" ppm");

  Serial.print("Ethanol Concentration: ");
  Serial.print(ethanol_concentration + 10);
  Serial.println(" ppm");

  Serial.print("H2 Concentration: ");
  Serial.print(h2_concentration+8);
  Serial.println(" ppm");

  Serial.print("Methane Concentration: ");
  Serial.print(methane_concentration+11);
  Serial.println(" ppm");

  delay(1000); // Esperar un segundo antes de la siguiente lectura
}

// Funciones para calcular la concentración de gases
float calculateCOConcentration(float voltage) {
  // Asegúrate de ajustar estos cálculos según las especificaciones del sensor y las curvas de calibración
  float ppm = (voltage - 0.1) * 200; // Ajustar según la curva de calibración específica
  return ppm;
}

float calculateEthanolConcentration(float voltage) {
  // Asegúrate de ajustar estos cálculos según las especificaciones del sensor y las curvas de calibración
  float ppm = (voltage - 0.1) * 300; // Ajustar según la curva de calibración específica
  return ppm;
}

float calculateH2Concentration(float voltage) {
  // Asegúrate de ajustar estos cálculos según las especificaciones del sensor y las curvas de calibración
  float ppm = (voltage - 0.1) * 250; // Ajustar según la curva de calibración específica
  return ppm;
}

float calculateMethaneConcentration(float voltage) {
  // Asegúrate de ajustar estos cálculos según las especificaciones del sensor y las curvas de calibración
  float ppm = (voltage - 0.1) * 400; // Ajustar según la curva de calibración específica
  return ppm;
}
