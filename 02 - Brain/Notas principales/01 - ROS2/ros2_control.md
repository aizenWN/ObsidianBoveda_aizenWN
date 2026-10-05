---
aliases:
tags:
  - ROS
  - En_curso
Creado: 2026-10-04
Relacionado:
  - Framework
  - "[[Capa 3 (.ros2control)]]"
  - Robotica
  - Movimiento
  - Motor
  - Sensores
---
# Introducción
Es el **[[Framework|framework]]** (el código o programa de fondo). Es la arquitectura de [[ROS]] 2 que se encarga de conectar en tiempo real la lógica de software con los [[Motor Electrico|motores]] y sensores fisicos (o simulados) del robot.

---
# Desarrollo
Es una buena idea revisar que paquetes tenemos instalador y la version de gz sim para asegurar que usamos los plugins correctos:
```bash
ros2 pkg list | grep -E 'ros_gz|gz_ros2|gazebo|ros2_control|diff_drive'
```

```bash
gz sim --version
```

Asi podriamos ver si tenemos algo equivalente a `gz_ros2_control`en la lista.
##  Plugin DiffDrive
El camino más facil para generar movimiento sin utilizar directactamente `ros2_control`es mediante un plugin para [[Gazebo]], el cual se escribe de la siguiente manera para: https://gazebosim.org/api/sim/8/classgz_1_1sim_1_1systems_1_1DiffDrive.html?utm_source=chatgpt.com

>Gazebo Sim, version 8.11.0
Copyright (C) 2018 Open Source Robotics Foundation.
Released under the Apache 2.0 License.

```xml
<gazebo>
	<plugin
		filename="gz-sim8-diff-drive-system"
		name="gz::sim::systems::DiffDrive">
		
		<!-- Ruedas del lado izquierdo -->
		<left_joint>front_left_wheel_joint</left_joint>
		<left_joint>back_left_wheel_joint</left_joint>
		
		<!-- Ruedas del lado derecho -->
		<right_joint>front_right_wheel_joint</right_joint>
		<right_joint>back_right_wheel_joint</right_joint>
		
		<!-- Geometría del rover -->
		<wheel_separation>0.34</wheel_separation>
		<wheel_radius>0.06</wheel_radius>
		
		<!-- Comunicación -->
		<topic>cmd_vel</topic>
		<odom_topic>odom</odom_topic>
		
		<!-- TF de odometría -->
		<frame_id>odom</frame_id>
		<child_frame_id>base_footprint</child_frame_id>
		
		<!-- Frecuencia de odometría -->
		<odom_publish_frequency>50</odom_publish_frequency>
	</plugin>
</gazebo>
```
Solo que, recordemos que el plugin de gazebo no recibe directamente un mensaje ROS 2, por ello tenemos que utilizar un bridge de ROS2 a Gz para los mensajes que le enviaremos de `/cmd_vel`.

Podriamos pensar que el [[Capa 7 (Lógica)|topico]] `/cmd_vel`solo existe para ROS 2 justo en este momento antes del bridge, necesitamos traducirlo a Gz Sim para que este también contenga `gz topic -e -t /cmd_vel`.

En bridge:
```yaml
- ros_topic_name: "/cmd_vel"
  gz_topic_name: "/cmd_vel"
  ros_type_name: "geometry_msgs/msg/Twist"
  gz_type_name: "gz.msgs.Twist"
  direction: ROS_TO_GZ
```

## Diferencia con ros2_controllers.yaml ([[Capa 4 (ros2_controller.yaml)|Capa 4]])
`ros2_controllers.yaml`o a veces llamado simplemente `controllers.yaml.

Es el **archivo de configuracion**, un documento de texto plano donde tu le especificas a `ros2_control`que controladores vas a activar y que parametros vas a usar.

Entonces, se podria decir que sirve para "darle ordenes" al componente principal de `ros2_control`llamado **Control Manager**. En el archivo indica cosas como:

1. Que controladores cargar (`diff_drive_controller, joint_state_broadcaster`).
2. La frecuencia del bucle (50 o 100Hz).
3. Configuraciones especificas del robot (Mapeo de articulaciones `joint`de [[Configuración de urdf - xacro ROS 2|urdf]]).

---
# Referencias
