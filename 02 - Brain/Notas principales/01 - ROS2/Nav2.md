---
aliases:
  - nav2
tags:
  - ROS
Creado: 2026-10-14
Relacionado:
  - Simulacion
  - AutoNav
  - Autonavegacion
---
# Introducción
En este archivo se abordaran muchas cosas relacionadas a Nav2 siguiendo su pagina web oficial y guía: https://docs.nav2.org/rolling/

Resumen de Información: [[Resumen Nav2]]

---
# Conceptos Clave

## Action: NavigateToPose.
Una de las interfaces principales para solicitar que el robot navegue hasta una pose objetivo.

## Behavior Tree Navigator.
Coordina el comportamiento de navegación mediante un árbol de comportamiento (Behavior Tree).

### ¿Que es un BT?
Si tenemos varias tareas.
1. Calcular una ruta.
2. Seguir esa ruta.
3. Comprobar si puede continuar avanzando.
4. Si encuentra un obstáculo, intenta resolver el problema.
5. Si llega a si destino, finaliza la navegación.

Un **BT** organiza estas tareas y define cuando se ejecutan, en que orden y que sucede si alguna llega a fallar.

### ¿Por que un BT en vez de una Maquina de Estados?
Un FSM podría definir estados como:
- Esperando una meta.
- Calculando una ruta.
- Avanzando.
- Detectando un obstáculo.
- Recuperándose.
- Re intentando la planificación.
- Llegando al destino.

El problema aparece cuando aumenta la complejidad; cada situación nueva puede requerir más estados y transiciones.

Un BT permite organizar las tareas en bloques re utilizables y establecer reglas de ejecución entre ellos.

- Se divide en tareas y subarboles
- Permite reutilizar subarboles
- Planificar, seguir y recuperarse mediante un árbol

>**Importante**: BT no es siempre superior a las FSM. Este se eligió para Nav2 porque facilita la organización y reutilizacion de comportamientos complejos.

### Ejemplo simplificado
Nav2 puede definir la estructura del árbol en un archivo XML.

```xml
<root BTCPP_format="4" main_tree_to_execute="MainTree">
  <BehaviorTree ID="MainTree">
    <Sequence>
      <ComputePathToPose
        goal="{goal}"
        path="{path}"/>

      <FollowPath path="{path}"/>
    </Sequence>
  </BehaviorTree>
</root>
```
Aquí aparecen tres conceptos:
- `Sequence`: intenta ejecutar sus hijos en orden. Si uno falla, la secuencia falla.
- `ComputePathToPose`: solicita calcular una ruta hacia la meta.
- `FollowPath`: solicita seguir la ruta calculada.

### ¿Los nodos son plugins?
Nav2 utiliza Behavior Tree.CPP V4.

Esta biblioteca permite registrar nodos de comportamiento y construir arboles a partir de ellos.

>**Por ejemplos**:
>Nav2 puede tener un nodo llamado ComputePathToPose. 
>
>Cuando el XML incluye ese nombre, el sistema debe disponer del plugin correspondiente para reconocerlo y ejecutarlo.

Esto permite ampliar los comportamientos sin tener que escribir toda la lógica de navegación desde cero.

También permite construir subarboles: un árbol más grande puede utilizar otro árbol como parte de una tarea.

## Lifecycle Nodes.
En Nav2, no basta con que un [[Capa 7 (Lógica)|nodo]] exista: muchos componentes deben configurarse y activarse antes de funcionar correctamente.

Un LIfecycle es un nodo que puede pasar por varios estados.

Para simplificar, imagina que enciendes un sistema de navegación.
1. El nodo existe, pero todavía no está preparado.
2. Carga sus parámetros y prepara sus recursos.
3. Activa sus interfaces y comienza a trabajar.
4. Cuando se detiene, desactiva y libera sus recursos de forma controlada.

Los estados principales son:

