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







---
# Referencias
