---
aliases:
  - Nav2
  - nav2
tags:
  - ROS
Creado: 2026-10-15
Relacionado:
  - Simulacion
  - AutoNav
  - Autonavegacion
---
# Introducción
Resumen de guía [[Nav2]]

---
# Desarrollo
## 1. Topics, Services y Actions

[[ROS]] 2 utiliza diferentes mecanismos de comunicación entre [[Capa 7 (Lógica)|nodos]].

|Mecanismo|¿Para qué sirve?|Ejemplo|
|---|---|---|
|**Topic**|Publicar y recibir datos continuamente.|`/cmd_vel` transmite comandos de velocidad.|
|**Service**|Realizar una petición y recibir una respuesta.|Consultar o cambiar una configuración.|
|**Action**|Ejecutar una tarea que puede durar tiempo, con feedback y resultado.|`NavigateToPose` permite solicitar que Maya llegue a una meta.|

## 2. Lifecycle Nodes
Los nodos de Nav2 tienen un ciclo de vida controlado.

Los estados principales son:

- `Unconfigured`: todavía no se han configurado sus recursos.
- `Inactive`: está configurado, pero no se encuentra activo para realizar su operación normal.
- `Active`: está activo.
- `Finalized`: ha finalizado su ciclo de vida.

Los **Lifecycle Managers** coordinan la transición de los nodos administrados entre estados.

El mecanismo _bond_ permite detectar si se pierde la comunicación esperada con un nodo administrado.

## 3. Behavior Trees (BT)

Un **Behavior Tree** organiza las tareas que deben ejecutarse para completar una misión.

Por ejemplo:

1. Calcular una ruta.
2. Seguirla.
3. Si algo falla, intentar recuperarse.
4. Continuar o finalizar la navegación.

El **BT Navigator** coordina la navegación utilizando un árbol de comportamiento.

Los árboles pueden definirse mediante archivos XML y utilizar nodos implementados como plugins de BehaviorTree.CPP.

## 4. Los cinco Navigation Servers

|Componente|Función que debes recordar|
|---|---|
|**Planner Server**|Calcula la ruta global hacia la meta.|
|**Controller Server**|Calcula los comandos de velocidad para seguir la ruta.|
|**Behavior Server**|Ejecuta comportamientos auxiliares y de recuperación.|
|**Smoother Server**|Refina una ruta para mejorar su geometría.|
|**Route Server**|Calcula recorridos utilizando un grafo de navegación predefinido.|

Los servidores pueden utilizar algoritmos intercambiables mediante plugins.

Por ejemplo, el Controller Server puede utilizar DWB o MPPI para calcular cómo seguir una ruta.

## 5. State Estimation y TF2
Nav2 necesita conocer la posición del robot y relacionarla con el mapa y los sensores.

La cadena de referencia habitual es:

```
map
 └── odom
      └── base_link
           ├── base_laser
           └── imu_link
```

Las transformaciones más importantes son:

|Transformación|Función|
|---|---|
|`map → odom`|Relaciona la referencia local con la global.|
|`odom → base_link`|Representa la estimación local del movimiento del robot.|
|`base_link → sensores`|Describe la posición de los sensores respecto al cuerpo del robot.|

**TF2** permite consultar las transformaciones entre frames y sus cambios temporales.

### Diferencia entre SLAM y AMCL

- **SLAM:** construye un mapa mientras estima la posición del robot.
- **AMCL:** estima la posición del robot dentro de un mapa previamente creado.

La odometría puede obtenerse de encoders, IMU, visión u otros sensores.

`robot_localization` permite fusionar datos de múltiples sensores para mejorar la estimación del estado.

## 6. Environmental Representation: Costmaps
Un **costmap** es una cuadrícula que representa el entorno mediante valores de costo.

Simplificando:

- Espacio libre: transitable.
- Obstáculos: zonas que deben evitarse.
- Espacio desconocido: zonas cuya transitabilidad no está confirmada.
- Inflación: zonas próximas a obstáculos que reciben costos para favorecer una distancia de seguridad.

Nav2 utiliza dos representaciones importantes:

- **Costmap global:** ayuda al planificador a calcular rutas.
- **Costmap local:** ayuda al controlador a calcular movimientos teniendo en cuenta el entorno cercano.

### Layers y Filters

|Elemento|Función|
|---|---|
|**Costmap Layers**|Incorporan información del entorno, por ejemplo, desde un LiDAR.|
|**Costmap Filters**|Aplican reglas espaciales, como restringir el acceso a determinadas zonas.|

Ejemplos de filtros:

- _Keepout_: zonas prohibidas.
- _Speed Filter_: zonas con límites de velocidad.

## 7. Waypoint Following
El componente `nav2_waypoint_follower` permite enviar al robot a varios puntos de paso.

Por ejemplo:

```
Punto A → Tomar fotografía
    ↓
Punto B → Esperar
    ↓
Punto C → Finalizar
```

También admite plugins para ejecutar tareas en los puntos de paso.

Esto permite construir misiones más complejas que simplemente alcanzar una única meta.

**Debes aprender:** la navegación a una meta es una tarea individual; seguir waypoints permite organizar una secuencia de destinos y acciones.

---

# Lo que debes dominar

1. **Comunicación ROS 2:** distinguir Topics, Services y Actions.
2. **Ciclo de vida:** comprender por qué los nodos de Nav2 deben configurarse y activarse.
3. **Behavior Trees:** entender cómo se coordinan las tareas de navegación.
4. **Navigation Servers:** diferenciar planificación, control, recuperación, suavizado y navegación mediante grafos.
5. **TF2 y estimación:** comprender `map → odom → base_link`, así como las funciones de SLAM, AMCL y odometría.
6. **Costmaps:** entender cómo Nav2 representa el entorno para planificar y evitar obstáculos.

### El proceso completo de navegación
1. [[RViz]] envía la meta mediante una Action.
2. El BT Navigator coordina la navegación.
3. El Planner Server calcula una ruta utilizando la representación global del entorno.
4. El Smoother Server puede refinarla, si el árbol lo solicita.
5. El Controller Server calcula los comandos de velocidad.
6. La estimación de posición y las transformaciones TF2 permiten relacionar el robot con el mapa y los sensores.
7. Los costmaps ayudan a planificar y controlar el movimiento evitando obstáculos.
8. Si aparece un problema, el árbol puede solicitar un comportamiento de recuperación.

Este proceso es conceptual: el orden exacto y los componentes utilizados dependen de la configuración del árbol y de Nav2.

---
# Referencias
