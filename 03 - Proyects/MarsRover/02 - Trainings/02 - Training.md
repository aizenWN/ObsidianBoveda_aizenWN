---
aliases:
tags:
  - MarsRover
  - Completado
Creado: 2026-09-16
Relacionado:
  - "[[ROS]]"
  - ROS2
  - Programacion
  - Software
---
# Introducción
En está nota se documentara todo lo visto en el Training 02 (ROS) de Mars Rover para la seccion de Software.

---
# Desarrollo
Custom interface (interfaz personalizada)

Es un archivo de configuración como .msg, .srv

Se puede crear un custom interface utilizando el typename que tiene por defecto ros

## Custom Interface
ros2 interface list
ros2 interface package sensor_msg
ros2 interface show 

ros2 interface package nav_msg

### Se puede crear uno completamente nuevo si aquí queremos
Se recomienda tener un paquete especifico para los custom interfaces
aizen@asus-vivobook:/Data/mars_rover/ros2_ws/src$ ros2 pkg create prueba_custom_interfaces --build-type ament_cmake
going to create a new package

remover: rm -r include/ src/

Saber que funciona 
ros2 interfaces show prueba_custom_interfaces/msg/HardwareStatus

se crea un paquete exclusivo para los custom, se borra src y include y se añade la carpeta msg, se añade información en CMake y en packages

#### Utilizarlos


## NameSpace
Si tengo un [[Capa 7 (Lógica)|topico]] enviando 2 imagenes, se le puede poner un namespace para identificar que imagen le llega a cada robot sin necesidad de declarar un segundo topico para enviarlos por separado.

se puede agregar desde un comando en la terminal o desde un [[Capa 5 (launch)|launch]]
Terminal: `ros2 run <Nombre del paquete donde esta tu nodo> <Nombre del ejecutable> --ros-args -r __ns:=<Namespace ha agregar>`

kill id -a pid (process ID)
Se puede matar un comando mediante su ID en la terminal si no muere con Ctrl + C

---
# Referencias
