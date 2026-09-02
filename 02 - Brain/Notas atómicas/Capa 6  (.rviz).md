---
aliases:
  - Capa 6
  - .rviz
tags:
  - ROS
  - Incompleto
Creado: 2026-06-19
Relacionado:
  - "[[Capa 1 (Modelo 3D)]]"
  - "[[Capa 2 (Simulación)]]"
  - "[[Capa 3 (.ros2control)]]"
  - "[[Capa 4 (ros2_controller.yaml)]]"
  - "[[Estructura de trabajo (ROS)]]"
  - Rviz
  - Robotica
  - Robot
  - Ubuntu
  - Programacion
  - Linux
  - Simulacion
  - "[[Capa 5 (launch)]]"
---
# Capa 6
## Introducción
La pregunta que se busca responder en está capa es.

**¿Como quiero visualizar información?**

Los archivos que podemos encontrar en está sección son los siguientes:
```
(yaml)

\ros2_ws\src\carrito_prueba_description\config
	display.rviz
	gazebo.rviz
```
En este apartado, [[RViz|Rviz]] no controla nada, no simula nada, solo dibuja (guarda la apariencia del programa), entonces se podría borrar Rviz y el robot sigue funcionando perfectamente, no tiene nada que ver con el Robot directamente.

Es simplemente un archivo de configuración de Rviz.

---
## Desarrollo
Si abrimos un archivo ``.rviz``, encontraremos cosas parecidas a:
```
Panels:
	-Class: rviz_common/Displays
	
Visualization Manager:
	Display:
		- Class: rviz_default_plugins/RobotModel
		  Enabled: true
		  
		- Class: rviz_default_plugins/Grid
		  Enabled: true
```
- **Panels:** Activa el panel lateral principal de RViz (llamado "Displays" o Visualizaciones).
- **Visualization Manager:** Abre la sección dedicada a gestionar todo lo que se va a dibujar en el espacio 3D.
- **Class:** Dibuja el suelo de rejilla (cuadricula) gris en el fondo, el cual sirve como referencia visual para saber donde está el suelo y medir distancias a simple vista, está activado por defecto ``true``.
---
**Que cosas puede guardar**
1. **Camara (Posición, zoom, orientación):** Para que siempre abras RViz viendo el robot desde el mismo ángulo.
2. **Grid (Cuadricula del suelo):** Se puede modificar tamaño, color, resolución.
3. **RobotModel:**  Leer ``/robot_description``.
4. **TF (Sistemas de referencia):** Los ejes XYZ, base_link -> joint1 -> pendulo_1.
5. **[[Capa 7 (Lógica)|Tópicos]] (Visualizar información de [[ROS]]):** LaserScan, PointCloud, Odometry, IMU.









# Referencias
