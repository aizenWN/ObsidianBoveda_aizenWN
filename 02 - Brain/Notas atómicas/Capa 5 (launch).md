---
aliases:
  - Capa 5
  - launch
  - .launch.py
  - .launch.cpp
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
  - Ubuntu
  - Simulacion
  - Robotica
  - Robot
  - Programacion
  - Linux
  - Gazebo
---
# Capa 5
## Introducción 
En está capa es donde nos hacemos la siguiente pregunta:

**Que programas quiero arrancar**
De hecho, estos archivos lo podemos ver de igual manera como nuestro ``main()``, no del [[Capa 7 (Lógica)|nodo]], controladores, ni joint, sino que es **de el robot completo**.

Los tipos de archivos que te puedes encontrar en está capa son los siguientes:
```
(Python)

\ros2_ws\src\carrito_prueba_description\launch
	display.launch.py
	gazebo.launch.py
```
Aquí no se encuentra la lógica, solo sirve para arrancar / ejecutar cosas, por ejemplo:
- Abrir [[Gazebo]]
- Cargar robot
- Iniciar controller_manager
- Abrir [[Capa 6  (.rviz)|Rviz]]

**Nota:** Recuerda, no es el motor, es el interruptor que enciende todo el sistema

---
## Desarrollo (gazebo.launch.py)
En está ocasión, solo nos concentraremos en el launch ``gazebo.launch.py``.

En estos archivos te puedes encontrar con los siguientes comandos: 
```
robot_state_publisher
gz_sim
joint_state_broadcaster
velocity_controller
```
Cuando ejecutamos ``gazebo.launch.py``, [[ROS]] entra a ``def generate_launch_description();`` y va creando cosas.

Las partes que ya existen en este archivo desde el inicio son:
- ``robot_state_publisher``
- ``gazebo``
- ``spawn_robot``
- ``ros_gz_bridge``
- ``return LaunchDescription([gazebo, spawn_robot, ros_gz_bridge, robot_state_publisher,])``

---
### ros_gz_bridge (ya existente)
Este es extremadamente importante ya que ROS y Gazebo hablan idiomas distintos.

ROS ---- (No se entienden) ---- Gazebo
*Entonces añadimos*
ROS ---- (ros_gz_bridge) ---- Gazebo

De está manera utilizamos este traductor para que pueda fluir la comunicación, a futuro ``IMU, Lidar, Cámara, Odometria, Clock`` casi siempre pasaran por un ``bridge``.

A partir de aquí, añadiremos cosas nuevas a nuestro ``launch``.

---
### joint_state_broadcaster_spawner
Aquí ya entramos con nuestro primer contacto real con ROS Control

Remontémonos a la [[Capa 4 (ros2_controller.yaml)|Capa 4]], nuestro .yaml, en este archivo de texto configuramos una instancia llamada ``joint_state_broadcaster`` del tipo / controlador ``JointStateBradcaster``.

En esa línea solamente configuramos la instancia, pero todavía no la crea.

En la línea ``executable='spawner'``, le decimos al **Nodo** ``controller_manager``:
*Crea una instancia ``joint_state_broadcaster``*

---
### velocity_controller_spawner
Exactamente la misma idea, le decimos a nuestro **Nodo** ``controller_manager``
*Crea la instancia ``velocity_controller``*

La cual fue definida igualmente en nuestra [[Capa 4 (ros2_controller.yaml)|Capa 4]].

Justo aquí es donde ocurre algo muy importante, en este momento es cuando nace ``/velocity_controller/commands``, el [[Capa 7 (Lógica)|tópico]] (nuestro cable de comunicación directo hacia los controladores de ROS), este tema se hablara más adelante en la [[Capa 7 (Lógica)]].

Visualmente, el flujo de trabajo se vería así:
```
.yaml
	Define la instancia
	
Spawner
	La crea
	
Controlador (Cargado a nuestras instancias)
	Crea sus tópicos 
```

---
### [[RViz|rviz]]_node
Esto simplemente sirve para **Abrir RViz automáticamente** 

No tiene ningún tipo de relación con el control, solo es la comodidad de ejecutar un solo launch y que se abran ambos programas.

**Nota:** Antes del nodo, añadimos la siguiente línea de código:
``rviz_config_file = os.path.join(pkg_ros_gz_rbot, 'config', 'display.rviz') #Añadido``

---
### return LaunchDescription
Originalmente, solo teníamos:
```
return LaunchDescription([
	gazebo,
	spawn_robot,
	ros_gz_bridge,
	robot_state_publisher,
])
```

Pero recordamos que acabamos de utilizar nuevos ejecutables en nuestro archivo, las hemos configurado y definido, pero nos falta ejecutarlas a la hora de lanzar nuestro launch, para esto sirve nuestro ``return``, nos falta agregarlas, una vez hecho, quedaría de la siguiente manera:

```
return LaunchDescription([
	gazebo,
	spawn_robot,
	ros_gz_bridge,
	robot_state_publisher,
	joint_state_broadcaster_spawner, ----------------------------------> #Añadido
	velocity_controller_spawner,     ----------------------------------> #Añadido
	rviz_node,                       ----------------------------------> #Añadido
])

Nota: Todos aquí son Nodos, aunque ninguno es creado por nosotros, son pre-configurados por ROS o rviz2, el sufijo "spawner"  se refiere a lanzar el nodo spawner de ROS, cuya tarea es crear la instancia.
```

