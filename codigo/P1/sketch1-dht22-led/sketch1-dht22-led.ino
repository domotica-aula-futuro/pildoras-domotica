#include <DHT.h>

#define PIN_DHT 2
#define PIN_LED 8
#define UMBRAL_TEMP 26.0          // °C, valor de ejemplo para la práctica

DHT dht(PIN_DHT, DHT22);
unsigned long ultimaLectura = 0;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_LED, OUTPUT);
  dht.begin();
  Serial.println("Nodo de clima arrancado");
}

void loop() {
  if (millis() - ultimaLectura >= 2000) {      // una lectura cada 2 s
    ultimaLectura = millis();
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    if (isnan(t) || isnan(h)) {
      Serial.println("Error leyendo el DHT22");
      return;
    }
    Serial.print("Temperatura: "); Serial.print(t, 1); Serial.print(" C  ");
    Serial.print("Humedad: ");     Serial.print(h, 1); Serial.println(" %");
    digitalWrite(PIN_LED, t > UMBRAL_TEMP ? HIGH : LOW);
  }
}
