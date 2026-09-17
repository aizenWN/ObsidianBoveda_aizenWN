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

## comandos terminal para ros2
Si das bloque tab aparecen las opciones que tiene cada comando
Ejemplo: ros2 topi (tab x2) despliega: echo, list, etc.

- ros2 node list
- ros2 node info /noticiero_2
- ros2 topic list
- ros2
- ros2 topic hz (frecuencia con la que publica)
- ros2 topic bw (ancho de banda / en el [[Sensor Lidar|lidar]] consume mucho ancho de banda a la hora de enviar datos)
- ros2 interface show
- rqt (Nos abre (algo) nos vamos a la partes de plugins/topics/message publisher) por corroborar
- rqt_graph (Creo que podemos ver  como está la conexion entre publisher y suscribers, algo asi)
- rqt_plot

## Clientes y servicios

### ROS 2 Service
Tienen la siguiente estructura: 

AddTwoInts

int64 a REQUEST (lo que envía el client)
int64 b client
|
v
int a+b RESPONSE (lo que el service responde)

Son bidireccionales, el client le envía información al service y el service al client, 

#### Comunicacion Sincrona
El cliente se queda congelado hasta que el service recibe una respues (no es recomendable usarlo nunca)
Si por alguna razon el service está caido, el client se queda congelado

#### Comunicacion asincrona
No se queda congelado

### Client
Es el comensal que lee el menu, decide que quiere y le pide la oprdean al mesero (envía la peticion)
Trabaja con un objeto futue
Genera una peticion (Request)
Es dependiente de la existencia del Servidor
Relacion muchos a uno (N a 1)

Asi se declara que sea asincrono el client
future = self.client_.call_async(request)

### Herramientas de debuggeo
- ros2 service list (muestra los servicios que existen)
- ros2 service type /sumador
- ros2 service find /example_interfaces/srv/AddTwoInts (servicio)
- ros2 interface show example_interfaces/srv/AddTwoInts
- ros2 interface list | grep msg/actions/
- rqt_graph (está interfaz para observar la comunicacion)
- rqt_plot



# Por organizar
aizen@asus-vivobook:/Data/mars_rover/ros2_ws/src/training_uno$ touch primer_nodo.py
aizen@asus-vivobook:/Data/mars_rover/ros2_ws/src/training_uno$ cd mi
bash: cd: mi: No existe el archivo o el directorio
aizen@asus-vivobook:/Data/mars_rover/ros2_ws/src/training_uno$ cd training_uno/
aizen@asus-vivobook:/Data/mars_rover/ros2_ws/src/training_uno/training_uno$ ls
__init__.py  primer_nodo.py
aizen@asus-vivobook:/Data/mars_rover/ros2_ws/src/training_uno/training_uno$ 


>Nota: siempre abrir el VSC dentro de src (/Data/mars_rover/ros2_ws/src code .)

# PYTHON O C++
Python para calculos pesado
C++ cuando son cosas de driver, comunicacion con hardware.


---
# Referencias
