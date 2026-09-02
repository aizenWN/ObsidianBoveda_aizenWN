---
aliases:
  - Capa 4
  - ros2_controller.yaml
tags:
  - ROS
  - Incompleto
Creado: 2026-06-18
Relacionado:
  - Programacion
  - Simulacion
  - Sistemas Embebidos
  - Ubuntu
  - Rviz
  - Robot
  - Robotica
  - Controlador
  - Embebidos
  - Linux
  - Gazebo
  - Microcontroladores
  - "[[Capa 3 (.ros2control)]]"
---
# [[Estructura de trabajo (ROS)|Capa]] 4
## Introducción
Hasta ahora [[ROS]] sabe que existen joint, que existe un modelado 3D y sus parámetros y tal vez las configuraciones del mundo ([[Capa 2 (Simulación)]] en [[Gazebo]])

Pero no sabe quien le va a enviar ordenes, como se enviaran, que [[Capa 7 (Lógica)|tópico]] usar, que controlador utilizar.

Aquí es donde entra ``controll_manager``.

**Nota:** .yaml es un archivo de texto, especialmente utilizados para configuraciones, no se considera un lenguaje de programación.

---
## controll_manager
Este es un **Nodo de ROS ya existente**

Viene con ros2_control, nosotros no lo programamos.

El trabajo de este Nodo es leer .yaml, cargar las instancias, cargar los controladores, activarlos.

**El archivo .yaml no crea Nodos**
``velocity_controller`` no es un nodo, es una instancia del controlador 

Visualmente seria:
```
controller_manager (NODO)
	velocity_controller     (INSTANCIA)
	joint_state_broadcaster (INSTANCIA)
```

---
## Análisis (control_manager)
En un archivo .yaml podemos tener está parte del código:
```
controller_manager:
  ros__parameters:

    update_rate: 100

    joint_state_broadcaster:
      type: joint_state_broadcaster/JointStateBroadcaster

    velocity_controller:
      type: velocity_controllers/JointGroupVelocityController
```
Como bien sabemos, ``control_manager`` es un nodo, debajo de el podemos observar ``ros__parameters`` (palabra reservada), aquí estamos indicando que le estamos pasando parámetros a nuestro nodo, después viene.

``update_rate: 100`` 

Significan 100Hz, es decir, cada 10ms el controlador se actualiza, 

Ahora observemos las instancias:
### Instancias
Recordemos que las instancias pueden ser llamadas como queramos, en base a este, el controlador creara un tópico, basándose en el nombre que nosotros hemos elegido para nuestra instancia.

**Primera instancia** ``joint_state_broadcaster:``

Aquí estamos declarando una instancia, que sera del tipo ``joint_state_broadcaster/JointStateBroadcaster,`` es decir, le estamos cargando el controlador ``JointStateBroadcaster`` nativo de ROS a nuestra instancia.

Tambien lo podemos ver como si fuera POO en C++, el controlador sería el equivalente a nuestra class, nuestra instancia creada a partir de nuestra class es llamada ``joint_state_broadcaster`` (equivalente a un objeto).

**¿Que hace?**
Lee ``postion, velocity, effort`` y publica ``/joint_states``, no controla nada, solo informa.

**Segunda instancia** ``velocity_controller:``

Del tipo ``JointGroupVelocityController`` 

```
Visualmente es:

Instancia:
    velocity_controller

Tipo:
    JointGroupVelocityController
    
O

Clase:
    JointGroupVelocityController

Objeto:
    velocity_controller
```

---
## Configuración de la Instancia
Ahora vamos a hacer la configuración especifica del "objeto".

Nos dice: ¿Como quiere configurar el controlador?

Recordamos ``ros__parameters`` para configurar los parametros de nuestra instancia. a la cual le enviamos nuestros joints:
```
joints:
  - joint1
  - joint2
  - joint3
  - joint4
```
Le estamos diciendo a nuestra instancia que controle esos joints, así cuando creemos nuestro nodo (el cual sera el que envié la información para la acción que queremos realizar), podríamos mandar algo como ``[2.0, -2.0, 2.0, -2.0]``, le mandas la información de movimiento a cada uno de los joint.

---

**interface_name: velocity**

Aquí estas diciendo, usa la interfaz velocity
Es donde se conecta con la **Capa 3**, ya que en ros2_control escribimos, ``<command_interface name="velocity"/>``.

Si escribiéramos ``<command_interface name="position"/>``, entonces necesitaríamos otro controlador, uno que no sea de velocidad.

---
## Código Completo
```
controller_manager:
  ros__parameters:

    update_rate: 100

    joint_state_broadcaster:
      type: joint_state_broadcaster/JointStateBroadcaster

    velocity_controller:
      type: velocity_controllers/JointGroupVelocityController

velocity_controller:
  ros__parameters:

    joints:
      - joint1
      - joint2
      - joint3
      - joint4

    interface_name: velocity
```

---
## Extra
Entonces aquí es donde declaramos las instancias:
```
velocity_controller --------------------------------------------> (Velocidad)
position_controller --------------------------------------------> (Posición)
joint_trajectory_controller ------------------------------------> (Trajectoria)
pid_controller -------------------------------------------------> (PID)
diff_drive_controller ------------------------------------------> (Robot diferencial)
```


# Referencias
