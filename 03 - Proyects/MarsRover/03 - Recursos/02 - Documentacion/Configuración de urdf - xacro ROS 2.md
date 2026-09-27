---
aliases:
  - urdf
  - xacro
  - configuración urdf
  - configuración xacro
tags:
  - ROS
  - En_curso
Creado: 2026-08-24
Relacionado:
  - Robot
  - Rviz
---
# Introducción

En está nota se abordara todo lo relacionado a un archivo .urdf o .xacro.
Configuración, tips, cosas que puede almacenar, etc...

---
# Desarrollo
## Anatomía Básica
Un archivo URDF funciona con solo dos bloques fundamentales: `link` (las partes rígidas/cuerpos) y `joint` (las articulaciones o uniones entre cuerpos).

#### Cuerpos Rígidos `<link>
Cada link representa un componente físico.

`<link name="base_link">

En el código se puede usar la propiedad `<visual>`, la cual le dice a RViz2 como debe visualizarse.

```
<link name="base_link">
  <visual>
    <geometry>
      <box size="0.5 0.3 0.15"/>  <!-- Geometría: largo (X), ancho (Y), alto (Z) -->
    </geometry>
    <material name="blue"/>       <!-- Color asignado previamente -->
  </visual>
</link>
```
En el código también pueden apreciarse más propiedades, vamos a desglosarlas

**Formas Geométricas Estándar en URDF (`<geometry>`):***
- **Caja:** `<box size="X Y Z"/>`(en metros)
- **Cilindro:** `<cylinder radius="R" length="L"/>` (radio y altura).
- **Esfera:** `<sphere radius="R"/>`.

**Pigmentación (Color)**:
La etiqueta `<material>` es la que nos ayuda a decidir el material o mejor dicho, el color de nuestra geometría, esto se hace de la siguiente manera:

`<material name="color_name">`
	`<color rgba="R G B A"/>`
`<material>`

> **Nota**: Primero se conceptualizan y declaran los cuerpos (link) y después se conectan mediante las articulaciones (joint).

##### Estructura Completa de un link
```
<link name="nombre_del_cuerpo">
  <visual>       
  Aspeto Gráfico (Lo que ves en RViz2)    
  </visual>
  
  <collision>    
  Geometría de Impacto (Para detectar choques)
  </collision>
  
  <inertial>
  Propiedades Físicas (Masa e Inercia para Simulación)              </inertial>
</link>
```

1. `<visual>`(Apariencia)
Se pueden poner **varios** bloques `<visual>`dentro del mismo `<link>`si tu pieza está compuesta por varias formas unidas (por ejemplo, una caja con dos cilindros).

2. `<collision>`(Física de contacto)
**¿Por que se separa de `<visual>`?** Para optimizar computo. Un robot puede tener un modelo visual hiperdetallado (miles de polígonos), pero para calcular choques en tiempo real es mejor representarlo con una caja o cilindro simple.

3. `<inertial>`(Dinámica)
4. Obligatorio si vas a simular tu robot en [[Motor Electrico|motores]] físicos como **[[Gazebo]]** o **Isaac Sim**. Describe como responde el cuerpo a fuerzas y gravedad.
	- Contiene la masa (`<mass value="1.5/>`) y la matriz de inercia 3x3 (`<inertia ixx="..." ixy="..." ... />)

###### Ejemplo Practico de link completo
```
<link name="chasis_avanzado">

  <!-- ASPECTO VISUAL (Se ve en RViz2) -->
  <visual>
    <origin xyz="0 0 0" rpy="0 0 0"/>
    <geometry>
      <!-- Usamos un modelo 3D detallado diseñado en CAD -->
      <mesh filename="package://rover_description/meshes/chasis.stl" scale="0.001 0.001 0.001"/>
    </geometry>
    <material name="blue"/>
  </visual>

  <!-- COLISIÓN (Simplificada para que la computadora no sufra) -->
  <collision>
    <origin xyz="0 0 0" rpy="0 0 0"/>
    <geometry>
      <box size="0.5 0.3 0.15"/>
    </geometry>
  </collision>

  <!-- PROPIEDADES FÍSICAS (Para simular masa real) -->
  <inertial>
    <origin xyz="0 0 0" rpy="0 0 0"/>
    <mass value="5.0"/> <!-- 5 Kilogramos -->
    <inertia ixx="0.0468" ixy="0" ixz="0" iyy="0.1135" iyz="0" izz="0.1414"/>
  </inertial>

</link>
```


>**Nota**: Este código nos hace ver que los tres bloques **conviven de forma independiente dentro del mismo link**, compartiendo el mismo sistema de coordenadas local del cuerpo. 

---
#### Articulaciones `<joint>`
Si los `<link>`son los huesos del robot, los `<joint>`son los músculos y articulaciones.

El `joint` conecta un `link` padre (`parent`) con un link hijo (`child`) y define como se mueve la articulación.

`<joint name="wheel_front_ledt_joint" type="continous">

En el siguiente código se pueden ver las diferentes propiedades de un `joint
```
<joint name="wheel_front_left_joint" type="continuous">
  <parent link="base_link"/>
  <child link="wheel_front_left_link"/>
  <origin xyz="0.15 0.18 -0.05" rpy="-1.5708 0 0"/>
  <axis xyz="0 0 1"/>
</joint>
```
Vamos a desglosarlas:
 
