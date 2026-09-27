---
aliases:
  - Curso ROS
tags:
  - En_curso
  - ROS
Creado: 2026-08-20
Relacionado:
  - Robotica
  - Simulacion
  - "[[ROS]]"
---
# Introducción
Esta nota será acerca del curso de [[Capa 2 (Simulación)|simulación]] para [[ROS]] llamado:

**ROS Basics in 5 Days (C++)**

De la pagina **The Construct**: https://app.theconstruct.ai/welcome

Aquí se escribirán todos los puntos importantes que considere necesarios documentar mientras se acredita el curso antes mencionado.

---
# Desarrollo

## Conceptos Básicos
- **Node**: Mini programa dedicado a una tarea especifica.
- **Topic**: Cable, grupo o canal de comunicación que sirve para que los nodes se comuniquen entre si.
- **WorkSpace**: Espacio de trabajo o carpeta principal donde se va a guardar, compilar y organizar todo el código del Robot.
## Publisher
También conocido como publicador, es un programa diseñado para escribir o transcribir un mensaje hacia un topic.

## Services
Los tópicos no son la única forma de comunicación, también existen los servicios, estos son útiles para ejecutar una función especifica, por ejemplo:

"**Has una rutina de movimiento durante 5 segundos y después detente**"

Los servicios se dividen en **dos** partes:

- **Service Server**: Es el servidor que contiene la lógica o función y la mantiene lista para ser ejecutada cuando alguien se lo pida.

- **Service Client**: Es el cliente que realiza la solicitud (call/request) para activar esa función en el servidor.

En pocas palabras, el servidor está en espera de que el cliente le pida la información o el cliente está en espera de que le pidan que vaya al servidor para avisar que ejecute la lógica almacenada.

### Ejemplo
Asumamos que tenemos el siguiente **Service Server**:

``roslaunch service_demo service_1aunch.launc_h

En este caso, primero debemos ejecutar el Servidor para "Encenderlo", si no se hace esto previamente, no se podrá mandar a llamar mediante el Client.
Esto se debe de realizar en terminales independientes, ya que, se mantiene en ejecución y no podrás ejecutar múltiples tareas en la misma terminal.

Ahora lanzamos el **Service Client**:

``rosservice call /service_demo "{}"

Ahora como lo habíamos visto anteriormente, el client mandaría llamar al server para ejecutar su lógica, aunque hay algo importante que debemos recordar.

A diferencia del tópico que se mantenía reproduciendo la lógica de manera contante, el service ejecuta una tarea especifica de principio a fin, en el caso de este ejemplo, moverse durante cierto periodo de tiempo definido y detenerse.

## Actions
Son un tipo de comunicación diseñado para tareas pesadas o de larga duración (como navegar en una habitación). Se parecen a los Services, pero resuelven sus dos principales limitaciones:

- **No bloquean el sistema (Asíncronas):** En un **Service**, el programa se "congela" a esperar de que termine la tarea antes de cualquier cosa. Al usar un **Action**, el robot puede ejecut7ar la tarea de fondo y seguir realizando otros cálculos al mismo tiempo. 
- **Envían Feedback**: Mientras la acción se ejecuta, el servidor te envía actualizaciones en tiempo real ("Voy al 50% del camino" o "Me faltan 2 metros"), algo que un Service no puede hacer.
- **Se pueden cancelar**: Si el robot va camino a la cocina y detecta un obstáculo inesperado, el Client puede enviarle la señal de cancelar (cancel goal) a mitad del proceso. Un **Service** no puede ser cancelado una vez ejecutado. 

También se clasifican en dos al igual que los Service:
- **Action Server**.
- **Action Client**.

## /cmd_vel
Es un tópico especifico que utiliza ROS para enviar comandos de velocidad a la base motriz del robot.

## Detener Ejecución
Es importante recordar que se pueden detener la ejecución de los [[Capa 7 (Lógica)|nodos]] en nuestra terminal, pero la simulación seguirá activa con la ultima acción, ya que, se necesita un comando diferente como lo podría ser "Detener", para pausar los movimientos del Robot simulado.


## Debugging (Depuración)
Al programar robots, resolver fallos o comportamientos inesperados es parte del proceso diario. Para ellos, ROS cuenta con un ecosistema de herramientas de diagnostico.

La herramienta visual más importante es [[RViz]] (ROS Visualization). Te permite ver en un entorno 3D lo que el robot "ve" y siente en tiempo real: sus sensores de distancia, mapas, trayectorias planeadas y el modelo del robot. 

## RViz
ROS Visualization.

Es la herramienta que nos permite visualizar el entorno del Robot, como lo que "ve" y "siente".

Una de las maneras de ejecutar / abrir RViz es a través del siguiente comando: ``rosrun rviz rviz.

### Fixed Frame
Es el marco de referencia fija (el "origen 0,0,0") que RViz utiliza como centro absoluto del universo para dibujar todos los sensores, transformaciones y [[Capa 1 (Modelo 3D)|modelos 3D]].

Si elegimos a ``odom`` u ``map`` en **Fixed Frame**, el robot se moverá por el mundo, ya que el marco de referencia para el Robot será el "mundo" del visualizador, en cambió, si elegimos ``base_link``, el robot se quedara estático en su centro y veremos como el mapa u los obstáculos giraran alrededor de el.
### base_link
Recordemos siempre cambiar a **base_link** en el **Fixed Frame**.

``base_link`` es el centro físico del robot, también es un punto geométrico ubicado habitualmente en el centro de la estructura o eje de ruedas del robot.

Para centrar la visualización en el vehículo, colocamos ``base_link`` como **Fixed Frame**, de está manera le estamos diciendo a RViz "Haz que el centro del mundo sea el propio robot". Toda la información del sensor laser (LaserScan) se dibujara relativa a la posición del Robot.

### map / odom
**El piso / Mundo real**
Si el robot se mueve por la habitación, la habitación no se mueve, el robot si. Para ver al robot desplazándose por el piso, el **Fixed Frame** debería ser ``map`` u ``odom``.


### Botón add
Aquí encontraremos diferentes opciones para añadir a nuestro visualizador, como por ejemplo: **LaserScan** o **RobotModel**.

- **RobotModel**: Carga la representación tridimensional del Robot.
- **LaserScan**: Añade la visualización del Laser / [[Sensor Lidar|Lidar]] del Robot.


---
# Referencias












# Referencias
