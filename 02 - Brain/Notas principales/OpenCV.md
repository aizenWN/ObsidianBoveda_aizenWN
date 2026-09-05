---
aliases:
  - opencv
  - openCV
  - Opencv
tags:
  - Programacion
  - En_curso
Creado: 2026-08-28
Relacionado:
  - Visión Computacional
  - Visión Robótica
  - "[[Python]]"
---
# Introducción
En está nota se abordara todo sobre OpenCV.
Bases, utilización, métodos, etc...

---
# Desarrollo
**OpenCV (Open Source Computer Visión Library)** es la librería de visión robótica por computadora más popular y utilizada del mundo. Es de código abierto, extremadamente rápida (escrita en C/C++) y cuenta con interfaces para Python, C++, Java y otros lenguajes.

En términos sencillos: si la programación tradicional le enseña a una computadora a procesar texto o números, **OpenCV** le enseña a una computadora a "ver" e interpretar imágenes y video.

## ¿Para que sirve?
- **Procesamiento de imágenes:** Ajustar brillo, contraste, redimensionar, rotar o aplicar filtros (desenfoque, detección de bordes, etc.).
- **Detección y reconocimiento:** Identificar rostros, objetos, colores, señales de transito o códigos QR.
- **Análisis de video:** Seguimiento de objetos en movimiento, detección de movimiento en cámaras de seguridad.
- **Reconstrucción 3D y realidad aumentada:** Calibración de cámaras y estimación de profundidad.

Para OpenCV, una imagen no es más que una matriz de números (gracias a Numpy en Python).
- Una imagen en escala de grises es una matriz de 2D donde cada pixel tiene un valor de 0 (negro) a 255 (blanco).
- Una imagen a color (RGB) es una matriz de 3D (alto x ancho x 3 canales).
- OpenCV carga por defecto las imágenes a color en formato BGR (Azul, Verde, Rojo) y no en el estándar RGB.

## Librerías
```Python
import cv2
import numpy as np
import math
from matplotlib import pyplot as plt
```

| Libreria          | Descripcion                                                                                                                                           |
| ----------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------- |
| cv2               | Liberia principal de Visión por Computadora (Procesa y manipula imagene o video en tiempo real.)                                                      |
| numpy             | Para calculo numérico y manejo de arreglos de datos (Matriz de datos gigantes como lo es una imagen de cv2)                                           |
| math              | Funciones matemáticas avanzadas (formulas geométricas, trigonométricas, etc.)                                                                         |
| matplotlib        | Paquete gigante de Python que contiene cientos de herramientas para diseño gráfico, renderizado 3D, exportación de archivos y creación de interfaces. |
| matplotlib.pyplot | Especializada en visualizar datos y graficas.                                                                                                         |

### matplotlib.pyplot as plt
```python
plt.clf()
```
Esto limpia la figura actual de matplotlib.
Como en este contexto se usa dentro de `while`, si no se limpia, cada nuevo histograma se iría dibujando encima del anterior.



## Procesar vídeo de la cámara
Para abrir y procesar el vídeo de una cámara en tiempo real en Python, necesitas dos librerías fundamentales:
- ``opencv-python (cv2)``: Es la librería principal.
- ``numpy``: OpenCV maneja cada fotograma de la cámara como una matriz numérica. NumPy es la librería que maneja estas matrices de forma ultra rápida y es un requisito obligatorio para que OpenCV funcione.

> **Nota**: math también es una librería muy utilizada dentro de OpenCV

**Código Mínimo para su Funcionamiento:**
```python
import cv2

# 0 indica la cámara predeterminada de la laptop/equipo (puedes probar 1 o 2 si tienes webcams externas)
cap = cv2.VideoCapture(0)

# Verificamos si la cámara se abrió correctamente
if not cap.isOpened():
    print("Error: No se pudo acceder a la cámara.")
    exit()

while True:
    # Capturamos cuadro por cuadro
    # ret: booleano (True si el cuadro se leyó correctamente)
    # frame: la imagen tomada como matriz NumPy
    ret, frame = cap.read()

    if not ret:
        print("Error al recibir el fotograma.")
        break

    # Mostramos el fotograma en una ventana llamada 'Camara en Vivo'
    cv2.imshow('Camara en Vivo', frame)

    # El video corre en un bucle; se interrumpe si el usuario presiona la tecla 'q'
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Liberamos el recurso de la cámara y cerramos las ventanas abiertas
cap.release()
cv2.destroyAllWindows()
```
**Conceptos Clave**
- `cv2.VideoCapture(index)`: Inicializa la captura de video. El índice 0 suele ser la cámara integrada.
- `cap.read()`: Devuelve un par ordenado `(ret, frame)`. `frame` no es más que una imagen estática capturada en ese instante de milisegundo.
- `cv2.waitKey(1)`: Detiene el flujo por 1 ms para procesar eventos de teclado y permitir que la ventana renderice la imagen. Sin este comando, la ventana se congelara.
- `cap.relase()` y `cv2.destroyAllWindows()`: Liberan el hardware de la cámara para que otras aplicaciones puedan usarla y limpian la memoria grafica.

