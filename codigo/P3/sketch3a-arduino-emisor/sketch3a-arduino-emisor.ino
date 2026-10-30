#include <DHT.h>
#include <SoftwareSerial.h>

DHT dht(2, DHT22);
SoftwareSerial enlace(10, 11);           // RX = 10, TX = 11 hacia el ESP32
unsigned long ultima = 0;

void setup() {
  Serial.begin(9600);                     // USB para depurar
  enlace.begin(9600);                     // enlace con el ESP32
  dht.begin();
}

void loop() {
  if (millis() - ultima >= 5000) {
    ultima = millis();
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    int luz = map(analogRead(A0), 0, 1023, 0, 100);
    if (isnan(t) || isnan(h)) return;
    String msg = "T:" + String(t, 1) + ";H:" + String(h, 1) + ";L:" + String(luz);
    enlace.println(msg);
    Serial.println("Enviado -> " + msg);
  }
}
