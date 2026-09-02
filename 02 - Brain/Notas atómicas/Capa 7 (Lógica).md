---
aliases:
  - Capa 7
  - Nodos
  - instancias
  - topicos
  - Topicos
  - Tópicos
  - tópicos
  - tópico
  - Tópico
  - topico
  - Topico
  - Nodo
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
  - Controlador
  - Rviz
  - Robotica
  - Robot
  - Programacion
  - Ubuntu
  - Linux
  - Gazebo
  - Simulacion
  - "[[Mi primer Nodo]]"
---
# Capa 7
## Introducción 
Esta es la capa en la que posiblemente se invierta más tiempo, ya que está es la capa **Lógica**, donde toda la matemática, comportamientos y programación harán que nuestro robot haga lo que nosotros ordenemos.

En está capa se encontrara archivos como:
```
(C++ o Python)

\ros2_ws\src\carrito_prueba_control\src
	adelante.cpp
	direcciones_prueba.cpp
	parar.cpp
	pid.cpp
	seguimiento_de_linea.cpp
	
Ejemplo:
	adelante.cpp
		if(distancia < 20) detener;
```
Si nos fijamos bien en la ruta, está vez no nos encontramos en ``\src\carrito_prueba_description``, creamos un nuevo apartado exclusivo para nuestro ``control``, de está manera llevar una mejor organización.

Tambien es importante mencionar que estamos trabajando con **Nodos** en lenguaje **C++**, ya que nuestro objetivo es llevarlo todo a una placa de desarrollo como (ESP32, STM, RaspBerry) mediante [[Micro-ROS]], como bien sabemos, estas placas de desarrollo se manejan mejor mediante lenguaje **C++**, si creáramos nuestros **Nodos** en **Python**, sería más complicado el traslado lógico a nuestros [[Microcontroladores|microcontroladores]].

## Desarrollo
  Para explicar este apartado y entender como es que funciona el manejo de la lógica mediante nuestros **Nodos**, primero comencemos con un ejemplo visual muy básico de como es el flujo de trabajo completo desde nuestra lógica (**Nodo**) hasta que llega la información al simulador, después de esto, estaremos desglosándolo y así explicar cada cosa por partes.

[[usable1.canvas]]
  
Tengamos abierto el diagrama anterior mientras continuamos con las explicaciones y tener un apoyo visual en todo momento.

**Nota:** Algo que se tiene que diferenciar muy bien y tener en cuenta, es que una cosa es el **Flujo de arranque** (archivos, software, comandos) [Ejecución Real (Como se conectan las capas.canvas)], esto pasa cuando ejecutamos el ``launch``, al **Flujo de comunicación** [[usable1.canvas]] que tienen los archivos una vez todo se este ejecutando, puede parecer que unas cosas se crean antes que otras, pero todo depende del punto de vista.

---
### Instancias
Como habíamos mencionado anteriormente, en nuestra [[Capa 4 (ros2_controller.yaml)|Capa 4]] se definen las configuraciones de nuestra instancia, aquí es donde nombramos a la instancia y le cargamos el tipo de controlador que va a utilizar, dependiendo de la funcionalidad que busquemos.

Las instancias pueden ser llamadas como sea de nuestro agrado (aconsejando que sea un nombre referente a la funcionalidad), pero como ya hemos leído anteriormente, el comportamiento de la instancia depende exclusivamente del controlador cargado a esta.

Una forma más fácil de ver las Instancias de una manera muy visual y comparándolo con algo que ya conocemos es de la siguiente forma:
```
Conociendo POO (Programacion Orientada a Objetios C++)

Sabemos que, cuando queremos crear un objeto, primero debemos definir la clase a la que este pertenece, imaginemos que tenemos una "class Luz", después vamos a crear un objeto, para definir de que color va a ser esa Luz, viendolo en forma de código quedaría como:

--------------------------------------------------------------------------------------------------------
class Luz{
	private: // Atributos
	public: //  Contructor
		Luz::Luz(){}
		
		// Metodos
		void Luz::begin(){}
		void Luz::color(){}
		void Luz::encender(){}
}
--------------------------------------------------------------------------------------------------------
Una vez creada la clase, hacemos una instancia de esta, la cual sera nuestro objeto

Luz rojo;
Luz azul;
Luz magenta;

int main(){}
```

