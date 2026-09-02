---
aliases:
  - Capa 2
  - Simulación
  - Simulacion
  - .gazebo
tags:
  - ROS
  - Incompleto
Creado: 2026-06-19
Relacionado:
  - Ubuntu
  - Rviz
  - Robotica
  - Robot
  - Linux
  - "[[Capa 3 (.ros2control)]]"
  - "[[Capa 4 (ros2_controller.yaml)]]"
  - "[[Capa 1 (Modelo 3D)]]"
---
# [[Estructura de trabajo (ROS)|Capa]] 2
## Introducción 
Cuando hablamos de la capa 2, nos referimos a la simulación, específicamente, a **Gazebo**, aquí es donde nos hacemos la siguiente pregunta:

**¿Como se comporta [[Gazebo|gazebo]] en el mundo?**
```
(xml)

\ros2_ws\src\carrito_prueba_description\urdf
	carrito_prueba.gazebo
```
Aquí es donde viven etiquetas como:
```
<gazebo> (friccion)
<mu1>, <mu2>, ... (sensores)
<camera>
<lidar>

Y diferentes plugins de simulación 
```
Se modifica cuando agregamos camaras, sensores, imu, gps, cambios físicos, etc... 

---
## Desarrollo
Una de las cosas más importantes antes de iniciar, es añadir el siguiente plugin en ``carrito_prueba.gazebo``:
```
<gazebo>
  <plugin
      filename="libgz_ros2_control-system.so"
      name="gz_ros2_control::GazeboSimROS2ControlPlugin">
  
    <parameters>
      $(find carrito_prueba_description)/config/ros2_controller.yaml
    </parameters>

  </plugin>
</gazebo>
```

**¿Porque colocamos ese Plugin?**
Este plugin es el puente entre *[[Gazebo]] <-> [[ROS|ros2]]_control*

Sin el, Gazebo sabe que existe un joint, pero no sabe que ROS quiere controlarlo, con el plugin Gazebo hace algo parecido a:
```
"ROS quiere controlar joints"
"Voy a crear controller_manager"
"Voy a leer ros2_controller.yaml"
"Voy a permitir que ROS mande comandos"
```






# Referencias
