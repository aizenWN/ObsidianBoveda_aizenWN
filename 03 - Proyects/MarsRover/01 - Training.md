---
aliases:
tags:
  - MarsRover
  - Completado
Creado: 2026-09-04
Relacionado:
  - "[[ROS]]"
  - Programacion
  - Software
---
# Introducción
En está nota se documentara todo lo visto en el Training 01 (ROS) de Mars Rover para la seccion de Software.

---
# Desarrollo
Siempre utlizar camel_case (es está forma de separar con guion bajo las palabras) para evitar problemás de compilacion

Comando en la terminal para crear nuevo paquete ROS:
```python
aizen@asus-vivobook:/Data/mars_rover/ros2_ws/src$ ros2 pkg create nombre_paquete --build-type ament_python --dependencies rclpy 
```


Comando en la terminal para crear nuevo paquete ROS:
```cpp
aizen@asus-vivobook:/Data/mars_rover/ros2_ws/src$ ros2 pkg create training_uno_cpp --build-type ament_cmake --dependencies rclcpp 
```


## Colcon para un solo paquetre
```
aizen@asus-vivobook:/Data/mars_rover/ros2_ws$ colcon build --packages-select training_uno
```

## Colcon para todos los paquetes
```
aizen@asus-vivobook:/Data/mars_rover/ros2_ws$ colcon build
```

## ROS2 es Agnostico al Lenguaje
No importa en que lenguaje programaste tu [[Capa 7 (Lógica)|nodo]], se pueden comunicar entre ellos sin problemas.

rdlpy (Codigo de python)
|
rcl (Libreria escrita en C)
|
rclcpp (Codigo en C++)

Se comunican sin problemas

## ALT + CTRL + T
Atajo de teclado para abrir nueva terminal

## Cambiar termporalmente el nombre de nodo
```
ros2 run training_uno primer_nodo --ros-args -r __node:= <nuevo_nombre>
```
## Comando para crear ejecutable en nodos python
```
Para crear ejecutable en archivo de python: chmod +x primer_nodo.py
```
ls
Si cambia de color a amarillo se volvio ejecutable

## Topicos

### python









# Por organizar
aizen@asus-vivobook:/Data/mars_rover/ros2_ws/src/training_uno$ touch primer_nodo.py
aizen@asus-vivobook:/Data/mars_rover/ros2_ws/src/training_uno$ cd mi
bash: cd: mi: No existe el archivo o el directorio
aizen@asus-vivobook:/Data/mars_rover/ros2_ws/src/training_uno$ cd training_uno/
aizen@asus-vivobook:/Data/mars_rover/ros2_ws/src/training_uno/training_uno$ ls
__init__.py  primer_nodo.py
aizen@asus-vivobook:/Data/mars_rover/ros2_ws/src/training_uno/training_uno$ 





---
# Referencias
