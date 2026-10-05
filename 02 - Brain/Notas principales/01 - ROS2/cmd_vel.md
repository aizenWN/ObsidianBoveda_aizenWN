---
aliases:
tags:
  - ROS
  - Topico
  - En_curso
Creado: 2026-10-04
Relacionado:
  - Gazebo
  - MarsRover
  - Robotica
---
# Introducción
En está nota profundizaremos sobre el uso de [[Capa 7 (Lógica)|topico]] denominado como `/cmd_vel`.

---
# Desarrollo
**¿Que es `/cmd_vel`?**
Es un topico estandar en [[ROS]] 2 que se utiliza para enviar ordenes de movimiento en tiempo real a un robot movil.

>**Ordenes de movimiento, no generador de movimiento**

Controla la velocidad con la que debe desplazarse y girar, funciona como un canal de comunicacion donde un nodo emisor (publisher) publica las instrucciones y el controlador del robot o simulador (suscriber) las lee para mover las ruedas.

## Estructura del mensaje
Los datos que viajan a traves de `/cmd_vel` pertenecen comunmente al tipo de interfaz `geometry_msgs/Twist`(o `TwistStamped`). 
Este mensaje se divide en dos vectores tridimiensionales.

- **Velocidad Lineal** (`lineal | traslacional`).
- **Velocidad Angular** (`angular | rotacional`).
```json
{
  "linear": {"x": 0.2, "y": 0.0, "z": 0.0},
  "angular": {"x": 0.0, "y": 0.0, "z": 0.0}
}
```

## Driver de Control
Una vez que tenemos configurado nuestro envio de mensajes de veolcidad mediante `/cmd_vel` necesitaremos un driver de control, el cual sera el encargado real de generar este movimiento.

Podemos elegir 2 caminos:

1. [[Gazebo]] clasico | simple.
Agregar directamente un plugin de diferencia que genere movimiento:
```
/cmd_vel
|
v
plugin
|
v
wheel joints
```

2. [[ros2_control]].
Contruir algo parecido a:
```
/cmd_vel
|
v
diff_drive_controller
|
v
ros2_control
|
v
Gazebo
|
v
joints
```

Una cosa que debemos tener en cuenta es que el **segundo camino** es el más cercano a una **arquitectura que después se pueda llevar a un rover fisico**.

---
# Referencias
