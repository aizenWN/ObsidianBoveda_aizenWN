---
aliases:
  - Lidar
  - lidar
  - sensor lidar
tags:
  - Componente
  - En_curso
Creado: 2026-08-22
Relacionado:
  - "[[Electronica]]"
  - Robotica
  - "[[ROS]]"
---
# Introducción
Esta nota describe que es un Sensor Lidar, como funciona y más para tener una idea general sobre este modulo.

---
# Desarrollo
### ¿Que es?
Lidar significa *Light Detection and Ranging (Detección y Rango por Luz)*

Funciona enviando pulsos de luz láser invisibles y midiendo cuanto tiempo tarda el haz en rebotar contra un objeto y regresar al sensor (mecanismo llamado Tiempo de Vuelo o Time of Flight - ToF).

**Distancia = (Velocidad de la luz * Tiempo) / 2**

Como el láser viaja a la velocidad de la luz, el sensor puede realizar miles de estas mediciones por segundo. Con ellas crean un mapa de puntos de distancia alrededor del robot.

### Tipos de Lidar
1. **Lidar 2D (Monoplano):**
Un emisor y receptor láser rotan sobre un motor a alta velocidad (360°). Escanea un único plano horizontal a una altura fija.

- **Uso:** Mapeo de interiores, SLAM 2D y esquivar obstáculos en carros tipo Rover/AGV.
- **Ejemplo:** Tu sensor **LD Lidar D300** o los sensores de las aspiradoras robóticas.

2. **Lidar 3D (Multicapa):**
Apila múltiples haces láser verticalmente (16, 32, 64 o 128 lineas) mientras gira, generando una nube de puntos tridimensionales (x, y, z).

- **Uso:** Vehículos autónomos de carretera (Tesla, Waymo) y drones.

3. **Lidar Solid State (Estado Solido):**
No tiene piezas mecánicas móviles que giren; usa matrices de micro-espejos para dirigir el láser. Es más duradero, aunque con menor campo de visión.

---
# Referencias
