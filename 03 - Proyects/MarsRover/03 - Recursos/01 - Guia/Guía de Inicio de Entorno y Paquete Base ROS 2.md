---
aliases:
  - Guía de Instalación ROS 2
  - Instalación ROS 2
  - Paquete ROS 2
tags:
  - ROS
  - Completado
Creado: 2026-08-22
Relacionado:
  - Simulacion
  - ROS2
  - "[[ROS]]"
  - Rviz
  - Gazebo
---
# Introducción
En está nota encontraremos como instalar ROS 2, algunos de sus paquetes necesarios, así como la creación de nuestro WorkSpace y un paquete de lanzamiento urdf y launch.

---
# Desarrollo

### Configurar Teclas y Repositorios de ROS 2 Jazzy

Asegura el soporte UTF-8, instala las llaves oficiales de ROS 2 y añade el repositorio a Ubuntu 24.04:

```
# Asegurar Locale

sudo apt update && sudo apt install -y software-properties-common curl gnupg lsb-release

sudo locale-gen en_US en_US.UTF-8

sudo update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
export LANG=en_US.UTF-8

# Añadir la llave GPG oficial de ROS 2

sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg

# Agregar el repositorio a las fuentes de APT

echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null
```

### Instalación de Paquetes Base y Herramientas
Instalación de ROS 2 Jazzy Desktop, dependencias de compilación y el paquete gráfico para las articulaciones:

```
# 1. Actualizar el índice de paquetes locales
sudo apt update

# 2. Herramientas base de ROS 2 Jazzy y GUI para articulaciones

sudo apt install -y ros-jazzy-desktop ros-dev-tools python3-colcon-common-extensions

sudo apt install -y ros-jazzy-joint-state-publisher-gui

# 3. Simulador Gazebo Harmonic (Integración con ROS 2)
sudo apt install -y ros-jazzy-ros-gz

# 4. Navegación (Nav2) y Mapeo (SLAM Toolbox)
sudo apt install -y ros-jazzy-navigation2 ros-jazzy-nav2-bringup ros-jazzy-slam-toolbox
```

### Probar / Validar Instalaciones
Mediante los siguientes comandos, probaremos que las instalaciones correspondientes son correctas:

1. Probar RViz2 (Visualizador 3D)
```
source /opt/ros/jazzy/setup.bash
rviz2
```

2. Probar [[Gazebo]] Harmonic (Motor de Física y [[Capa 2 (Simulación)|Simulación]])
```
source /opt/ros/jazzy/setup.bash
gz sim
```

3. Probar el Administrador de Articulaciones (`joint-state-publisher-gui`)
```
source /opt/ros/jazzy/setup.bash
ros2 run joint_state_publisher_gui joint_state_publisher_gui
```

4. Probar Nav2 y SLAM (Sistemas de Navegación y Mapeo)
```
source /opt/ros/jazzy/setup.bash

# Verificar que los comandos de lanzamiento de Nav2 existen
ros2 launch nav2_bringup navigation_launch.py --help

# Verificar que el nodo de SLAM Toolbox responde
ros2 pkg prefix slam_toolbox
```
Si los comandos en la terminal te imprimen opciones de configuración de Nav2 sin marcar error, ya estará bien instalado

### Creación de Workspace
Configuramos el espacio de trabajo en la carpeta donde queramos trabajar los archivos:

```
# Crear la estructura de carpetas

	mkdir -p /ruta_preferida/ros2_ws/src
	cd /ruta_preferida/ros2_ws/src

# Cargar el entorno de ROS 2

	source /opt/ros/jazzy/setup.bash

a
```

## Crear estructura de un paquete robótico rover_description
Creación de los subdirectorios para los archivos Xacro y [[Capa 5 (launch)|Launch]]:
```
# Creamos el paquete minimo de descripción en Python 
(Este último comando lo ejecutamos en el directorio de nuestra terminal src/, genera automaticamente la plantilla basica con su package.xml, su setup.py y la estructura de carpetas minima para trabajar inmediatamente en un robot)

	ros2 pkg create --build-type ament_python rover_description --dependencies rclpy
```

