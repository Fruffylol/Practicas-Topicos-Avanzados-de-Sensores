#include <SoftwareSerial.h>

SoftwareSerial gps(4, 3);

void setup() {
  Serial.begin(115200);
  gps.begin(9600);
  Serial.print("Hora UTC,Latitud,Longitud,Número de Satélites");
  Serial.print("\n");
}

void loop() {
  if (gps.available()) {
    // Lee la sentencia NMEA completa
    String sentence = gps.readStringUntil('\n');

    // Verifica si la sentencia comienza con "$GPGGA"
    if (sentence.startsWith("$GPGGA")) {
      // Separa la sentencia en partes utilizando la coma como delimitador
      String parts[15];
      int i = 0;
      char *token = strtok(const_cast<char*>(sentence.c_str()), ",");
      while (token != NULL) {
        parts[i++] = token;
        token = strtok(NULL, ",");
      }

      // Extrae la hora, latitud, indicación de latitud, longitud, indicación de longitud y número de satélites
      String timeUTC = parts[1];
      String latDegreesMinutes = parts[2];
      String latIndicator = parts[3];
      String lonDegreesMinutes = parts[4];
      String lonIndicator = parts[5];
      String numSatellites = parts[7];

      // Convierte la hora a formato decimal (hh:mm:ss)
      String hourStr = timeUTC.substring(0, 2);
      String minuteStr = timeUTC.substring(2, 4);
      String secondStr = timeUTC.substring(4, 6);
      String timeDecimal = hourStr + ":" + minuteStr + ":" + secondStr;

      // Convierte latitud y longitud a decimal
      float latitude = convertToDecimal(latDegreesMinutes, latIndicator);
      float longitude = convertToDecimal(lonDegreesMinutes, lonIndicator);

      // Imprime los datos en forma de tabla
      delay(60000);
      Serial.print(timeDecimal);
      Serial.print(",");
      Serial.print(latitude, 6);  // Imprime con 6 decimales
      Serial.print(",");
      Serial.print(longitude, 6);
      Serial.print(",");
      Serial.print(numSatellites.toInt());
      Serial.print("\n");
    }
  }
}

// Función para convertir grados y minutos a decimal
float convertToDecimal(String degreesMinutes, String indicator) {
  // Divide la cadena en grados y minutos
  int dotIndex = degreesMinutes.indexOf('.');
  int degrees = degreesMinutes.substring(0, dotIndex - 2).toInt();
  float minutes = degreesMinutes.substring(dotIndex - 2).toFloat();

  // Calcula la coordenada decimal
  float decimal = degrees + (minutes / 60.0);

  // Ajusta el signo según la indicación (N/S para latitud, E/W para longitud)
  if (indicator == "S" || indicator == "W") {
    decimal = -decimal;
  }

  return decimal;
}




