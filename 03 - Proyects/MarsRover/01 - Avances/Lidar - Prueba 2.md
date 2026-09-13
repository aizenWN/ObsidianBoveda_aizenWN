---
aliases:
tags:
  - MarsRover
  - Componente
Creado: 2026-09-11
Relacionado:
  - Avances
  - AutoNav
  - ROS2
---
# Introducción
Esta nota avarca mis segundos avances relacionados al [[Sensor Lidar|sensor Lidar]] LD19 para su presentacion de AutoNav.

---
# Desarrollo
## Ruta Propuestá de Aprendizaje
![[Pasted image 20260911125707.png]]

## Informacion Importante
>**Comando:**  [[ROS|ros2]] topic echo /scan --once

El lidar recibe tres parametros importantes por cada lectura, los cuales son:
- angle
- ranges[]
- intensities[]

`angles`:
Se refiere a los limites fisicos en cuanto a sus angulos de medicion.
Tenemos tres tipos de mediciones, los cuales son el `angle_min`, que corresponden al angulo 0° o su posición frontal / inicial, después tenemos `angles_max`que corresponderian a 6.28.., esto representa los 360°, confirmando que su escaneo es de una vuelta completa, por último tenemos `angle_increment` el cual indica cada elemento siguiente en el array `ranges[n]`, este va aumentando y corresponde a un angulo un poco mayor que el anterior.

Como adicional tenemos el dato `scan_time`el cual nos arroja un 0.10..., lo cual nos indica que escanea 10 vueltas por segundo.

`ranges`:
Ranges nos arroja las siguientes mediciones.
`range_min`= 0.0199.., esto hace referencia a que como minimo, los datos validos tienen que estar a una distancia de por lo menos 2 cm del sensor, así como `range_max`= 12.0 indica que como maximo toma en cuenta los valores tomados a 12 cm de distancia, por último tenemos delo más importante, el parametro `ranges` el cual nos indica la distancia a la que se capturo ese dato, son publicados en metros como:
- 0.277
- 0.266
- 0.259
Osea que en las mediciones devueltas, nos indica que tomo una a los 27.7 cm, otra a los 26.6 cm y otra a los 25.9 cm.

Por si solo `ranges[0]`no nos dice donde está el objeto, hasta que conoce su `angle_min + i*angle_increment`solo así ya tenemos la distancia + angulo para ubicar perfectamente su posicion.

Hay una cosa mas a tomar en cuenta, aproximadamente cada posición del arreglo avanza 0.8°.
```
ranges[0] -> 0.0°
ranges[1] -> 0.8°
ranges[2] -> 1.6°
...
ranges[6] -> 4.8°
```
Esto quiere decir que `ranges[0]` llega hasta aproximadamente `ranges[453]` para cubrir los 360°.

`intensities`:
Finalmente tenemos a intensities, el cual hace referencia que que tan fuerte fue el retorno del laser, esto servira mucho para filtrar retornos o estudiar superficies, los datos publicados son como:
- 227.0
- 229.0
- 231.0

>Tambien nos podemos encontrar con valores leidos como .nan, esto se refiere a que no se capturo un valor.

---
# Referencias