```
Lo que más nos importa es lo último de lo anterior para compararlo con ROS, de está manera se pueda entender más facilmente:

Declaramos un Objeto en C++
Luz rojo;

Esta misma declaracion se puede leer en ROS como:
JointGroupVelocityController velocity_control

Viendo las comparaciones seria:
Luz == class == Controlador == JointGroupVelocityController
rojo == object == Instancia == velocity_control
```
Observando la lista de controladores que está a continuación, nos damos cuenta de mejor manera que no siempre existe /commands al final de un tópico, todo depende de cual estemos utilizando.

**Regla práctica**
Cuando agreguemos un controlador nuevo y tengamos dudas, podemos preguntarle directamente a [[ROS]] con el siguiente comando:

``ros2 control list_controllers
después
``ros2 topic list``

Si queremos aprender más sobre controladores, es bueno enfocarse en:
```
JointStateBroadcaster
JointGroupVelocityController
JointGroupPositionController
DiffDriveController

Con estos se puede entender el 80% de los robots movilers y simulaciones básicas 
```

#### Controladores
Los controladores que estaremos utilizando son derecho de ROS y vienen por defecto con este, nosotros no los creamos.
Existen diferentes tipos de controladores que pueden ser cargados a nuestras instancias, a continuación, exploraremos una lista de los diferentes controladores que podemos utilizar y una breve explicación de su funcionamiento:
```
JointGroupVelocityController
	Se encarga de publicar estados /joint_states
		
		Ejemplo:
			joint1 = 2 rad/s
			joint2 = -2 rad/s
			joint3 = 2 rad/s
			joint4 = -2 rad/s
	
		Tópico
			/nombre_instancia/commands
```

```
JointGroupPositionController
	Sirve para mover joint a una posición especifica
	
		Ejemplo:
			joint1 -> 90°
			joint2 -> 45°
		
		Topico
			/nombre_instancia/commands
```

```
JointTrajectoryController
	Uno muy usado en brazos roboticos, sirve para mover articulaciones siguiendo trayectorias
	
		Ejemplo:
			0 s -> posición A
			2 s -> posición B
			4 s -> posición C
	
		Topico
			/nombre_instancia/joint_trajectory
			o
			/nombre_instancia/follow_joint_trajectory
```

```
DiffDriveController
	Robots con dos ruedas diferenciales (tipo: Robot aspiradora, carrito de reparto, TurtleBot)
	
		Entrada típica:
			/cmd_vel
			
		Salida:
			Internamente mueve rueda_izquierda, rueda_derecha		
```

```
Ackermann Steering Controller
	Automoviles
	
	Entrada:
		/cmd_vel o mensajes Ackermann
	
	Salida:
		ángulo,
		direccion,
		velocidad,
		ruedas
```

```
JointStateBroadcaster
	Sirve para publicar estados de joints
	
	Publica:
		/joint_states
	
	 No recibe nada ni controla nada
```

```
IMU Sensor Broadcaster

	Publica:
		/imu
	
	No recibe comandos
```

```
ForceTorqueSensorBroadcaster

	Publica:
		/force_torque_sensor
```

---
### Tópicos 
Los tópicos los podemos ver como "cables" virtuales, como podemos observar en nuestro [[usable1.canvas]] y en una breve mención de nuestra [[Capa 5 (launch)|Capa 5]], estos son creados por ``control_manager`` en base a nuestra instancia, por ejemplo, si nosotros tenemos la siguiente línea de código:
```
controller_manager:

	ros__parameters:
	
		update_rate: 100
		
		velocity_controller:
		  type: velocity_controllers/JointGroupVelocityController
```
Sabemos que estamos declarando una instancia ``velocity_controller`` a la que le estamos cargando el Controlador ``JointGroupVelocityController``.
Cuando el ``spawner`` ([[Capa 5 (launch)|Capa 5]]) llama a ``controller_manager``, se crea oficialmente esta instancia.
El controlador ``JointGroupVelocityController`` ve que el nombre de la instancia al que fue cargado es ``velocity_controller``, entonces y solo entonces, se creara un *Tópico* en base al mismo nombre, declarado como:

``/velocity_controller/commands``

**¿Que es?**
Es nuestro "cable o canal" de comunicaciones, ya que los controladores son los únicos que puedes comunicarse directamente con ROS, necesitamos un canal, el cual ya creamos.

