---
aliases:
  - mi primer nodo
  - Mi primer NODO
  - Mi primer nodo
tags:
  - ROS
  - En_curso
Creado: 2026-06-25
Relacionado:
  - "[[Crear un Paquete de Control (Lógica) ROS]]"
---
## Introducción
Para está sección, nos apoyaremos de dos plantillas ya hechas, en cuanto a código, tienen prácticamente lo mismo, en lo que se diferencia una de la otra es que, la llamada ``plantilla comentada``, está sumamente explicada, cada línea de código está comentada, explicando su funcionamiento, y si ello es parte del [[C++|Lenguaje C++]], o si de forma contraria, se está utilizando el [[Framework]] de [[ROS]].

Las plantillas las podrán encontrar en el siguiente enlace de **GitHub:** 
``https://github.com/aizenWN/Plantillas_nodos_para_ROS``

Nos centraremos en la ``plantilla comentada`` para está nota de aprendizaje.

---
## Desarrollo
Tambien utilizaremos los siguientes medios para poner en practica lo aprendido, en está ocasión, se utilizara el archivo exportado ``carrito_prueba_description`` + ``carrito_prueba_control``.

Iremos al siguiente enlace y descargaremos su contenido: ``https://github.com/aizenWN/Nodos-ROS``

En el, podremos observar [[Capa 7 (Lógica)|Nodos]], los cuales ya son de nuestra propiedad, así que finalmente, tenemos nodos hechos por nosotros, de está manera estudiar su comportamiento, de aquí en adelante, gran parte del trabajo se deriva en estar trabajando en nuestra Logica.

---
## CMakeLists.txt
Este documento es una parte vital del Flujo de trabajo para nuestros nodos, sin el, no podemos utilizarlos.

Abriremos nuestro archivo ``CMakeLists.txt``, una vez abierto, veremos algo parecido a esto:
```
cmake_minimum_required(VERSION 3.8)
project(carrito_prueba_control)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()



# Instalamos el ejecutable para que el comando 'ros2 run' lo localice
install(TARGETS
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
```
En este archivo tenemos que añadir manualmente los Nodos que hemos creados, ya que solamente creamos la lógica, pero oficialmente no está vinculada con todo el proyecto en ROS, por cada nodo nuevo tenemos que agregar tres líneas de código a este documento, estas tienen que ser colocadas preferentemente después de el bloque ``if(BUILD_TESTING) ... endif()``, pogamos de ejemplo que queremos agregar el nodo llamado ``adelante.cpp``, el cual ya descargamos gracias al enlace de **GitHub** vimos anteriormente, las líneas de código son las siguientes:

1. Declaramos el binario ejecutable y su ruta de origen: ``add_executable(adelante_node src/adelante.cpp)``
2. Añadimos las dependencias para que compile con ROS2: ``ament_target_dependencies(adelante_node rclcpp std_msgs)``
3. En el último bloque ""install(TARGETS"", vamos a añadir finalmente el nombre de nuestro nodo:
```
install(TARGETS 
adelante_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
```

Si nos fijamos bien, el nombre elegido para nuestro nodo, en este caso es ``adelante_node``, se debe a que en estas tres líneas de código, lo hemos nombrado así y lo vinculamos al archivo .cpp que contiene nuestra lógica, esto sirve para que cuando mandemos ejecutar nuestro nodo en la terminal, ya que [[Gazebo]] / [[RViz]] se este ejecutando, sea llamado mediante este nombre que acabamos de definir.

---
## Comando para Ejecutar Nodo 
Ya tenemos todo listo, lo único que nos falta por hacer ese ejecutar nuestro nodo, para ellos, tenemos que asegurar que Gazebo / RViz esten completamente abiertos, con el modelos insertado en nuestro mundo y sin ningún tipo de error, una vez confirmamos esto, abriremos una nueva terminal Ubuntu 24.04.

Cada vez que abramos una nueva terminal Ubuntu, necesitamos ejecutar el comando ``source install/setup.bash``, esto dentro de la ruta ``cd ros2_ws/``, este comando le manda decir a ROS, "aquí está mi workspace, búscalo".

Si es que hacemos alguna modificación en nuestros archivos (actualizar nodos, configurar instancias, modificar entorno, etc...), tenemos que compilar el proyecto, recordemos que esto se puede hacer con ``colcon build`` para todos los paquetes dentro de nuestro ``/src``, o elegir un paquete en especifico mediante ``colcon build --packages-select carrito_prueba_control``.

Listo, ya solo mandamos nuestro nodo con el siguiente comando:
``ros2 run nombre_del_paquete nombre_del_nodo_node``
Ejemplo:
``ros2 run carrito_prueba_control adelante_node

**¿Que sigue?**
Simplemente nos queda observar como nuestro modelo simulado comienza a ejecutar nuestro nodo, visualizándolo como movimiento hacia adelante en este caso, ahora, solo queda seguir el mismo proceso para cualquier nodo nuevo que creemos, lo único en lo que trabajamos nosotros es en programar su lógica, utilizando la plantilla dada al inicio de la nota.

## Felicidades
Oficialmente, después de mucho procedimiento y entendimiento, podemos decir que, ahora puedes utilizar el Framework de ROS2, claramente queda mucho trabajo por delante, pero debes estar orgulloso de haber pasado por todo este proceso para lograr entender una de las herramientas de Robótica para Posgrado, utilizada por las Grandes la de la industria Robótica Real.
![[Pasted image 20260625185757.png]]![[Pasted image 20260625185757.png]]![[Pasted image 20260625185757.png]]