---
aliases:
  - gazebo
tags:
  - ROS
  - En_curso
Creado: 2026-06-24
Relacionado:
  - Simulacion
  - Robotica
  - Rviz
  - Linux
  - Ubuntu
---
# Introducción
Esta nota solamente aborda que es Gazebo de una manera muy superficial, para más información a profundidad sobre su utilización, consultar la siguiente nota: [[Configuración Gazebo]].

---
# Desarrollo
**Gazebo** es un potente simulador de robots 3D que permite probar modelos físicos, sensores y algoritmos en un entorno virtual realista antes de usarlos en el mundo real.

Mientras que **[[ROS]] 2** actúa como el "cerebro" del robot procesando datos y enviando comandos, **[[RViz]]** es la herramienta de visualización en tiempo real que permite ver lo que el robot "piensa" y "percibe" (como mapas, nubes de puntos laser o transformadas de coordenadas). En conjunto, forman el ecosistema estándar para el desarrollo de software robotico.

## ¿Como se conecta todo?
El flujo de trabajo habitual en que **Gazebo** calcula física y simula los sensores del entorno, **ROS 2** intermedia los mensajes entre las plataformas mediante un puente de comunicación, y **RViz** renderiza los datos lógicos para el desarrollador.

```
GAZEBO <- (Fisica y Sensores Simulados)
^
|         (Puente de red / ros_gz_bridge)
v
ROS 2  <- (Nodos, Controladores y Topicos)
^
|         (Topicos de visualizacion /scan)
v
RViz  <-  (Graficos de lo que ve el robot)
```

## Integración y Conexión General
1. Instalar el puente de Comunicación (`ros-jazzy-ros-gz`).
2. Definir el modelo del robot ([[Configuración de urdf - xacro ROS 2|URDF]]).
3. Ejecutar el Puente (`ros_gz_bridge`).
4. Visualizar en RViz.


# Referencias
