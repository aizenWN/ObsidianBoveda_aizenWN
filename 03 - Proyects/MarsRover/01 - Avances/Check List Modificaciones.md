---
aliases:
tags:
  - MarsRover
Creado: 2026-10-10
Relacionado:
  - ROS2
  - Programacion
  - Simulacion
---
# Introducción
Aquí existira una Check List de todas las modificaciones hechas en el WorkSpace de Maya para su confirmación oficial.

---
# Desarrollo
- [ ] `<input type="checkbox">`
- [q] `<input type="checkbox" checked>`

| Archivo                                       | Modificacion                                                                                                | Linea Aproximada                                                                                  | Check List              |
| --------------------------------------------- | ----------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------- | ----------------------- |
| sensors_frame.xacro                           | Confirmar cambio de nombre para frame lidar                                                                 | 19 - 49                                                                                           | <input type="checkbox"> |
| mobile_base.xacro                             | Cambio de meshes a la optimizadas                                                                           | Todas las rutas del modelado (visual/colission)                                                   | <input type="checkbox"> |
| maya.launch.xml                               | 1.- Modo Hardware para joint state publisher y <let name="sim" value="false"/> let name="sim" value="false" | 28 - 65                                                                                           |                         |
| maya.launch.xml                               | 2.- Modo Simulacion (Comentado)                                                                             | 70 - 84                                                                                           |                         |
| maya.launch.xml (Importante para SLAM y NAV2) | 3.- use_sim_time value "false" para no utilizar el tiempo simulado de gazebo, si se utiliza gazebo "true".  | Multiples archivos, (23-25 time aprox). Buscar entre varios archivos (creo que todos en bringup). |                         |
| random_world.sdf                              | max_step_size = 0.01 de 0.05                                                                                | 13                                                                                                |                         |
| gazebo_bringe_yaml                            | colocar nombre de frame_id a /scan                                                                          | 37                                                                                                |                         |
|                                               |                                                                                                             |                                                                                                   |                         |


---
# Referencias
