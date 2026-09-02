---
aliases:
  - configurar vsc
  - configurar visual estudio code
  - config visual studio code
tags:
  - Programacion
  - ROS
  - Completado
Creado: 2026-06-25
Relacionado:
  - "[[Crear un Paquete de Control (Lógica) ROS]]"
  - ROS2
---
## Introducción 
Para trabajar cómodamente en [[ROS]], necesitamos instalar el IDE (Entorno de Desarrollo Integrado) llamado Visual Studio Code (VSC), en nuestro Windows, si es que eres usuario de [[Linux]] nativo, debemos investigar como sería para este entorno.

Una vez instalado, tenemos que asegurarnos que, también tenemos instalado el entorno de WSL Ubuntu 24.04 (Subsistema de Windows para Linux), el cual se explica en la [[Guía ROS2.pdf]], documento guía de látex.

Ya que tenemos ambas herramientas, abrimos nuestro VSC, lo primero que vamos a hacer es irnos al apartado de extensiones, necesitamos instalar varias para poder dejar configurado nuestro entorno y trabajar cómodamente con ROS, para abrir el apartado de extensiones podemos utilizar el comando ``Ctrl + Shift + X`` o ir a la barra del lado izquierdo y buscar el icono de un cuadrado dividido en cuatro.

Una vez entremos ahi, la primera extension que vamos a instalar es:
1. WSL (Microsoft)
Lo que nos permitirá está extension es, poder abrir nuestro VSC de manera nativa en nuestro Subsistema Linux (WSL), ¿A que me refiero?, si queremos abrir archivos de código (.cpp, .py, .yaml, etc...) que estén dentro de nuestro WSL, Linux por sus restricciones no nos lo permitirá (Por lo menos con VSC), de está manera, gracias a la extension lo podemos hacer, solo que hay un pequeñísimo inconveniente, el cual arreglaremos a continuación.

**¿Como utilizar correctamente está extension?**
No es abriendo cada archivo por individual, tenemos que abrir un WorkSpace de todos nuestros paquetes, es decir, de nuestra carpeta ``/ros2_ws``, para hacerlo, tenemos que abrir una terminal Ubuntu, una vez dentro, nos movemos a ``cd ros2_ws`` y escribimos la siguiente línea de código: ``code .``

**Que hicimos**
Acabamos de abrir VSC en nuestro WorkSpace de Linux, ahora podemos navegar con total libertad entre todos nuestros paquetes / proyectos.

**¿Es el mismo VSC que tenemos en Windows?**
No, no es exactamente el mismo, es un nuevo apartado, lo cual quiere decir, que las extensiones que tengamos en Windows, no necesariamente estarán ya instaladas en nuestro WSL.

## Extensiones
Ahora que ya tenemos listo nuestro IDE en WSL, comenzamos a instalar extensiones necesarias para trabajar más comodo en ROS, a continuación, te encontraras con un listado del nombre de las extensiones, así como su autor:

- C/C++                               (Microsoft)
- C/C++ Extensión Pack      (Microsoft)
- Error Lens                          (Alexander)
- Python                               (Microsoft)
- [[Configuración de urdf - xacro ROS 2|URDF]]                                 (smilerobotics)
- XML                                   (Red Hat)
- YAML                                 (Red Hat)

## Corregir Líneas de Error
Ahora puedes usar VSC perfectamente, pero hay un pequeño inconveniente, es posible que, aunque el código este correcto, aun así el IDE marque líneas de código erróneas en rojo o mensajes de WARNING, esto puede pasar porque no se instalaron bien las direcciones de los archivos para (includePath / IntelliSense).

Es relativamente fácil solucionarlo, primero, necesitamos continuamente el siguiente comando: ``Ctrl + Shift + P``

Se nos abra un tipo de buscador en la parte superior del IDE, lo primero que vamos a buscar sera:
``C/C++: Edit Configurations (UI)``
Una vez seleccionado, nos abrirá una nueva pestaña, buscaremos el apartado de ``Compiler path``, en el debemos de tener seleccionada la opción de ``/usr/bin/g++``. Si no está seleccionada la opción anterior, seleccionar la lista desplegable y seleccionarlo.

Ahora, volvemos a presionar el comando ``Ctrl + Shift + P``, en el buscador, vamos a buscar la siguiente opción:
``C/C++: Edit Configurations (JSON)
Se nos abrir una archivo ``.json``, el cual debería ser igual o parecido al escrito en la parte inferior de está nota, en el subíndice ``Codigo Erróneo``.

Tenemos que modificar la línea de código ``includePath`` y ``defines``, ya que está es la encargada de encontrar correctamente la ruta de los archivos, para que no nos marque error.

El código correcto está añadido en el subíndice llamado ``Codigo Corregido``, que se encuentra al final de está nota, si te fijas, prácticamente la unica configuración fue incluir la línea ``compileCommands``, quitando ``includePath``.

---
### Comandos importantes
Para volver a recargar VSC sin necesidad de cerrarlo y volverlo a abrir, podemos utilizar los siguientes comandos:

``Ctrl + Shift + D``

``C/C++: Reset IntelliSense Database

``Developer: Reload Windows``

Utilizamos siempre los 3 para asegurar que se han actualizado las configuraciones.

Tambien es super importante no olvidar que, tenemos que compilar nuevamente todos los paquetes para ROS en nuestra terminal WSL:

``colcon build`` o ``colcon build --packages-select carrito_prueba_control``

``source install/setup.bash``

**Nota:** Una ultima cosa importante a mencionar, ya que sinceramente no recuerdo exactamente como es este último punto, existe la posibilidad de que aun así te marque alguna línea de error, si es así, esto puede deberse a que, nuestro [[Capa 7 (Lógica)|nodo]] no está correctamente añadido a nuestro archivo ``CMakeLists.txt``, profundizaremos en el mediante nuestra nota [[Mi primer Nodo]].


---
### Código Erróneo
```
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "${workspaceFolder}/**"
            ],
            "defines": [],
            "compilerPath": "/usr/bin/g++",
            "cStandard": "c17",
            "cppStandard": "gnu++17",
            "intelliSenseMode": "linux-gcc-x64"
        }
    ],
    "version": 4
} 
```

---
### Código Corregido
```
{
    "configurations": [
        {
            "name": "Linux",
            "compilerPath": "/usr/bin/g++",
            "compileCommands": "${workspaceFolder}/build/compile_commands.json",
            "cStandard": "c17",
            "cppStandard": "gnu++17",
            "intelliSenseMode": "linux-gcc-x64"
        }
    ],
    "version": 4
}
```



# Referencias