**¿Para que sirve?**
 Nos ayuda a que nuestros *Nodos* pueda comunicarse con el controlador mediante este cable que hemos creado, de está manera, le podemos mandar información/comandos desde nuestra lógica, al controlador, para que está sea procesada y visualizada hacia [[RViz]] o [[Gazebo]].
 
**¿Por que el Tópico termina en ``/commands`` si no es parte del nombre de la instancia?**
Estos es un simple identificador que crea el controlador ``JointGroupVelocityController``, podríamos decir que es un estándar, otros controladores podrían dejar solamente el nombre de la instancia agregando ``/`` al inicio del nombre o dejar otro nombre identificador al final de este.

---
### Nodos
Es una de las partes más importantes para trabajar con ROS2, sin este apartado, prácticamente no sirve de nada todo lo aprendido anteriormente, ya que si no tenemos "Logica", no hay movimiento, entonces de que nos serviría el Simulador.

Como bien acabamos de mencionar anteriormente, un *Nodo* es la **Lógica**, literalmente es nuestro archivo .cpp, el cual contiene código en especifico para realizar las tareas que queremos que realice nuestro Robot.

Primero, para irnos familiarizando con este termino, debemos saber que, ROS ya tiene ciertos Nodos por defecto, uno de ellos lo hemos mencionado en multiples ocasiones y seguramente ya te suena su nombre, es conocido como ``control_manager``, este nodo ya viene cargado con ROS, por lo tanto, solo necesitamos configurarlo, no crearlo, antes de mencionar cuales son algunos de los *Nodos* que ya vienen por defecto, necesitamos aclarar que, en su mayoría **Nosotros vamos a crear nuestros propios Nodos, de ahi viene la identidad de nuestro Robot**.

Ahora, veamos una pequeña lista de los Nodos por defecto:
```
controller_manager
	El jefe de los controladores, los crea
	
robot_state_publisher
	Dice donde está cada link del robot
	
joint_state_publisher_gui
	Genera ventana con sliders. para hacer pruebas con los joint

ros_gz_bridge
	Traductor entre Gazebo y ROS (Capa 5)

rviz2
	Visualizador, no controla nada

ros_gz_sim create
	Inserta el robot en Gazebo
	
spawner
	Su único trabajo es decirle a controll_managerm "Crea este controlador"
```
Ahora podemos ver que los *Nodos* no crean controladores, utilizan controladores

Como mencionamos anteriormente, todos estos nodos ya están creados, la realidad es que, nosotros tenemos que crear nuestros propios nodos de lógica para el comportamiento de nuestro robot, se vería algo así:
```
/ros2_ws/src/carrito_prueba_control/src/
	adelante.cpp
	atras.cpp
	giro_derecha.cpp
	giro_izquierda.cpp
	sensor.cpp
	pid.cpp
```
Para más información de como crear un Nodo, ir a la siguiente nota: [[Crear un Paquete de Control (Lógica) ROS]]

---
## Conclusiones
De está manera, podemos definir que:

- Nodo: Ejecuta Lógica 
- Tópico: Transporta mensajes
- Controlador: Maneja Hardware
- Gazebo: Simula Hardware
- RViz: Visualizador
- [[Micro-ROS]]: Lleva nodos a microcontrolador

Visualmente, podemos observar que todos estos conceptos de la [[Capa 7 (Lógica)|Capa 7]] no están aislados, sino que trabajan constantemente en conjunto, así que podemos verlo con el siguiente diagrama:
```
Nodos:
|	|- controller_manager
|	|- robot_state_publisher
|	|- ros_gz_bridge
|	|- adelante.cpp
|
Topicos:
|	|- /velocity_controler/commands
|	|- /joint_states
|	|- /cmd_vel
|	|- /scan
|
Instancias de controladores:
	|- velocity_controller
	|	  Tipo (Class):
	|		  JointGroupVelocityController
	|- joint_state_broadcaster
		  Tipo (Class):
			  JointStateBroadcaster
```
Todos viven en conjunto, solo que se necesitan unos de otros para hacer su función, el diagrama anterior es una representación de que todo está en igualdad de condiciones, aunque, realmente lo que sucede sería lo siguiente a nivel de ejecución:
```
Nodos
|
|
controller_manager
|	- velocity_controller
|		  - JointGroupVelocityController
ros_gz_bridge
|
robot_state_publisher
|
adelante.cpp
```




# Referencias
