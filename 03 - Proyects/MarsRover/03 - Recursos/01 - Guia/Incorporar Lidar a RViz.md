---
aliases:
  - Incorporar Lidar
tags:
  - MarsRover
  - Lidar
  - RViz
Creado: 2026-09-10
Relacionado:
  - Github
  - Linux
  - ROS2
---
# Introducción
Esta nota trata sobre los pasos a seguir para incluir el [[Sensor Lidar]] LD19 en [[ROS]] 2 y su visualización en [[RViz]].

**Repositorio Oficial:** https://github.com/ldrobotSensorTeam/ldlidar_ros2.git

---
# Desarrollo
1. Creamos un Workspace para almacenar el paquete del Lidar:
```
cd ~ 
mkdir -p ldlidar_ros2_ws/src 
cd ~/ldlidar_ros2_ws/src
```
Esto de preferencia fuera del proyecto que tenemos, osea, a la misma altura de nuestro `/ros2_ws` (si es que ya tienes un workspace dediaco a `ros2_ws`).

Entonces quedaria una ruta como: 
```
/Tu_workspace_de_ros
	/ros2_ws
		/src
	/ldlidar_ros2_ws
		/src
```
Entonces, una vez dentro de la carptea `ldlidar_ros2_ws/src`:

2. Clonamos el repositorio oficial:
```
git clone https://github.com/ldrobotSensorTeam/ldlidar_ros2.git
```

3. Entramos al repositorio e inicializamos sus submódulos:
```
cd ~/ldlidar_ros2_ws/src/ldlidar_ros2
git submodule update --init --recursive
```
El repo oficial incluye un submódulo `sdk`, que es necesario para compilar el driver.

4. Conectamos el Lidar mediante su adaptador USB-UART.
>En mi caso, el adaptador apareció como un CP210x de Silicon Labs, lo comprobamos con: `lsusb`

>Comprobamos el dispositivo serie: `ls /dev/ttyUSB*`

Si obtenemos respuesta entonces si se está detectando correctamente.

5. Comprobamos permisos del puerto:
```
ls -l /dev/ttyUSB0 
(o el puerto que te arroje el comando anterior)
```
En mi equipo el dispositivo pertinence al grupo `dialout`y mi usuario también, así que no se necesitaba usar permisos externos de forma permanente.

El README oficial propone como ejemplo:
`sudo  chmod 777 /dev/ttyUSB0`

6. Revisar el [[Capa 5 (launch)|launch]] del LD19, abrimos:
```
~/ldlidar_ros2_ws/src/ldlidar_ros2/launch/ld19.launch.py
```
y verificamos que tuviera: `{'port_name': '/dev/ttyUSB0'},`

Ademas, para este LD19 aparecen parámetros como:
```
product_name: LDLiDAR_LD19
frame_id: base_laser
laser_scan_topic_name: scan
point_cloud_2d_topic_name: pointcloud2d
serial_baudrate: 230400
```
El launch también publica una transformación estática entre: `base_link -> base_laser`.

Con una traslación vertical de aproximadamente `0.18 m`.

7. Compilar el Workspace:
```
cd ~/ldlidar_ros2_ws
colcon build
```

## Problema de mi Sistema
Cuando intente compilar apareció este problema especifico en mi sistema, puede que a ti no te suceda, si es así, omite está secession.

- En la compilación aparecieron errores como:
```
pthread_mutex_init was not declared
pthread_mutex_lock was not declared
pthread_mutex_unlock was not declared
```
en: `sdk/src/log_module.cpp`

