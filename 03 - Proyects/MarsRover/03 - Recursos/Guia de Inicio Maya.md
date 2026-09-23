---
aliases:
tags:
  - MarsRover
  - Completo
Creado: 2026-09-23
Relacionado:
  - ROS2
---
# Introducción
En está nota exploraremos *mis* problemás iniciales a la hora de obtener el WorkSpace de Maya y quere ejecutarlo utilizando el repositorio: https://github.com/MarsRoverUdeGSpace.

---
# Tutorial rápido — Preparar y ejecutar Maya en mi equipo

## 1. Entrar al repositorio principal

### Causa
Necesitamos trabajar desde la raíz del repositorio.

### Solución

Ejecutar:

```bash
cd /Data/mars_rover/maya_2026/AutoNav_Mission_2026
```

---
## 2. Inicializar los submódulos de Git

### Causa
El repositorio utiliza submódulos y algunos paquetes, como los relacionados con ZED, pueden no estar descargados correctamente.

### Solución

Ejecutar desde:

```text
/Data/mars_rover/maya_2026/AutoNav_Mission_2026
```

Comando:

```bash
git submodule update --init --recursive
```

---

## 3. Limpiar compilaciones anteriores

### Causa
Puede haber archivos viejos de compilación o configuraciones anteriores.

### Solución

Ejecutar desde:

```text
/Data/mars_rover/maya_2026/AutoNav_Mission_2026
```

Comando:

```bash
rm -rf build install log
```

---

## 4. Cargar [[ROS]] 2 Jazzy

### Causa
La terminal necesita conocer la instalación base de ROS 2.

### Solución

Se puede ejecutar desde cualquier carpeta.

```bash
source /opt/ros/jazzy/setup.bash
```

---

## 5. Evitar que el [[Capa 5 (launch)|launch]] dependa obligatoriamente de ZED

### Causa
Aunque se ejecute Maya con:

```bash
use_zed:=false
```

el launch seguía intentando localizar el paquete `zed_wrapper`.

### Solución

Editar el archivo:

```text
/Data/mars_rover/maya_2026/AutoNav_Mission_2026/src/maya_bringup/launch/maya.launch.xml
```

Buscar:

```xml
<arg name="zed_ros_params_override"
     default="$(find-pkg-share zed_wrapper)/config/profiles/halow_32mbps.yaml" />
```

Cambiar por:

```xml
<arg name="zed_ros_params_override" default="" />
```

---

## 6. Compilar sin los paquetes ZED

### Causa
Los paquetes ZED requieren dependencias que no necesitamos para ejecutar Maya en [[Capa 2 (Simulación)|simulación]].

### Solución

Ejecutar desde:

```text
/Data/mars_rover/maya_2026/AutoNav_Mission_2026
```

Comando:

```bash
colcon build --packages-ignore \
  zed_components \
  zed_wrapper \
  zed_ros2
```

---

## 7. Cargar el workspace compilado

### Causa
La terminal necesita conocer los paquetes recién compilados.

### Solución

Ejecutar desde:

```text
/Data/mars_rover/maya_2026/AutoNav_Mission_2026
```

Comando:

```bash
source install/setup.bash
```

---

## 8. Instalar Git LFS

### Causa
Los archivos STL pueden existir como punteros de Git LFS en lugar de contener los modelos reales.

### Solución

La instalación puede hacerse desde cualquier carpeta.

```bash
sudo apt install git-lfs
```

Después:

```bash
git lfs install
```

---

## 9. Descargar los archivos reales almacenados con Git LFS

### Causa
Los STL y otros archivos grandes necesitan descargarse mediante Git LFS.

### Solución

Ejecutar desde:

```text
/Data/mars_rover/maya_2026/AutoNav_Mission_2026
```

Comando:

```bash
git lfs pull
```

---

## 10. Corregir la ruta de recursos de [[Gazebo]]

### Causa
Gazebo encontraba el mundo, pero no podía resolver correctamente los [[Capa 1 (Modelo 3D)|meshes]] del paquete `maya_description`.

### Solución

Editar:

```text
/Data/mars_rover/maya_2026/AutoNav_Mission_2026/src/maya_bringup/launch/maya.launch.xml
```

Buscar:

```xml
<set_env
  name="GZ_SIM_RESOURCE_PATH"
  value="$(find-pkg-share maya_bringup)/world" />
```

Cambiar por:

```xml
<set_env
  name="GZ_SIM_RESOURCE_PATH"
  value="$(find-pkg-share maya_bringup)/world:$(find-pkg-share maya_description)/.." />
```

---

## 11. Recompilar después de modificar el launch

### Causa
Los cambios realizados en archivos instalados por el paquete deben reflejarse en el workspace compilado.

### Solución

Ejecutar desde:

```text
/Data/mars_rover/maya_2026/AutoNav_Mission_2026
```

Comando:

```bash
colcon build --packages-ignore \
  zed_components \
  zed_wrapper \
  zed_ros2
```

Después:

```bash
source install/setup.bash
```

---

## 12. Ejecutar Maya sin ZED

### Causa
La simulación debe ejecutarse sin depender de la cámara ZED física.

### Solución

Primero cargar ROS 2:

```bash
source /opt/ros/jazzy/setup.bash
```

Después cargar el workspace:

```bash
source /Data/mars_rover/maya_2026/AutoNav_Mission_2026/install/setup.bash
```

Finalmente ejecutar:

```bash
ros2 launch maya_bringup maya.launch.xml \
  use_zed:=false \
  use_depth_scan:=false
  
  o
  
ros2 launch maya_bringup maya.launch.xml use_zed:=false use_depth_scan:=false
```

Este comando se puede ejecutar desde cualquier carpeta siempre que el workspace haya sido cargado correctamente.

---
# Secuencia rápida de comandos

Ejecutar desde:

```text
/Data/mars_rover/maya_2026/AutoNav_Mission_2026
```

```bash
git submodule update --init --recursive

rm -rf build install log

source /opt/ros/jazzy/setup.bash

git lfs install
git lfs pull

colcon build --packages-ignore \
  zed_components \
  zed_wrapper \
  zed_ros2

source install/setup.bash

ros2 launch maya_bringup maya.launch.xml \
  use_zed:=false \
  use_depth_scan:=false
```

---

# Cambios manuales necesarios

## Archivo

```text
src/maya_bringup/launch/maya.launch.xml
```

### ZED

Cambiar a:

```xml
<arg name="zed_ros_params_override" default="" />
```

### Recursos de Gazebo

Cambiar a:

```xml
<set_env
  name="GZ_SIM_RESOURCE_PATH"
  value="$(find-pkg-share maya_bringup)/world:$(find-pkg-share maya_description)/.." />
```

---
# Referencias
