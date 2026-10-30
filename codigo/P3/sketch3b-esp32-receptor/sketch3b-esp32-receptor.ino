#define RXD2 16
#define TXD2 17

float temperatura = NAN, humedad = NAN;
int luz = -1;

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
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
}

void loop() {
  if (Serial2.available()) {
    String linea = Serial2.readStringUntil('\n');
    linea.trim();
    procesar(linea);
    Serial.printf("T=%.1f  H=%.1f  L=%d\n", temperatura, humedad, luz);
  }
}
