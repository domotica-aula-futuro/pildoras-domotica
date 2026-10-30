# Píldoras formativas · Domótica para el aula del futuro

Material de las siete píldoras del primer trimestre (curso 2026-27, del 2 de noviembre al 18 de diciembre) de la agrupación de centros «Domótica para el aula del futuro»: de Arduino y ESP32 a Home Assistant.

> Proyecto de agrupación de centros financiado por el Ministerio de Educación, Formación Profesional y Deportes. El contenido compromete exclusivamente a sus autores.

## Centros
IES Vasco de la Zarza (Ávila, coordinador) · IES Alonso Quijano (Quintanar de la Orden) · IES Comercio (Logroño) · IES Federica Montseny (Burjassot) · IES Politècnic (Palma) · IES La Guancha (Tenerife)

## Píldoras
| | Píldora | Semana | Imparte | Material (numeración anterior) |
|---|---|---|---|---|
| P0 | Arranque y Home Assistant OS propio: proyecto, GitHub, instalación de HA OS y pretest | 2–6 nov | IES Vasco de la Zarza | P0 (actualizada) y P4 · [Ficha 2 «Ejes»](pdf/Ficha_2_Ejes_competencias.pdf) |
| P1 | Arduino y ESP32: E/S digitales y analógicas, sensores y WiFi | 9–13 nov | IES Politècnic | P1, P2 · [codigo/P1](codigo/P1), [codigo/P2](codigo/P2) |
| P2 | Buses y pasarela Arduino–ESP32 (UART, I2C) | 16–20 nov | IES Politècnic | P3 · [codigo/P3](codigo/P3) |
| P3 | ESPHome y MQTT en el Home Assistant del aula | 23–27 nov | IES Federica Montseny | P5, P6 · [codigo/P5](codigo/P5), [codigo/P6](codigo/P6) |
| P4 | Automatizaciones, paneles, historial y análisis de datos | 30 nov – 4 dic | IES Federica Montseny e IES Alonso Quijano | P7, P8 · [codigo/P7](codigo/P7), [codigo/P8](codigo/P8) |
| P5 | Actuadores y seguridad eléctrica | 9–11 dic | IES La Guancha | P9 · [codigo/P9](codigo/P9) |
| P6 | Red del aula y ciberseguridad básica + mini-reto | 14–18 dic | IES Comercio | P10 |

Los PDF están en [`pdf/`](pdf).

**Ficha 2 «Ejes»** ([PDF](pdf/Ficha_2_Ejes_competencias.pdf)): autoevaluación de las 9 competencias transversales en tres momentos (pretest en P0, intermedio el 12 de febrero y postest en EvaluAR). Imprímela, rellénala y sube una foto a tu carpeta de `practicas-pildoras`. P0 ya sigue el calendario actual; P1–P10 conservan la numeración anterior (once píldoras) hasta que se reagrupen según esta tabla.

## Uso del código
- Los sketches `.ino` están cada uno en su carpeta, como exige Arduino IDE.
- Las contraseñas aparecen como `********` o `!secret`: nunca subas las reales. Copia `codigo/P5/secrets.yaml.example` como `secrets.yaml` en ESPHome.
- Los umbrales (26 °C, 800/1200 ppm de CO2…) son valores de ejemplo para la práctica.

## Evidencias del alumnado
Van en el repositorio privado `practicas-pildoras`, no en este.

## Licencia
Material educativo abierto para su reutilización por otros centros. <!-- Elegid la licencia en la reunión de coordinación, p. ej. CC BY-SA 4.0 para los PDF y MIT para el código. -->