| Estado         | Significado                                                            |
| -------------- | ---------------------------------------------------------------------- |
| `unconfigured` | El nodo todavía no ha sido configurado.                                |
| `inactive`     | Esta configurado, pero no está activo para realizar su trabajo normal. |
| `active`       | Esta activo y puede realizar su funcion.                               |
| `finalized`    | Ha terminado su ciclo de vida.                                         |
También existen estados transitorios, como `configuring`, `activating` y `deactivating`, que representan las transiciones entre estados.

### ¿Quien controla estos estados?
Nav2 utiliza un componente llamado **Lifecycle Managers**.

Su función es coordinar la configuración y activación de los nodos administrados.
**Ejemplo:**
- /lifecycle_manager_localization/manage_nodes
- /lifecycles_manage_navigation/manage_nodes

### ¿Que ocurre si un nodo falla?
Un bond es un mecanismo de comunicación que permite detectar que un componente administrado ha dejado de responder o ha desaparecido.

Si un servidor de Nav2 falla, el administrador puede detectar la perdida de esa conexión y tomar medidas para evitar que el sistema continue en un estado inconsistente.

Esto es importante porque la **navegación depende de varios componentes que deben funcionar coordinadamente**.

## Navigation Servers
Explica que componentes de Nav2 realizan el trabajo real de navegación.

### Cinco servidores principales de Nav2
En la guía se presentan cinco servidores principales:
- Planner.
- Controller.
- Behavior.
- Smoother.
- Route.

Un **servidor** es un componente que ofrece una interfaz para solicitar una tarea.
En estos casos, los servidores de Nav2 utilizan Actions y pueden alojar algoritmos intercambiables mediante plugins.

Imaginemos que se le da una meta al Robot desde [[RViz|Rviz]]:

| Servidor          | ¿Que hace?                                                   | Ejemplo                                                                    |
| ----------------- | ------------------------------------------------------------ | -------------------------------------------------------------------------- |
| Planner Server    | Calcula una ruta global hacia la meta.                       | Decide por donde debe pasar el robot ára llegar a su destino.              |
| Controller Server | Calcula como debe moverse el robot para seguir la ruta.      | Genera velocidades para avanzar y girar evitando obstaculos.               |
| Behavior Server   | Ejecuta comportamientos auxiliares y de recuperacion.        | Ordena retroceder o girar para intentar salir de una situación complicada. |
| Smoother Server   | Refina una ruta para mejorar su geometria.                   | Reduce giros bruscos o irregularidades de la ruta calculada.               |
| Route Server      | Calcula recorridos sobre un grafo de navegacion predefinido. | Permite seguir una red de caminos o carriles definidos previamente.        |

### ¿Que significa que los servidores utilicen plugins?
Un servidor puede alojar distintos algoritmos sin que tengas que cambiar toda la arquitectura de Nav2.

Por ejemplo, **Controller Server** puede utilizar distintos controladores:
- **DWB**: Calcula velocidades para seguir la ruta considerando posibles trayectorias y obstáculos.
- **MPPI**: Evalúa numerosas trayectorias candidatas para seleccionar un control adecuado.

Ambos pueden cumplir la tarea de seguir una ruta, aunque utilicen métodos diferentes.

>La guía menciona el nombre **FollowPath**. Este es un alias de la tarea que se relaciona con el controlador configurado para ejecutarla.

### ¿Como colaboran durante una navegación?
Imaginamos que seleccionamos una meta en RViz y nuestro Robot debe evitar un obstáculo.

Un proceso conceptual seria:
```
Meta enviada desde RViz
|
v
BT Navigator
|
v
Planner Server (Calcula la ruta)
|
v
Smoother Server (Refina la ruta)
|
v
Controller Server (Calcula las velocidades)
					|
					v
				  Robot
					|
			 ¿Puede avanzar?
			/               \
		   Si               No
		   |                 |    
		Continuar      Behavior Server
		               Intenta recuperarse
```

Este esquema es ilustrativo: el árbol determina cuándo se solicitan las tareas, y no todas las navegaciones necesitan ejecutar un suavizador o una recuperación.

Además, el controlador puede re calcular las velocidades continuamente mientras el Robot avanza.

**Importante:** el Behavior Server no decide por sí solo cuándo recuperarse. El Behavior Tree puede detectar un fallo y solicitar el comportamiento de recuperación correspondiente.