Creamos nuestras carpetas para almacenar nuestros archivos .xacro y .launch:
```
cd /ruta_preferida/ros2_ws/src/rover_description
mkdir -p urdf launch
```

Dentro de la carpeta rover_description/ debería quedar una estructura interna parecida a esto:
```
rover_description/
├── launch/
│   └── display.launch.py
├── urdf/
│   └── rover.urdf.xacro
├── package.xml
└── setup.py
```

### Configuración de rover.urdf.xacro
Define la geometría 3D del chasis, ruedas, marcadores visuales y articulaciones (`joints`) del vehículo respetando la convención de ejes de ROS 2
(**REP 103**: $X$=Rojo/Frente, $Y$=Verde/Izquierda, $Z$=Azul/Arriba).

```
<?xml version="1.0"?>
<robot xmlns:xacro="http://www.ros.org/wiki/xacro" name="rover">

  <!-- MATERIALES -->
  <material name="blue">
    <color rgba="0.0 0.0 0.8 1.0"/>
  </material>
  <material name="black">
    <color rgba="0.0 0.0 0.0 1.0"/>
  </material>
  <material name="red">
    <color rgba="1.0 0.0 0.0 1.0"/>
  </material>

  <!-- BASE FOOTPRINT (Proyección en el suelo) -->
  <link name="base_footprint"/>

  <!-- JOINT BASE FOOTPRINT -> BASE LINK -->
  <joint name="base_footprint_joint" type="fixed">
    <parent link="base_footprint"/>
    <child link="base_link"/>
    <origin xyz="0 0 0.15" rpy="0 0 0"/>
  </joint>

  <!-- BASE LINK (Chasis Principal) -->
  <link name="base_link">
    <visual>
      <geometry>
        <box size="0.5 0.3 0.15"/>
      </geometry>
      <material name="blue"/>
    </visual>
  </link>

  <!-- MARCADOR FRONTAL (Indicador visual de dirección +X) -->
  <joint name="front_marker_joint" type="fixed">
    <parent link="base_link"/>
    <child link="front_marker_link"/>
    <origin xyz="0.2 0 0.09" rpy="0 0 0"/>
  </joint>

  <link name="front_marker_link">
    <visual>
      <geometry>
        <box size="0.08 0.08 0.03"/>
      </geometry>
      <material name="red"/>
    </visual>
  </link>

  <!-- RUEDA TRASERA IZQUIERDA -->
  <joint name="wheel_rear_left_joint" type="continuous">
    <parent link="base_link"/>
    <child link="wheel_rear_left_link"/>
    <origin xyz="-0.15 0.18 -0.05" rpy="-1.5708 0 0"/>
    <axis xyz="0 0 1"/>
  </joint>

  <link name="wheel_rear_left_link">
    <visual>
      <geometry>
        <cylinder radius="0.1" length="0.05"/>
      </geometry>
      <material name="black"/>
    </visual>
  </link>

  <!-- RUEDA TRASERA DERECHA -->
  <joint name="wheel_rear_right_joint" type="continuous">
    <parent link="base_link"/>
    <child link="wheel_rear_right_link"/>
    <origin xyz="-0.15 -0.18 -0.05" rpy="-1.5708 0 0"/>
    <axis xyz="0 0 1"/>
  </joint>

  <link name="wheel_rear_right_link">
    <visual>
      <geometry>
        <cylinder radius="0.1" length="0.05"/>
      </geometry>
      <material name="black"/>
    </visual>
  </link>

  <!-- RUEDA DELANTERA IZQUIERDA -->
  <joint name="wheel_front_left_joint" type="continuous">
    <parent link="base_link"/>
    <child link="wheel_front_left_link"/>
    <origin xyz="0.15 0.18 -0.05" rpy="-1.5708 0 0"/>
    <axis xyz="0 0 1"/>
  </joint>

  <link name="wheel_front_left_link">
    <visual>
      <geometry>
        <cylinder radius="0.1" length="0.05"/>
      </geometry>
      <material name="black"/>
    </visual>
  </link>

  <!-- RUEDA DELANTERA DERECHA -->
  <joint name="wheel_front_right_joint" type="continuous">
    <parent link="base_link"/>
    <child link="wheel_front_right_link"/>
    <origin xyz="0.15 -0.18 -0.05" rpy="-1.5708 0 0"/>
    <axis xyz="0 0 1"/>
  </joint>

  <link name="wheel_front_right_link">
    <visual>
      <geometry>
        <cylinder radius="0.1" length="0.05"/>
      </geometry>
      <material name="black"/>
    </visual>
  </link>

</robot>
```

