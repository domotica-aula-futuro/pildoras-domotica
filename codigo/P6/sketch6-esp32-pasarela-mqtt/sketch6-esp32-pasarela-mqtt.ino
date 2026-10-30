#include <WiFi.h>
#include <PubSubClient.h>

const char* SSID = "RED_IOT_AULA";         const char* PASS = "********";
const char* BROKER = "192.168.50.10";      // IP del servidor de Home Assistant
const char* MQ_USER = "mqtt_nodos";        const char* MQ_PASS = "********";

const char* NODO    = "vasco_clima_nodo2";
const char* T_DISP  = "aula/vasco/clima/nodo2/disponible";
const char* T_TEMP  = "aula/vasco/clima/nodo2/temperatura";
const char* T_HUM   = "aula/vasco/clima/nodo2/humedad";
const char* T_VENT  = "aula/vasco/clima/nodo2/ventilador";
const char* T_VSET  = "aula/vasco/clima/nodo2/ventilador/set";

WiFiClient wifi;
PubSubClient mqtt(wifi);
float temperatura = NAN, humedad = NAN;
int luz = -1;

const char* DISP_JSON = "\"device\":{\"identifiers\":[\"vasco_clima_nodo2\"],"
                        "\"name\":\"Clima nodo 2\",\"model\":\"Arduino UNO + ESP32\"}";

void anunciarSensor(const char* id, const char* nombre, const char* topic,
                    const char* unidad, const char* clase) {
  char cfg[96], json[480];
  snprintf(cfg, sizeof(cfg), "homeassistant/sensor/%s/config", id);
  snprintf(json, sizeof(json),
    "{\"name\":\"%s\",\"unique_id\":\"%s\",\"state_topic\":\"%s\","
    "\"unit_of_measurement\":\"%s\",\"device_class\":\"%s\","
    "\"availability_topic\":\"%s\",%s}", nombre, id, topic, unidad, clase, T_DISP, DISP_JSON);
  mqtt.publish(cfg, json, true);
}

void anunciarInterruptor() {
  char json[480];
  snprintf(json, sizeof(json),
    "{\"name\":\"Ventilador\",\"unique_id\":\"vasco_clima_nodo2_vent\","
    "\"command_topic\":\"%s\",\"state_topic\":\"%s\","
    "\"availability_topic\":\"%s\",%s}", T_VSET, T_VENT, T_DISP, DISP_JSON);
  mqtt.publish("homeassistant/switch/vasco_clima_nodo2_vent/config", json, true);
}

void alRecibir(char* topic, byte* datos, unsigned int len) {   // órdenes desde HA
  String orden;
  for (unsigned int i = 0; i < len; i++) orden += (char)datos[i];
  bool on = (orden == "ON");
  Serial2.println(on ? "R:1" : "R:0");                  // se lo pasa al Arduino (relé)
  mqtt.publish(T_VENT, on ? "ON" : "OFF", true);        // confirma el estado
}

void conectarMQTT() {
  while (!mqtt.connected()) {
    // última voluntad (LWT): si el nodo cae, el broker publica "offline"
    if (mqtt.connect(NODO, MQ_USER, MQ_PASS, T_DISP, 0, true, "offline")) {
      mqtt.publish(T_DISP, "online", true);
      anunciarSensor("vasco_clima_nodo2_temp", "Temperatura", T_TEMP, "°C", "temperature");
      anunciarSensor("vasco_clima_nodo2_hum",  "Humedad",     T_HUM,  "%",  "humidity");
      anunciarInterruptor();
      mqtt.subscribe(T_VSET);
    } else {
      delay(3000);
    }
  }
}

// Función de P3 (Sketch 3b): descompone "T:23.4;H:45.1;L:62"
void procesar(String linea) {             // "T:23.4;H:45.1;L:62"
  int i = 0;
  while (i < linea.length()) {
    int fin = linea.indexOf(';', i);
    if (fin < 0) fin = linea.length();
    String par = linea.substring(i, fin);
    char clave = par.charAt(0);
    float valor = par.substring(2).toFloat();
    if (clave == 'T') temperatura = valor;
    if (clave == 'H') humedad = valor;
    if (clave == 'L') luz = (int)valor;
    i = fin + 1;
  }
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 16, 17);   // enlace con el Arduino (P3)
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  mqtt.setServer(BROKER, 1883);
  mqtt.setBufferSize(512);                   // los JSON de discovery superan los 256 B por defecto
  mqtt.setCallback(alRecibir);
}

void loop() {
  conectarMQTT();
  mqtt.loop();
  if (Serial2.available()) {
    String linea = Serial2.readStringUntil('\n');
    procesar(linea);
    mqtt.publish(T_TEMP, String(temperatura, 1).c_str());
    mqtt.publish(T_HUM,  String(humedad, 1).c_str());
  }
}