### cv2.VideoCapture()
Originalmente planteamos el comando con un único parámetro:
`cap = cv2.VideoCapture(0)`

Pero podemos añadir un segundo parámetro llamado:
`cv2.CAP_DSHOW` **(DirectShow)**

Si solo escribimos `cap = cv2.VideoCapture(0)`, OpenCV intentara abrir la cámara con la API predeterminada del sistema. En Windows, esto suele causar dos problemas muy conocidos:

1. **Lentitud al Iniciar**: La cámara tarda entre 3 y 8 segundos en encenderse.
2. **Advertencias o congelamientos**: Muestra advertencias de controladores en la consola.

`cv2.CAP_DSHOW` fuerza a OpenCV a usar **DirectShow** (la API nativa de audio y video de Windows). Esto abre la cámara de manera instantánea y sin conflictos de controladores.

#### cap.set(cv2.CAP_PROP_FRAME)
El método `cap.set`.
`VideoCapture` no solo lee la cámara, también permite configurar sus propiedades de hardware. Con `cap.set()` se define la resolución de captura antes de empezar a procesar fotogramas:
- `cv2.CAP_PROP_FRAME_WIDTH, 320`: Ajusta el ancho a 320 píxeles.
- `cv2.CAP_PROP_FRAME_HEIGHT, 240`: Ajusta la altura a 240 píxeles.

**¿Por que una resolución tan pequeña?**
Como se pueden llegar a utilizar operaciones matemáticas pixel por pixel (rotación, translación, escalado) dentro del bucle `while True`, una resolución pequeña garantiza que la computadora procese los fotogramas a más de 30 FPS sin trabarse ni saturar la memoria del sistema.

#### `_,` src = cap.read() 
(sin espacio entre el guion bajo y coma)

En el siguiente código podemos observar lo siguiente:
```python
cap = cv2.VideoCapture(0, cv2.CAP_DSHOW)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 320)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 240)

# Verificación inicial
_, src = cap.read()
if src is None:
    print("Error al acceder a la cámara")
    exit()

dimensions = src.shape  # (filas, columnas, canales)
```
Como podemos observar en la verificación del `if src is None.
Podemos ver el comando antes mencionado de titular, el objeto `cap` es una instancia de la clase `cv2.VideoCapture`. 

El método `.read()` ya fue descrito en los conceptos clave de **Procesar vídeo de la cámara** más arriba, solo que no se interesaba guardar el primer valor `ret` por ellos simplemente se escribió como `_,`, se interesaba solamente guardar el segundo valor `frame`.
#### src.shape
En Python, cualquier imagen de OpenCV es una matriz NumPy. La propiedad `.shape` nos entrega la estructura o las dimensiones de esa matriz en forma de tupla:

> src.shape = (filas, columnas, canales)

- **Filas (`dimensions[0]`):** La altura de la imagen en píxeles (240).
- **Columnas (`dimensions[1]`):** El ancho de la imagen en píxeles (320).
- **Canales (`dimensions[2]`):** La cantidad de capas de color (3 para BGR: Azul, Verde, Rojo).

Esto nos sirve para medir él tamaño del vídeo entrante antes de iniciar el bucle y así calcular el tamaño que debía tener la ventana o la matriz de salida.

## Cargar Imagen
Para lograr cargar una imagen, hay que cuidar que la ruta en la que se encuentra no tenga caracteres especiales, así como este dentro del disco duro y no en carpetas como *OneDrive*, la manera más fácil de hacerlo es copiar la ruta de la imagen, y copearla en `imread
como cadena *raw* de la siguiente manera:

`cv2.imread(r"C:\Users\aizen\Downloads\anime-girls-short-hairs-7h.jpg")`

Agregando una "r" al inicio de la ruta, también recuerda agregar la extensión de la imagen (jpg, png, etc.).

**Código Mínimo**:
```python
imagen = cv2.imread(r"C:\Users\aizen\Downloads\anime-girls-short-hairs-7h.jpg")
 
if imagen is None:
    print("Error: No se pudo cargar la imagen.")
    exit()

cv2.imshow("Imagen de Archivo", imagen)

# o rescalar imagen

"""
imagen_pequeña = cv2.resize(imagen(800,600))
cv2.imshow("Imagen Escala Pequeña", imagen_pequeña)
"""
     
cv2.waitKey(0)
cv2.destroyAllWindows()
```

