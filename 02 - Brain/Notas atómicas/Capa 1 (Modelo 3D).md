---
aliases:
  - Meshes
  - Capa 1
  - .xacro
  - Modelo 3D
tags:
  - ROS
  - Incompleto
Creado: 2026-06-18
Relacionado:
  - "[[Capa 4 (ros2_controller.yaml)]]"
  - "[[Capa 3 (.ros2control)]]"
  - Gazebo
  - Linux
  - Programacion
  - Ubuntu
  - Sistemas Embebidos
  - Simulacion
  - Robotica
  - Robot
  - Rviz
---
# [[Estructura de trabajo (ROS)|Capa]] 1
## Introducción 
Básicamente nos referimos a capa 1, cuando estamos hablando de todo lo relacionado al modelado 3D, en principio exportado originalmente de algún programa CAD (Fusion 360, SolidWorks, AutoCAD, etc...), mediante algún script de la comunidad para exportar todo el modelado a formato .[[Configuración de urdf - xacro ROS 2|urdf]] o .xacro.

## Desarrollo
En este momento, gracias al script con el que se está trabajando, nos quedara un archivo, el cual dentro contendrá la siguiente carpeta con los siguientes archivos:
```
Ejemplo

\ros2_ws\src\carrito_prueba_description\meshes
	base_link.stl
	llanta_1_1.stl
	llanta_2_1.stl
	llanta_3_1.stl
	llanta_4_1.stl
```
Estos archivos tal cual son el modelado 3D, se reconocen fácil por ser los siguientes tipos de formato:
``.stl / .f3d / .step``

Tambien vamos a obtener la siguiente carpeta en la ruta especificada:
```
Ejemplo (xml)

\ros2_ws\src\carrito_prueba_description\urdf
	carrito_prueba.xacro
	materials.xacro
```
Estos archivos contienen formato de texto tipo ``xml``, el cual tienen como objetivo definir físicamente al robot.

**¿Que se modifica?**
Forma del chasis, ruedas, soportes, sensores, etc.
Normalmente se modifica al principio del proyecto, en está parte, aun no tenemos ninguna relación con una placa de desarrollo, ni con el simulador.
##  Ejemplo
Dentro de estos archivos ``xml`` podemos encontrar algunas de las siguientes etiquetas:
```
<link> (piezas fisicas)
<joint> (articulaciones / uniones)
<mass> (masas)
<inertial> (inercias)
```
Como podemos ver, después de exportar nuestro modelo mediante el script, ya no solo tenemos un modelado 3D, sino que lo hemos definido, que partes del modelos son las que se mueven, cuales son sus centros de masa, sus inercias, cuantas piezas físicas tenemos, etc.




# Referencias
