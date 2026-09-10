---
aliases:
tags:
  - MarsRover
  - Componente
  - Completado
Creado: 2026-08-29
Relacionado:
  - "[[ROS]]"
---
# Introducción
Esta es la primera nota de documentación sobre mi proceso de prueba para que el [[Sensor Lidar|Lidar]] sea detectado por un computador computador correctamente.

---
# Desarrollo
Se identifico que el sensor corresponde a un LDROBOT LD19, aunque se comercializa dentro del kit D300.

1. Se identifico si Ubuntu detectaba el dispositivo mediante: `lsub`
2. El Lidar no apareció como nuevo dispositivo USB. Tampoco se creo ningún puerto serie: `ls /dev/ttyUSB*` o  `ls /dev/ttyACM*`. Ambos comandos indicaron que no existía ningún dispositivo correspondiente.
3. Revise los mensajes del kernel con: `sudo dmesg | tail -30` y posterior `sudo dmesg -w`.

Ubuntu si detectaba correctamente otros dispositivos USB, como el adaptador WI-FI, pero no mostraba ningún evento al conectar la placa **USB-UART del Lidar**.

## Pruebas Físicas
- Se detecto que uno de los cables USB tenia un falso contacto, al moverlo se reiniciaba el LIDAR.
- Se cambió por otros cables y el LIDAR mantuvo correctamente la alimentación.
- Al conectar el LD19 a la placa, el [[Diodo Led|LED]] verde comienza a parpadear rápidamente. Esto sugiere que el led rojo está únicamente relacionado con alimentación y el verde probablemente con actividad de datos UART.
- Aun conectando únicamente la placa USB-UART a la computadora, Ubuntu no muestra nada nuevo en `lsusb` ni en `dmesg`.

Por ahora el problema no parece estar en ROS, porque ni siquiera hemos llegado a la etapa donde [[Linux]] reconoce el dispositivo.

La principal sospecha está en la placa **USB-UART o en su interfaz USB**: chip conversor dañado, conector USB, líneas D+/D-, pistas soldaduras, etc.

Se podría probar esa placa en **otra computadora** o utilizar **otro adaptador USB-UART de 3.3 V** compatible con el LD19 para verificar si el Lidar puede comunicarse correctamente.

Por lo tanto no existe /dev/ttyUSB0 para poder conectar los drivers ROS 

---
# Referencias
Pagina Web Oficial [LDROBOT](https://www.ldrobot.com)
Repositorio Oficial [LDROBOT](https://github.com/ldrobotSensorTeam/ldlidar_ros2?utm_source=chatgpt.com)