## Crear Ventana Nueva
Para crear una nueva ventana se utiliza el comando: 

`cv2.namedWindows("nameWindow")`

Pero si se ejecuta por si sola, se queda en estado de *(No Responde)*.
Ya que las ventanas graficas en cualquier Sistema Operativo funcionan mediante un **bucle de eventos**. La ventana necesita procesar constantemente eventos del sistema como:

- Redibujarse en pantalla.
- Escuchar si el usuario la arrastra o cambia de tamaño.
- Detectar clicks y entradas de teclado.

Cuando se ejecuta el comando anterior por si solo, se crea un "cascaron" de la ventana, pero si el programa no entra inmediatamente en un bucle que ejecute `cv2.waitKey()` o `cv2.imshow()`. Windows asume que el proceso se congelo porque no está respondiendo a sus peticiones graficas.

**Como Evitarlo**
Se debe de acompañar con un pequeño bucle con `cv2.waitKey()`:
```python
import cv2

# 1. Crear la ventana
cv2.namedWindow('Figura 2')

# 2. Bucle para mantener la ventana respondiendo al sistema operativo
while True:
    # waitKey(1) procesa los eventos gráficos del sistema cada milisegundo
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cv2.destroyAllWindows()
```



>**Nota**: Propiedad de configuración para namedWindows:
>
>	cv.2WINDOW_AUTOSIZE (Por defecto): La ventana se adapta al tamaño
>	cv.2WINDOW_NORMAL Permite que el usuario cambie el tamaño manual
>	cv2.WINDOW_GUI_EXPANDED Agrega una barra de herramientas superior
### Trackbars (Barras Deslizantes)
Son el componente de interfaz nativo que tiene OpenCV para interactuar con los algoritmos de forma más dinámica sin depender de librerías externas de GUI (como Tkinter o PyQt).

Las Trackbars se instancian justo después de registrar la ventana receptora:
```python
cv2.namedWindow('Figura 2')

cv2.createTrackbar('theta', 'Figura 2', 0, 700, rot)
cv2.createTrackbar('t', 'Figura 2', 0, 200, trans)
cv2.createTrackbar('s', 'Figura 2', 200, 400, scale)
```
**Desglose**:
1. **Nombre de Trackbar**: El primer parámetro es el nombre de nuestro Trackbar.
2. **Vinculo por Nombre**: El segundo parámetro (`Figura 2`) indica exactamente en que ventana se va a incrustar el control. Debe coincidir carácter por carácter con el nombre asignado en `cv.namedWindow()`.
3. Asignación de rangos enteros:
	-  OpenCV **solo admite valores enteros (`int`).
	- Para la variable `theta` (rotación), en el ejemplo se definió un rango de 0 a 700. Esto se hace para representar más de dos vueltas completas en grados (360° x 2 = 720°) o para mapear decimales.
	- Para la variable `s` (escala), se fijo un rango de 200 a 400 con un valor inicial de 200. Dado que la escala requiere flotantes, ese valor entero se divide luego en el código (`scale / 100`) para transformarlo en un factor multiplicativo (2.0).

> **Nota**: Se necesita crear una función genérica donde será almacenado nuestro trackbar, así que es obligatorio mandarle una función en su 5to parámetro.
> 
> def nada(x):
> 	pass
> 
> Lo estándar es llamarla nada, nothing, on_change y reutilizarla en todos los controles (Trackbar).

#### Flujo de lectura dentro del bucle principal
Crear el control solo dibuja el deslizador. Para extraer su valor numérico en cada fotograma del vídeo, podemos utilizar la función `cv2.getTrackbarPos()` dentro de nuestro bucle principal `while True:
```python
# Extracción de valores en tiempo real

theta = int(cv2.getTrackbarPos('theta', 'Figura 2'))
t = cv2.getTrackbarPos('t', 'Figura 2')
scale = cv2.getTrackbarPos('s', 'Figura 2')
```

**Resumen del ciclo de vida de una Trackbar en OpenCV**
- `cv2.createTrackbar(...)`: Registra e inicializa el elemento grafico en la memoria de OpenCV.
- **[[Callback]] obligatoria(`rot`, `trans`, etc.)**: Satisface el evento de cambio de estados.
- `cv2.getTrackbarPos(...)`: Consulta la posición actual del control en el fotograma activo para inyectar ese parámetro en las matrices matemáticas.



---
# Referencias
