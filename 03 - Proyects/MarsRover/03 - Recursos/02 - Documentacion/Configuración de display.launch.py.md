---
aliases:
  - display.launch.py
tags:
  - ROS
  - MarsRover
  - En_curso
Creado: 2026-09-01
Relacionado:
  - Programacion
  - "[[Python]]"
  - "[[Capa 5 (launch)]]"
  - Rviz
---
# Introducción
En está nota profundizaremos sobre todo lo relacionado a los archivos tipo launch.py, más en especifico de nuestro display.launch.py.

Este es el launch encargado de cargar todo el entorno en [[RViz]], así que si queremos visualizar algo en este, display.launch.py debe ser modificado y actualizado.

---
# Desarrollo
`display.launch.py` **se relaciona directamente con nuestro [[Configuración de urdf - xacro ROS 2|URDF]].

Entre una de sus múltiples tareas, es el encargado de leer el archivo `rover.urdf.xacrp`, procesarlo y abrir las ventanas de RViz2 para ver el robot en 3D.

**De donde sale este archivo?**
No se crea automáticamente. Lo creamos nosotros desde cero dentro de una carpeta llamada `/launch`

## Análisis detallado
Un archivo de launch en [[ROS]] 2 es un script de Python cuya única función es **lanzar múltiples [[Capa 7 (Lógica)|nodos]] y programas al mismo tiempo con un solo comando**.

Para visualizar tu robot en RViz2, el launch abre 3 **nodos esenciales de ROS 2**:

- `robot_state_publisher` (Procesa el URDF/Xacro --> publica TFs)
- `joint_state_publisher_gui` (Crea barritas para mover ruedas)
- `rviz2` (Abre la ventana 3D)

### Estructura de un archivo
```
import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node
import xacro

def generate_launch_description():

    # 1. Obtener la ruta del archivo Xacro dentro del paquete
    pkg_path = get_package_share_directory('rover_description')
    xacro_file = os.path.join(pkg_path, 'urdf', 'rover.urdf.xacro')

    # 2. Procesar el archivo Xacro para convertirlo a URDF puro (texto XML)
    robot_description_config = xacro.process_file(xacro_file).toxml()

    # 3. Nodo: robot_state_publisher (Publica la estructura 3D en ROS 2)
    node_robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        output='screen',
        parameters=[{'robot_description': robot_description_config}]
    )

    # 4. Nodo: joint_state_publisher_gui (GUI para mover las ruedas con sliders)
    node_joint_state_publisher_gui = Node(
        package='joint_state_publisher_gui',
        executable='joint_state_publisher_gui',
        output='screen'
    )

    # 5. Nodo: RViz2 (Visualizador 3D)
    node_rviz = Node(
        package='rviz2',
        executable='rviz2',
        output='screen'
    )

    # 6. Devolver la lista de nodos a ejecutar
    return LaunchDescription([
        node_robot_state_publisher,
        node_joint_state_publisher_gui,
        node_rviz
    ])
```
**Desglose de las 3 partes clave**:
1. **La conversión de Xacro (`xacro.process_file`):** Toma tu `rover.urdf.xacro`, resuelve las variables o macros que tenga y genera el XML limpio que entiende ROS 2.
2. **`robot_state_publisher`:** Es el nodo oficial de ROS 2 que lee el URDF y transmite las coordenadas ($X,Y,Z$) de cada link (`base_link`, `wheel_front_left`, etc.) a todo el sistema.
3. **`joint_state_publisher_gui`:** Lee los joints de tipo `continuous` o `revolute` de tu URDF y abre una ventana pequeña con barras deslizantes para que puedas girar manualmente las ruedas del rover.

### ¿Por qué necesitamos `setup.py` inmediatamente después?

Cuando ejecutas `colcon build`, ROS 2 no lee los archivos directamente de tu carpeta de desarrollo (`src/`). Copia los archivos a una carpeta del sistema llamada `install/`.

Si no le indicas en `setup.py` que debe copiar la carpeta `launch/` y la carpeta `urdf/`, al ejecutar `ros2 launch rover_description display.launch.py` **ROS 2 dirá que no encuentra el archivo**.



---
# Referencias
