---
aliases:
tags:
Creado:
Relacionado:
---
# Introducción
Esta nota abarcara de manera profunda la configuración de nuestro simulador [[Gazebo]], desde los primeros pasos, que tipos de archivos necesita hasta configuraciones avanzadas.

---
# Desarrollo
Una vez tengamos instalado nuestro entorno completo de [[ROS]] 2, podemos acceder a Gazebo mediante el siguiente comando en la terminal: `gz sim.

Se nos abrirá una ventana de inicio, en la que podemos elegir un mundo vacío (empty) o también multiples test pre-configurados, este mundo vacío también lo podemos abrir directamente mediante el comando: `gz sim empty.sdf`.

## Lanzar Gazebo desde ROS 2
De la manera anterior, estamos lanzando nuestro simulador completamente manual, ahora necesitamos que ROS 2 sea quien lo inicie, para ello, vamos a crear su archivo [[Capa 5 (launch)|launch]].py, como bien hemos trabajado, ya contamos con un launch de [[RViz]] llamado `display.launchp.py`dentro de nuestra carpeta launch, al mismo nivel que /[[Configuración de urdf - xacro ROS 2|urdf]], dentro de nuestro paquete `_description`, el cual creamos cuando leímos la nota titulada: [[Guía de Inicio de Entorno y Paquete Base ROS 2|Paquete ROS 2]].

Entonces, este nuevo launch pasara a llamarse `gazebo.launch.py`.

La plantilla minima que tendrá este archivo sera la siguiente:

```python
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource

from ament_index_python.packages import get_package_share_directory

import os


def generate_launch_description():

    ros_gz_sim = get_package_share_directory("ros_gz_sim")

    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(ros_gz_sim, "launch", "gz_sim.launch.py")
        ),
        launch_arguments={
            "gz_args": "empty.sdf"
        }.items()
    )

    return LaunchDescription([
        gazebo
    ])
```

La idea general de este paquete es muy sencilla:
```
gazebo.launch.py
|
|  busca el paquete
v
ros_gz_sim
|
|  utiliza su launch
v
gz_sim.launch.py
|
|  argumento: empty.sdf
v
Gazebo
```

Aquí es donde aparece el primer componente nuevo.
Ya conocemos nuestro launch, lo acabamos de crear, entonces aparece `ros_gz_sim`. Como vimos al principio, `gz sim`es Gazebo como tal, pero, `ros_gz_sim`es el paquete que nos proporciona integración de Gazebo Sim con el entorno de ROS2, incluyendo este launch que podemos reutilizar.

No estamos reinventando cómo arrancar Gazebo. Nuestro launch básicamente le dice:

> “Busca `ros_gz_sim`, utiliza su `gz_sim.launch.py` y arranca Gazebo con `empty.sdf`.”

Ademas, a continuación podemos ver algo que ya hemos utilizado en `display.launch.py`:
```python
get_package_share_directory("ros_gz_sim")
```
es el mismo concepto que cuando buscamos:
```python
get_package_share_directory("rover_description")
```

Solo cambia **qué paquete estamos buscando**.

Antes incluso de crear el archivo, podemos verificar que tenemos instalado:
```
ros2 pkg prefix ros_gz_sim
```
Si devuelve una ruta, tenemos disponible `ros_gz_sim`.


---
# Referencias
