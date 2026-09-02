---
aliases:
  - middleware
tags:
  - Software
  - Incompleto
Creado: 2026-06-19
Relacionado:
  - ROS2
  - "[[Estructura de trabajo (ROS)]]"
  - "[[Python]]"
  - "[[C++]]"
---
## Introducción 
Middleware es software que actúa como un puente o intermediario entre diferentes aplicaciones, sistemas o componentes de software para que puedan comunicarse y compartir datos entre sí.

Se le conoce coloquialmente como el "pegamento informático". Su función principal es conectar programas que no fueron diseñados originalmente para trabajar juntos, ocultando la complejidad de las redes, los sistemas operativos y los diferentes lenguajes de programación.

## ¿Para qué sirve el Middleware? (Funciones Clave)
Conecta sistemas incompatibles: Permite que una aplicación escrita en Java se comunique con otra escrita en C++ o Python sin problemas. Simplifica el desarrollo: Los programadores no necesitan escribir código complejo de red desde cero; el middleware se encarga de enviar y recibir los datos. Garantiza la seguridad: Administra la autenticación y el cifrado de la información mientras viaja de un punto a otro. Gestión de datos: Asegura que los mensajes lleguen a su destino en el orden correcto y sin pérdidas, incluso si la conexión de red es inestable.

## Un ejemplo cotidiano fuera de la robótica
Cuando compras un boleto de avión en una aplicación de viajes (como Expedia o Despegar), esa aplicación necesita consultar los vuelos, asientos y precios de múltiples aerolíneas en tiempo real.La app de viajes no tiene esa base de datos.El middleware es el sistema oculto que toma tu solicitud, viaja a los servidores de cada aerolínea, traduce la información y la trae de vuelta a la pantalla de tu teléfono de forma unificada.¿




# Referencias