`type`(Tipo de articulación):
 
- `fixed`: Rígida, no se mueve (ej. `base_footprint` a `base_link` o un sensor montado).
- `continuous`: Gira de forma infinita sin límites (ideal para ruedas).
- `revolute`: Gira pero con límites de ángulo en radianes (ej. un servomotor de 0° a 180°).
- `prismatic`: Se desliza lineal-mente sobre un eje (ej. un pistón o ascensor).
- `floating`: Permite 6 grados de libertad (movimiento libre en 3D y rotación).
- `planar`: Permite movimiento en un plano 2D (se mueve en X, Y y gira en Z).

`origin` (Posición y orientación del hijo respecto al padre):

- `xyz="X Y Z"`: Desplazamiento en metros 
- `rpy="Roll Pitch Yaw"`: Rotación en radianes sobre los ejes X, Y y Z.
	- El `-1.5708` que usamos en `rpy` equivale a **$-\pi / 2$ rad (-90°)**, necesario para acostar el cilindro de la rueda vertical y ponerlo horizontal.

`axis` (Eje de movimiento):
Define sobre que eje ocurre el movimiento (solo aplica para `continous`, `revolute` y `prismatic`.

- `<axis xyz="0 0 1"/>`: Indica que la rueda gira alrededor del eje Z propio de la articulación (que por la rotación del `origin`, apunta en la dirección de rodadura).

`<limit>`(Bloque de Restricciones):
Es obligatorio para joints tipo `revolute`y `prismatic`(en `continous`no se requiere limite angular).

Se escribe como:
```
<limit lower="-1.5708" upper="1.5708" effort="10.0" velocity="1.0"/>
```
**Desglose Detallado**:

- `lower`/`upper`: Limites angular (en radianes) o lineal (en metros). En este ejemplo, permite moverse de -90° a +90° (-1-5708 a +1.5708 rad).
- `effort`: Torque o fuerza máxima que puede aplicar el motor (en N * m o N).
- `velocity`: Velocidad máxima de la articulación (en *rad/s* o *m/s*)

##### Etiquetas complementarias
Existen otras 4 etiquetas secundarias que se usan dentro de `<joint>`para simulaciones físicas avanzadas o para controladores reales:

- `<dynamics>` (Fricción y amortiguamiento real)
	- `<damping>`(Amortiguamiento)
	- `<friction>`(Fricción estática)
- `<mimic>`(Articulaciones imitadoras / acopladas)
	- `multiplier`
	- `offset`
- `<safety_controller>`(Limites de seguridad por software)
	- `limit`
- `<calibration>`(Cero mecánico)

| `<joint>`      |                                                     |
| -------------- | --------------------------------------------------- |
| parent / child | **Obligatorio**                                     |
| origin         | **Obligatorio**                                     |
| axis           | Revolute / Continuous / Prismatic                   |
| limit          | Revolute / Prismatic Rango (lower/upper) y potencia |
| dynamics       | **Opcional**                                        |
| mimic          | **Opcional**                                        |

##### Relación parent / child
- `parent`(Padre/Origen): El sistema de referencia de origen.
- `child`(Hijo/Destino): El elemento que se posiciona **relativo al padre**.

```
base_footprint (En el suelo)(parent)
|
v
(joint: xyz="0 0 0.15")
|
v
base_link (Elevado 15 cm)(child)
```

---
#### base_footprint

`<link name="base_footprint"/>

En el siguiente código se puede analizar su contenido:
```
<link name="base_footprint"/>

<joint name="base_footprint_joint" type="fixed">
  <parent link="base_footprint"/>
  <child link="base_link"/>
  <origin xyz="0 0 0.15" rpy="0 0 0"/>
</joint>
```
En Rebotica móvil, `base_footprint` es un link "fantasma" sin geometria visual que se ubica exactamente en el suelo (Z = 0). Elevar el `base_link` a 0.15m hace que las ruedas del radio 0.10m descansen correctamente sobre el plano de [[RViz]] sin transpasar el suelo.

---
## Doble extensión .urdf.xacro
En un sistema como [[Linux]], **un archivo puede tener múltiples extensiones leídas de derecha a izquierda**. No es un solo tipo de archivo inventado, sino un proceso en cadena:

- `xacro`(XML Macro): Indica que procesador debe leerlo primero. Xacro es un lenguaje de plantillas que permite usar variables, matemáticas y funciones (macros).
- `.urdf`(Unified Robot Description Format): Indica el formato de salida final que entiende [[ROS]] 2.

**¿Como funciona la cadena?**
ROS2 no entiende código Xacro directamente. Cuando ejecutas tu comando de [[Capa 5 (launch)|launch]], ocurre esto en segundo plano:

```
rover.urdf.xacro
|
v
(Procesador Xacro)
|
v
Codifo URDF Puro
|
v
RViz / ROS 2
|
v
[[Capa 1 (Modelo 3D)|Modelo 3D]]
```
El doble punto es simplemente una convención para que tu y tu equipo sepan de un vistazo: "Este archivo se escribe como Xacro (`.xacro`), pero se procesara para generar un URDF (`.urdf`)".

---

# Referencias