Así que añadí: `#include <pthread.h>
en: `~/ldlidar_ros2_ws/src/ldlidar_ros2/sdk/src/log_module.cpp`

- Después limpie la compilación anterior:
```
cd ~/ldlidar_ros2_ws
rm -rf build install log
```
y recopilamos con: `colcon build`.
Después de eso compilo correctamente.

## Cargar el paquete en el entorno de ROS 2
8. Después de compilar correctamente, hacemos:
```
source ~/ldlidar_ros2_ws/install/setup.bash
```
El README oficial usa:
```
source install/local_setup.bash
```
Ambos tienen propósitos ligeramente distintos, pero para nuestro flujo usamos `setup.bash`, que carga el workspace incluyendo sus underlays. El punto clave es que hay que cargar el entorno generado para que ROS 2 conozca el paquete.

**Importante:** Hacer `source` no enciende el LiDAR. Solo hace visible el paquete en esa terminal.

9. Lanzamos el driver del LD19, ejecutamos:
```
ros2 launch ldlidar_ros2 ld19.launch.py
```
Este es precisamente el comando que el repositorio oficial indica para el LD19. También ofrece un launch específico para abrirlo junto con RViz:
```
ros2 launch ldlidar_ros2 viewer_ld19.launch.py
```
 En la ejecución aparecieron mensaje como los que están a continuación, esto confirma que el puerto serie abrió, el driver reconoció el sensor y el [[Capa 7 (Lógica)|nodo]] empezó a publicar datos.
```
LDLiDAR SDK Pack Version is:3.3.1
<product_name>: LDLiDAR_LD19
<laser_scan_topic_name>: scan
<point_cloud_2d_topic_name>: pointcloud2d
<frame_id>: base_laser
<port_name>: /dev/ttyUSB0
<serial_baudrate>: 230400
ldlidar serial connect is success
ldlidar communication is normal.
ldlidar driver start is success.
start normal, pub lidar data
```

10. Comprobamos el tipo del tópico:
```
ros2 topic info /scan
```
Y obtuvimos:
```
Type: sensor_msgs/msg/LaserScan
Publisher count: 1
```
Eso confirmó que había un nodo publicando un mensaje estándar de ROS 2 para LiDAR 2D.

Después ejecutamos:
```
ros2 topic echo /scan --once
```
Y recibimos un `sensor_msgs/msg/LaserScan` real, con campos como:
```
frame_id: base_laser
angle_min: 0
angle_max: ~6.283
range_min: 0.02
range_max: 12.0
ranges: [...]
intensities: [...]
```
Algunas posiciones aparecían como:
```
.nan
```
lo cual simplemente indica una medición inválida o ausencia de retorno válido en esa dirección.

Este paso fue importante porque antes de culpar a RViz confirmamos que el LiDAR ya estaba enviando datos correctamente.

11. Abrimos RViz
Con el driver todavía ejecutándose en la primera terminal, en una segunda:
```
source ~/ldlidar_ros2_ws/install/setup.bash
rviz2
```
El README oficial indica usar RViz2 para visualizar los datos del paquete.

12. Configurar el `Fixed Frame`.
En:
```
Global Options
→ Fixed Frame
```
pusimos:
```
base_laser
```
porque el propio mensaje `/scan` indicaba:
```
frame_id: base_laser
```
Así RViz podía interpretar directamente las coordenadas del escáner.

Cuando integras el LiDAR al rover completo, probablemente será más conveniente usar:
```
base_link
```
como `Fixed Frame`, porque ya existe la transformación:
```
base_link → base_laser
```
y RViz puede transformar automáticamente los datos del sensor.

13. Añadir el LaserScan.
En RViz:
```
Add
→ By display type
→ LaserScan
```
y en:
```
Topic
```
seleccionamos:
```
/scan
```
El estado terminó mostrando:
```
Global Status: Ok
LaserScan Status: Ok
```
y aparecieron los puntos del LiDAR alrededor del origen.

Entonces confirmamos que funciona correctamente.

## Utilización diaria
Ahora que ya está instalado, el procedimiento es más corto. En una terminal:
```
source ~/ldlidar_ros2_ws/install/setup.bash
ros2 launch ldlidar_ros2 ld19.launch.py
```
y en otra:
```
source ~/ldlidar_ros2_ws/install/setup.bash
rviz2
```
Después en RViz:
```
Fixed Frame → base_laser
LaserScan → /scan
```

---
# Referencias
