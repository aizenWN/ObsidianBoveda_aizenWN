---
aliases:
  - Capa
  - Estructura de trabajo
  - Capas
tags:
  - ROS
  - Incompleto
Creado: 2026-06-18
Relacionado:
  - "[[Capa 3 (.ros2control)]]"
  - "[[Capa 4 (ros2_controller.yaml)]]"
  - "[[Capa 1 (Modelo 3D)]]"
  - "[[Capa 2 (Simulación)]]"
  - "[[Microcontroladores]]"
  - "[[Python]]"
  - "[[C++]]"
  - "[[STM]]"
  - "[[ESP32]]"
  - "[[Micro-ROS]]"
  - "[[RaspBerry]]"
  - "[[ROS]]"
---
# Forma de trabajo
## Introducción 
ROS2 (Robot Operating System 2) es un **[[Framework|framework]]** de código abierto y un marco de [[Middleware]] (Software que actúa como un puente o intermediario ente diferentes aplicaciones, sistemas o componentes) diseñado específicamente para el desarrollo de software y sistemas robóticos.

| Capa                      | Se programa mucho | Frecuencia |
| ------------------------- | ----------------- | ---------- |
| 01 - Modelado 3D          | No                | Baja       |
| 02 - Simulacion           | Si                | Alta       |
| 03 - ros2_control         | Si                | Media      |
| 04 - ros2_controller.yaml | Si                | Media      |
| 05 - Launch               | Si                | Alta       |
| 06 - RViz                 | No                | Muy baja   |
| 07 - Nodos                | Si                | Muy alta   |

[[Ejecución Real (Como se conectan las capas).canvas]]





# Referencias