### ¿Que es el footprint del robot?
El _footprint_ representa la forma que ocupa el robot vista desde arriba. Nav2 lo utiliza para evaluar si puede pasar por determinadas zonas sin colisionar.

La guía menciona dos formas de definirlo:

- `robot_radius`: representa al robot mediante un círculo.
- `footprint`: representa su contorno mediante un polígono.

Por ejemplo, un robot aproximadamente circular podría utilizar un radio. Para Maya, si su base tiene una forma rectangular, podría resultar más apropiado definir un polígono que represente sus dimensiones reales.

**¿Por qué importa?**

Imagina que el planificador encuentra un pasillo de 60 cm de ancho. Si el modelo del robot tiene dimensiones incorrectas, Nav2 podría considerar transitable un espacio por el que el Robot realmente no cabe.

El footprint también puede actualizarse cuando cambia la forma del robot, por ejemplo, si despliega un brazo.

**Para un Rover:** conviene que el footprint refleje las dimensiones físicas de su base. No basta con configurar correctamente el [[Sensor Lidar|LiDAR]] si la geometría utilizada para comprobar colisiones no representa al robot.

### ¿Que es Waypoint Following?
Pero, que sucede si queremos visitar varias posiciones.

Un _waypoint_ es un punto de paso o destino. El componente permite ejecutar una secuencia de destinos y, mediante plugins de tareas, realizar acciones adicionales en ellos.

La guía también presenta dos enfoques de arquitectura:

- **Robot sencillo y gestor central inteligente:** un sistema externo decide las tareas y el robot se encarga de ejecutarlas.
- **Robot inteligente y gestor central sencillo:** el propio robot administra misiones más complejas, condiciones y decisiones.

>Ambos enfoques son posibles. Un árbol de comportamientos de nivel superior podría coordinar esas decisiones con Nav2.

### Conclusion
Hay tres conceptos que no debes confundir:

- **Servidor**: aloja y ejecuta la tarea.
- **Plugin**: implementa el algoritmo concreto.
- **Alias**: identifica la tarea o configuración asociada al plugin.

## State Estimation
Estimación de estado. 
La idea central es distinguir dos cosas: **donde cree el sistema que está el robot en el mapa y como estima su movimiento local**.

### ¿Que es TF y por que necesita esos Frames?
En [[ROS]] 2, los _frames_ son sistemas de referencia que permiten expresar posiciones y orientaciones.

Por ejemplo, un Robot puede tener frames como:

- `map`: referencia global del mapa.
- `odom`: referencia local que sigue el movimiento estimado del robot.
- `base_link`: referencia unida al cuerpo del robot.
- `base_laser`: referencia del LiDAR.

ROS 2 utiliza **TF2** para conocer las transformaciones entre esos sistemas de referencia y cómo cambian con el tiempo.

La estructura mínima que recomienda la guía es:
```
map
 └── odom
      └── base_link
           ├── base_laser
           └── imu_link
```
Cada conexión representa una transformación entre dos frames.

Por ejemplo, la transformación `base_link → base_laser` permite conocer dónde está montado el LiDAR respecto al cuerpo del Robot.

### ¿Por que necesitamos map y odom separados?
Los encoders pueden estimar ese desplazamiento, pero sus errores se acumulan. Por ejemplo, las ruedas pueden deslizarse o sus medidas pueden no ser exactas.

Este fenómeno se conoce como **deriva odométrica**.

Para comprender cómo se resuelve, debemos distinguir los dos frames.

`odom`: el movimiento local

El frame `odom` proporciona una referencia local continua y suave.

Sirve para estimar cómo se mueve Maya de un instante al siguiente.

Sin embargo, su posición puede desviarse progresivamente de la posición real.

`map`: la referencia global

El frame `map` representa la referencia global utilizada para la navegación.

Un sistema de localización, como AMCL, puede estimar dónde se encuentra el Robot dentro de un mapa conocido y corregir su posición global.

Por eso separamos las transformaciones:

- `odom → base_link`: sigue el movimiento estimado localmente.
- `map → odom`: relaciona esa estimación local con la referencia global.

Así, el sistema puede mantener un movimiento local suave y, a la vez, corregir su posición respecto al mapa.

### ¿Qué diferencia hay entre localización y SLAM?
La guía menciona dos opciones principales de Nav2.

**Localización:** El Robot dispone de un mapa y necesita determinar dónde está dentro de él.

Por ejemplo, utilizas un mapa creado previamente y AMCL compara las observaciones del LiDAR con ese mapa para estimar la posición del robot.

**SLAM:** El Robot construye un mapa mientras estima su propia posición durante la exploración.

En ambos casos, el sistema de posicionamiento debe proporcionar la transformación `map → odom` para que la arquitectura de navegación funcione según lo esperado.

Y un detalle importante: **Nav2 no exige utilizar un LiDAR**. También es posible utilizar cámaras, sensores de profundidad, GPS u otras fuentes de posicionamiento y detección, siempre que se proporcionen las interfaces y transformaciones necesarias.

### ¿Qué es la odometría y qué hace robot_localization?

La **odometría** estima el movimiento del robot a partir de sensores.

Por ejemplo, el robot puede disponer de:

- Encoders de las ruedas.
- Una IMU que mide aceleraciones y velocidades angulares.
- Una cámara que estima el movimiento mediante visión.

Cada sensor tiene limitaciones. Los encoders pueden sufrir deslizamientos, mientras que una IMU puede acumular errores al integrar sus mediciones.

El paquete `robot_localization` permite fusionar información de múltiples sensores mediante filtros de estimación, como el filtro de Kalman extendido (EKF).

Un esquema conceptual sería:

```
Encoders ───┐
	        │
IMU ────────┼──> robot_localization
            │          │
Visión ─────┘          ├──> Odometry
                       └──> odom → base_link
```

Este esquema supone que las fuentes están configuradas para proporcionar esas entradas. No todos los sensores tienen que utilizarse, y la salida depende de la configuración.

La finalidad es obtener una estimación de movimiento más estable aprovechando las ventajas de diferentes sensores.
### Resumen visual: cómo se relaciona todo

```
               MAPA GLOBAL
                    │
            Localización / SLAM
                    │
                 map → odom
                    │
                    ▼
                   odom
                    │
             Sistema odométrico
                    │
              odom → base_link
                    │
                    ▼
                base_link
                 /      \
                /        \
          base_laser    imu_link
```

La idea que debes retener es que Nav2 necesita una cadena de referencias consistente para relacionar el mapa, la posición del robot y los sensores.

No basta con tener los sensores funcionando: **sus mediciones deben estar correctamente relacionadas con los frames que utiliza la navegación**.

**Repaso rápido**
- **`map → odom`:** localización global o SLAM.
- **`odom → base_link`:** estimación del movimiento local.
- **`base_link → sensores`:** ubicación de los sensores respecto al robot.
- **TF2:** gestiona las transformaciones entre frames.
- **`robot_localization`:** permite fusionar sensores para mejorar la estimación del estado.
## Environmental Represemntation
La idea principal: **Nav2 utiliza costmaps para representar qué tan conveniente o peligroso es atravesar cada zona.**

- **Costmap:** cuadrícula 2D con celdas que representan espacio libre, obstáculos, zonas desconocidas y costos de proximidad a obstáculos.
- **Layers:** incorporan información de sensores, como LiDAR o cámaras, para actualizar el costmap.
- **Costmap Filters:** modifican el comportamiento según zonas marcadas en un mapa, por ejemplo, áreas prohibidas o zonas con velocidad limitada.
- **Otras representaciones:** mapas 3D, mapas de pendientes y modelos basados en objetos detectados mediante aprendizaje automático.

**Aplicado a un Robot:** el planificador utiliza el costmap global para calcular rutas; el controlador utiliza el costmap local para decidir cómo moverse evitando obstáculos.

Una distinción importante: **las layers representan e incorporan información del entorno; los filters permiten aplicar reglas espaciales específicas**, como prohibir el paso por una zona.


---

# Referencias
