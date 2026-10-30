#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

const char* SSID = "RED_IOT_AULA";       // pon aquí la red de tu aula
const char* PASS = "********";           // no subas la contraseña real a GitHub

DHT dht(4, DHT22);                       // DHT22 en GPIO4, alimentado a 3,3 V
WebServer server(80);

void paginaInicio() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  String html = "<h1>Nodo clima</h1>";
  html += "<p>Temperatura: " + String(t, 1) + " &deg;C</p>";
  html += "<p>Humedad: " + String(h, 1) + " %</p>";
  server.send(200, "text/html; charset=utf-8", html);
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASS);
  Serial.print("Conectando");
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
  Serial.print("\nConectado. IP: ");
  Serial.println(WiFi.localIP());
  server.on("/", paginaInicio);
  server.begin();
}

void loop() {
  server.handleClient();
}