Para más detalles visitar la siguiente nota: [[Configuración de urdf - xacro ROS 2]]
### Configuración de [[Configuración de display.launch.py|display.launch.py]]
Script de automatización de inicio en Python. Parsea el archivo Xacro, arranca `robot_state_publisher`, lanza la GUI de control de articulaciones y abre la interfaz 3D de RViz2 en un solo comando:

```
import os
import xacro
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    pkg_name = 'rover_description'
    
    # Obtener la ruta del archivo Xacro procesado en install/
    xacro_file = os.path.join(
        get_package_share_directory(pkg_name),
        'urdf',
        'rover.urdf.xacro'
    )
    
    # Procesar Xacro a formato XML nativo de URDF
    robot_description_raw = xacro.process_file(xacro_file).toxml()

    # [[Capa 7 (Lógica)|Nodo]] 1: Robot State Publisher
    node_robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        output='screen',
        parameters=[{'robot_description': robot_description_raw}]
    )

    # Nodo 2: Joint State Publisher GUI
    node_joint_state_publisher_gui = Node(
        package='joint_state_publisher_gui',
        executable='joint_state_publisher_gui',
        output='screen'
    )

    # Nodo 3: RViz2
    node_[[RViz|rviz]] = Node(
        package='rviz2',
        executable='rviz2',
        output='screen'
    )

    return LaunchDescription([
        node_robot_state_publisher,
        node_joint_state_publisher_gui,
        node_rviz
    ])
```

Para más detalles visitar la siguiente nota: [[Configuración de display.launch.py]]
### Configuración de setup.py
Inclusión de los directorios `launch` y `urdf` para que `colcon build` los exponga en el entorno de instalación:

Código:
```
import os
from glob import glob
from setuptools import find_packages, setup

package_name = 'rover_description'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages', ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'launch'), glob('launch/*.launch.py')),
        (os.path.join('share', package_name, 'urdf'), glob('urdf/*.xacro')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='aizen',
    maintainer_email='aizen@todo.todo',
    description='Rover description package',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [],
    },
)
```

Para más detalles visitar la siguiente nota: [[Configuración de setup.py]]
## Compilación y Ejecución
Compilación del workspace y lanzamiento del entorno gráfico:

```
# Ir a la raíz del workspace
cd /ruta_preferida/ros2_ws

# Compilar el paquete seleccionado
colcon build --packages-select rover_description

(Puedes no escribir --packages-select y compilara todos los paquetes dentro de nuestra ruta)
(La primera vez que compilamos, se crearan automaticamente tres carpetas build, install, log)

# Cargar las variables del workspace compilado
source install/setup.bash

# Lanzar la visualización en RViz2
ros2 launch rover_description display.launch.py
```

### Otros comandos útiles de inicio
Volver a abrir la ventana de `joint_state_publisher_gui

```
source /opt/ros/jazzy/setup.bash
ros2 run joint_state_publisher_gui joint_state_publisher_gui
```

---
# Referencias
