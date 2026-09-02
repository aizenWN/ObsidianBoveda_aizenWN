---
aliases:
  - Capa 3
  - .ros2control
  - ros2control
tags:
  - ROS
  - Incompleto
Creado: 2026-06-18
Relacionado:
  - Programacion
  - Robotica
  - Simulacion
  - Sistemas Embebidos
  - Embebidos
  - Linux
  - Ubuntu
  - Gazebo
  - Rviz
  - Robot
  - Microcontroladores
  - "[[Capa 4 (ros2_controller.yaml)]]"
---
# [[Estructura de trabajo (ROS)|Capa]] 3
## Introducción
Este archivo pertenece a la Capa 3 de [[ROS]]
¿Que parte del robot puede recibir ordenes?

De manera base solamente tenemos 
```
<?xml version="1.0"?>
	<robot xmlns:xacro="http://www.ros.org/wiki/xacro">

</robot>
```
---
## ros2_control
Nosotros tenemos que definir que queremos que reciba ordenes, en el caso del pendulo_prueba, queremos que reciba ordenes el pendulo como tal, ya que es lo unico en lo que queremos movimiento.

Asi que agregamos:
``<ros2_control name="GazeboSystem" type="system">``

De esta manera le decimos a ROS
**(Este robot tiene partes controlables)**

---
## hardware
Debajo de este bloque abrimos uno nuevo:
```
<hardware>
  <plugin>gz_ros2_control/GazeboSimSystem</plugin>
</hardware>
```
De esta manera le estamos diciendo a ROS
**(No es hardware realm usa [[Capa 2 (Simulación)|Gazebo]] como hardware)**

En un futuro se podrían añadir cosas como:
``<plugin>MiESP32Driver</plugin>``
``<plugin>DynamixelHardware</plugin>``
``<plugin>RealRobotHardware</plugin>``
Si es que estuviéramos mandando ordenes desde un hardware real

---
## Contenido 
Una vez que le indicamos a ROS que es lo que vamos a hacer queremos que haga, vamos a indicarle en que partes del robot hacerlo.

Cuando escribimos ``<joint name="joint1">``
Le estamos diciendo que ROS conozca el siguiente joint

Si no aparece en ``<ros2_control>`` entonces ROS no lo reconoce
Ahora solo falta mencionar que tipo de ordenes va a recibir ese joint

---
## command_interface

``<command_interface name="velocity"/>``
**Este joint acepta ordenes de velocidad**

Puede recibir +2 rad/s
-1 rad/s
0 rad/s

Pero no puede recibir ``posicion``

Entonces ``command_interface`` son los comandos o instrucciones de control que los controladores de ROS calculan y envían hacia los joint

Entonces entendemos el concepto, así que podríamos escribir las siguientes características para un joint:

``<command_interface name="position"/>`` (45° grados)
``<command_interface name="effort"/>`` (2 Nm = Newtown metro)

---

## state_Interface
Tenemos ``<state_interface name="position"/>``
No es una orden, es información que ROS puede leer, interprétalo como los valores leídos por los sensores, como encorders, feedback

Es la respuesta que el robot envía de vuelta, la lectura real, de lo que ocurrió y  devuelve el resultado.

---
## Conclusión 
Entonces, desde la terminal y mediante ros, enviamos comandos por medio de nuestros [[Capa 7 (Lógica)|nodos]], estos le llegan a los controladores que va a command_interface, y revisa, que joint puede recibir esta información que nos enviaron, en este caso, velocidad, ejemplo joint1, okey este puede recibir velocidad, después el controlador escribe la orden (objetivo) en ``command_interface``, esta es solo una variable, aquí es donde el hardware físico o el plugin de simulación toman ese valor, se ejecuta la acción, después ``state_interface`` solo guarda esa nueva posición y velocidad , no hace cálculos matemáticos, simplemente va almacenando el valor de los resultados

Esto
```
<joint name="joint1">

  <command_interface name="velocity"/>

  <state_interface name="position"/>

  <state_interface name="velocity"/>

</joint>
```
Es igual a esto:
```
joint1

Puede recibir:
    velocidad

Puede reportar:
    posición
    velocidad
```
**Aquí todavía no estamos manejando ningún controlador de ROS*

**Recuerda cerrar todo el bloque con ``</robot>``

---
## Código Completo
**Ejemplo de como se vería un código ros2control estructurado**  

```
<?xml version="1.0"?>

<robot xmlns:xacro="http://www.ros.org/wiki/xacro">

  <ros2_control name="GazeboSystem" type="system">

    <hardware>
      <plugin>gz_ros2_control/GazeboSimSystem</plugin>
    </hardware>

    <joint name="joint1">
      <command_interface name="velocity"/>
      <state_interface name="position"/>
      <state_interface name="velocity"/>
    </joint>

    <joint name="joint2">
      <command_interface name="velocity"/>
      <state_interface name="position"/>
      <state_interface name="velocity"/>
    </joint>

    <joint name="joint3">
      <command_interface name="velocity"/>
      <state_interface name="position"/>
      <state_interface name="velocity"/>
    </joint>

    <joint name="joint4">
      <command_interface name="velocity"/>
      <state_interface name="position"/>
      <state_interface name="velocity"/>
    </joint>

  </ros2_control>
  
</robot>
```

# Referencias