---
## Proyección a Futuro
La mayoría de las veces no vamos a tocar ``gazebo, robot_state_publisher, spawn_robot``
Lo que realmente va a crecer sera:
```
Node(
    package='carrito_prueba_control',
    executable='adelante'
)

Node(
    package='carrito_prueba_control',
    executable='seguir_linea'
)

Node(
    package='carrito_prueba_control',
    executable='evitar_obstaculos'
)
```
Recordemos que al principio estaremos modificando / manipulando mucho .[[Configuración de urdf - xacro ROS 2|urdf]] / .xacro, .yaml, ros2_control, ya que estaremos definiendo los parámetros de nuestro robot, el mundo simulado y sus características, después en su mayoría nos concentraremos en la lógica de movimiento (Nodos).

## Código Original
gazebo.launch.py

```
import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, TimerAction
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
import xacro
from os.path import join

def generate_launch_description():

    pkg_ros_gz_sim = get_package_share_directory('ros_gz_sim')
    pkg_ros_gz_rbot = get_package_share_directory('carrito_prueba_description')


    robot_description_file = os.path.join(pkg_ros_gz_rbot, 'urdf', 'carrito_prueba.xacro')
    ros_gz_bridge_config = os.path.join(pkg_ros_gz_rbot, 'config', 'ros_gz_bridge_gazebo.yaml')
    
    robot_description_config = xacro.process_file(robot_description_file)
    robot_description = {'robot_description': robot_description_config.toxml()}

   
    robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        output='screen',
        parameters=[robot_description],
    )

   
    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(join(pkg_ros_gz_sim, "launch", "gz_sim.launch.py")),
        launch_arguments={"gz_args": "-r -v 4 empty.sdf"}.items()
    )

    spawn_robot = TimerAction(
        period=5.0,  
        actions=[Node(
            package='ros_gz_sim',
            executable='create',
            arguments=[
                "-topic", "/robot_description",
                "-name", "carrito_prueba",
                "-allow_renaming", "false",  # prevents "_1" duplicate
                "-x", "0.0",
                "-y", "0.0",
                "-z", "0.32",
                "-Y", "0.0"
            ],
            output='screen'
        )]
    )

    ros_gz_bridge = Node(
        package='ros_gz_bridge',
        executable='parameter_bridge',
        parameters=[{'config_file': ros_gz_bridge_config}],
        output='screen'
    )

    return LaunchDescription([
        gazebo,
        spawn_robot,
        ros_gz_bridge,
        robot_state_publisher,
    ])

```

## Código Actualizado
gazebo.launch.py

```
import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, TimerAction
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
import xacro
from os.path import join

def generate_launch_description():

    pkg_ros_gz_sim = get_package_share_directory('ros_gz_sim')
    pkg_ros_gz_rbot = get_package_share_directory('carrito_prueba_description')


    robot_description_file = os.path.join(pkg_ros_gz_rbot, 'urdf', 'carrito_prueba.xacro')
    ros_gz_bridge_config = os.path.join(pkg_ros_gz_rbot, 'config', 'ros_gz_bridge_gazebo.yaml')
    
    robot_description_config = xacro.process_file(robot_description_file)
    robot_description = {'robot_description': robot_description_config.toxml()}

   
    robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        output='screen',
        parameters=[robot_description],
    )

   
    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(join(pkg_ros_gz_sim, "launch", "gz_sim.launch.py")),
        launch_arguments={"gz_args": "-r -v 4 empty.sdf"}.items()
    )

    spawn_robot = TimerAction(
        period=5.0,  
        actions=[Node(
            package='ros_gz_sim',
            executable='create',
            arguments=[
                "-topic", "/robot_description",
                "-name", "carrito_prueba",
                "-allow_renaming", "false",  # prevents "_1" duplicate
                "-x", "0.0",
                "-y", "0.0",
                "-z", "0.32",
                "-Y", "0.0"
            ],
            output='screen'
        )]
    )

    rviz_config_file = os.path.join(pkg_ros_gz_rbot, 'config', 'display.rviz') #Añadido

    rviz_node=Node( #Añadido
	    package='rviz2',
	    executable='rviz2',
	    name='rviz2',
	    output='screen',
        arguments=['-d', rviz_config_file]
    )

    ros_gz_bridge = Node(
        package='ros_gz_bridge',
        executable='parameter_bridge',
        parameters=[{'config_file': ros_gz_bridge_config}],
        output='screen'
    )

    joint_state_broadcaster_spawner = Node( #Añadido
        package='controller_manager',
        executable='spawner',
        arguments=[
            'joint_state_broadcaster',
            '--param-file',
            os.path.join(
                pkg_ros_gz_rbot,
                'config',
                'ros2_controller.yaml'
            )
        ],
        output='screen'
    )

    velocity_controller_spawner = Node( #Añadido
        package='controller_manager',
        executable='spawner',
        arguments=[
            'velocity_controller',
            '--param-file',
            os.path.join(
                pkg_ros_gz_rbot,
                'config',
                'ros2_controller.yaml'
            )
        ],
        output='screen'
    )

    return LaunchDescription([
        gazebo,
        spawn_robot,
        ros_gz_bridge,
        robot_state_publisher,
        joint_state_broadcaster_spawner, #Añadido
        velocity_controller_spawner,     #Añadido
	    rviz_node,                       #Añadido
    ])
```

---
## Desarrollo ([[Configuración de display.launch.py|display.launch.py]])
# Referencias
