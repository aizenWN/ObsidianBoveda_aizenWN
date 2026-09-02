---
aliases:
  - crear paquete de control ROS
tags:
  - ROS
  - En_curso
Creado: 2026-06-24
Relacionado:
  - "[[C++]]"
  - "[[Python]]"
  - Gazebo
  - Rviz
  - ROS2
  - Robotica
  - Programacion
  - Robot
  - Simulacion
---
## Pasos para Crear un [[Capa 7 (Lógica)|Nodo]]
Primero debemos decirle a [[ROS|ROS2]] que nos cree la estructura base para un paquete de C++ llamado ``carrito_prueba_control`` (Cambiar a nombre de proyecto real dejando "_control").

Vamos a abrir una nueva terminal Ubuntu 24.04

Una vez abierta, nos movemos a ``cd ros2_ws/src``

Después, ejecutaremos el siguiente código:
**(ojo, en el código dice "carrito_prueba", cambiar al nombre del proyecto real y dejar la ultima parte _control)**
``ros2 pkg create carrito_prueba_control --build-type ament_cmake --dependencies rclcpp std_msgs``

Entonces se creara el paquete de lógica dentro de nuestros /src, lo que nos debería quedar es:
```
Ejemplo con modelado de carrito

/ros2_ws/src
	carrito_prueba_description  (Paquete de Capa 1 a 6)
	carrito_prueba_control      (Paquete de Lógica [Capa 7])
```
Dentro de este paquete que acabamos de encontrar, nos deberíamos encontrar con los siguientes archivos:
```
/src/carrito_prueba_control
	|_include
	|	 |_ carrito_prueba_control
	|
	|_src
	|	 |_ Vacio (de momento, aquí iran nuestros nodos de lógica)
	|
	|_templates (carpeta creada para Nodos de prueba)
	|	 |_ Vacio
	|
	|_CMakeLists.txt
	|
	|_package.xml
```
Con está estructura estamos completamente listos para comenzar a escribir nuestros códigos (Nodos) dentro de nuestra carpeta ``/carrito_prueba_control/src``, aunque antes de ello, primero debemos de configurar nuestro IDE, en este caso Visual Studio Code, para poder trabajar cómodamente con ROS, lo veremos en el siguiente archivo: [[Configurar VSC]]

---

**Nota de recomendación:** Primero hacer el "Ejemplo práctico con carrito_prueba_control" el cual viene en el Capitulo 4 en la *[[Guía ROS2.pdf]]*, la guía inicial que he creado en formato látex. 

---

Una vez configurado, podemos adentrarnos en como escribir código para nuestros nodos, este es un campo bastante complejo, así que necesitamos centrarnos solo en ello, he preparado una plantilla base, la cual siempre se utilizara en prácticamente todos los Nodos en los que estemos trabajando, sumamente comentada en la que se explica paso a paso que hace cada línea de código, así, después de entender este apartado, trabajar en nuestro primero Nodo: [[Mi primer Nodo]].

Al final no olvidemos siempre compilar está carpeta con ``colcon build --packages-select carrito_prueba_control``
o simplemente ``colcon build`` para compilar todos los paquetes con su correspondiente ``source install/setup.bash`` antes de ejecutar cualquier [[Capa 5 (launch)|Launch]].











# Referencias
