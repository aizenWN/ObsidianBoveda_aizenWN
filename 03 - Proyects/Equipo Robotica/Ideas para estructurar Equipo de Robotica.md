---
aliases:
tags:
  - Proyecto
  - En_curso
Creado: 2026-07-26
Relacionado:
  - Robotica
  - "[[Equipo de Robótica]]"
---
# Estructura
```
Supervisor General (Ingeniería de Sistemas)
- Hardware
- Software
- Diseño Mecánico
```

**Supervisor General**
No es el que más trabaja.
Es quien integra.
Debe asegurarse de responder preguntas como:

- ¿Todo es compatible?
- ¿Los equipos se comunican?
- ¿El software conoce las limitaciones del hardware?
- ¿El diseño mecánico permite el cableado?
- ¿El proyecto sigue la visión general?
## Responsabilidades (Ingeniería en Sistemas)
"¿La PCB tiene los conectores que necesita el software?"
"¿El modelo CAD deja espacio para el cableado?"
"¿El peso del brazo afecta la autonomía?"
"¿La interfaz entre el ESP32 y [[ROS]]2 ya está definida?"

---
# Propósito

Diseñar plataformas robóticas modulares de código abierto, inspiradas en prácticas de ingeniería profesional, para investigación, educación y competición.

No construimos productos, construimos capacidades

Formar ingenieros capaces de desarrollar sistemas robóticos profesionales mediante proyectos colaborativos.

## Filosofía del equipo
Misión
Formar ingenieros capaces de desarrollar sistemas robóticos profesionales mediante proyectos colaborativos, utilizando tecnologías empleadas en la industria y aplicándolas en investigación, educación y competición.

Los robots son el medio.
El verdadero objetivo es formar ingenieros.

---
# Objetivos

- Formar ingenieros con experiencia práctica.
- Aprender tecnologías utilizadas en la industria.
- Desarrollar plataformas robóticas modulares.
- Documentar todo el conocimiento generado.
- Crear proyectos reutilizables.
- Participar eventualmente en competiciones nacionales e internacionales.

---
# Valores

- Aprender antes que impresionar.
- Entender antes que copiar.
- Documentar antes que olvidar.
- Modular antes que rápido.
- Enseñar antes que depender.
- Compartir conocimiento antes que competir internamente.

---
# Crecimiento del Equipo
No buscar llenar plazas.
Buscar personas que aporten.

En lugar de decir
Necesitamos nueve integrantes.

Pensar
Necesitamos incorporar personas que mejoren el equipo.
El crecimiento debe ser progresivo.

---
# El proceso de integración

Yo no hablaría de "reclutamiento".
Hablaría de **Programa de Formación de Integrantes**.
Eso cambia completamente la filosofía.

La idea sería:
Interés
↓
Entrevista
↓
Periodo de integración
↓
Proyecto pequeño
↓
Evaluación mutua
↓
Ingreso al equipo

Así ambos lados pueden decidir si el equipo y la persona encajan.

---
# Perfiles Buscados
Aquí sí definiría perfiles muy claros.
## Hardware

No buscas únicamente un electrónico.
Buscas alguien que quiera convertirse en el referente técnico de Hardware.

Idealmente alguien interesado en:
- PCB
- circuitos
- sensores
- drivers
- [[Motor Electrico|motores]]
- instrumentación
- fuentes
- soldadura
- medición
No importa tanto la carrera.
Importa lo que disfruta hacer.

## Diseño Mecánico
Perfil orientado a:
- CAD
- impresión 3D
- mecanismos
- materiales
- transmisiones
- diseño estructural
Más importante que conocer SolidWorks es disfrutar diseñar mecanismos.

## Software
Persona interesada en:
- C++
- Python
- [[Linux]]
- ROS2
- Git
- visión
- [[Capa 2 (Simulación)|simulación]]
No hace falta que domine ROS.
Hace falta que quiera aprenderlo.

---
# Apartados de Evaluación
Yo evaluaría cuatro aspectos.

| Aspecto             | Importancia |
| ------------------- | ----------- |
| Compromiso          | Muy alta    |
| Curiosidad          | Muy alta    |
| Trabajo en equipo   | Alta        |
| Conocimiento actual | Media       |
Es mucho más sencillo enseñar ROS que enseñar compromiso.

---
# Preguntas para entrevista
No buscaría evaluar conocimientos como un examen.
Buscaría entender cómo piensa la persona.
Por ejemplo:

## Sobre experiencia
- ¿Qué proyecto es el que más orgulloso te hace sentir?
- ¿Qué aprendiste de ese proyecto?
- ¿Qué salió mal?
## Sobre aprendizaje
- ¿Qué tecnología te gustaría aprender este año?
- ¿Cuál fue la última herramienta que aprendiste por tu cuenta?
## Sobre trabajo en equipo
- ¿Prefieres trabajar solo o acompañado?
- ¿Cómo reaccionas cuando alguien critica tu trabajo?
## Sobre compromiso
- ¿Cuánto tiempo podrías dedicar al equipo?
- ¿Qué esperas obtener del equipo?
## Sobre documentación
- ¿Documentas tus proyectos?
- ¿Utilizas GitHub?
- ¿Has trabajado con Git?

---
# Primeros pasos para el equipo
**(Debatible)**
Todos saben usar Git y GitHub.
Todos saben documentar en Obsidian.
Todos tienen Linux configurado para el trabajo del equipo.
Todos conocen los fundamentos de ROS 2 (aunque no sean expertos).
Todos diseñan una pieza sencilla en CAD y la imprimen.
Todos entienden los conceptos básicos de electrónica y pueden leer un esquema.
Todos presentan un pequeño proyecto individual relacionado con su área.

Prohibidos los robots grandes y ambiciosos

Al final del primer semestre de este equipo, se tendrá algo más valioso, cinco personas capaces de colaborar con una base técnica común.

---
# 5 Reglas para el equipo (Debatible)
Reglas muy debatibles pero sirven de base: Aprender antes que impresionar.

1. No importa si el robot es pequeño.
	Importa que entendamos cómo funciona.

2. Documentar antes que olvidar.
	Todo conocimiento debe quedar escrito.

3. Modular antes que rápido.
	Todo debe poder reutilizarse.

4. Entender antes que copiar.
	Nunca usar una librería sin comprender qué hace.

5. Enseñar antes que depender.
	Si solo una persona sabe hacerlo, el equipo todavía no lo sabe.
---

# Documentación
Aquí creo que tienes una idea excelente.

Yo la haría obligatoria.

GitHub
↓
Código

Obsidian
↓
Conocimiento

Cada proyecto debería dejar:
- documentación
- fotos
- diagramas
- problemas encontrados
- soluciones
Así el conocimiento nunca se pierde.

---
# Modularidad
Yo la convertiría en una regla del equipo.
Cada proyecto debe intentar producir algo reutilizable.
Ejemplos.

Una PCB.
↓
Puede servir para cinco robots.

Un driver.
↓
Puede reutilizarse.

Un paquete ROS.
↓
Puede utilizarse en cualquier robot.

Una pieza CAD.
↓
Puede adaptarse.

Con el tiempo se crea una biblioteca propia.

---
# Competencias

No deberían ser el objetivo.

Deberían ser la consecuencia.

Cuando el equipo tenga suficiente nivel técnico, competir será simplemente una forma de demostrar lo aprendido.

---
# ¿Cómo lograr la independencia del equipo?

Esta es, para mí, la parte más importante de toda la conversación.

Si el equipo depende siempre del Supervisor General, el proyecto tiene un punto único de fallo. Si un día no puedes dedicarle tiempo, todo se detiene.

La meta debería ser que el equipo funcione incluso cuando tú no estés presente.

Yo propondría estos principios:

### a) Cada líder es dueño de su área

El líder de Hardware no espera instrucciones para decidir qué investigar o qué mejorar. Lo mismo ocurre con Software y Diseño Mecánico.

### b) Cada integrante tiene un proyecto propio dentro de la misión

Además de colaborar en proyectos comunes, cada persona debería tener una pequeña línea de trabajo que pueda desarrollar por iniciativa propia y luego compartir con el equipo.

### c) Las reuniones sirven para integrar, no para repartir órdenes

Una reunión ideal no es "esto es lo que tienen que hacer", sino:

- ¿Qué avanzó cada área?
- ¿Qué problemas encontraron?
- ¿Qué aprendieron?
- ¿Qué necesitan de las otras áreas?

### d) Rotar la responsabilidad de enseñar

Una práctica que me parece muy poderosa es que cada cierto tiempo un integrante prepare una sesión corta (15–30 minutos) sobre algo que aprendió: una herramienta de KiCad, un comando de Git, una librería de ROS 2, un mecanismo interesante, etc. Enseñar obliga a comprender y hace que el conocimiento se distribuya.

### e) Tomar decisiones de forma técnica

Cuando haya varias opciones, acostúmbrense a responder preguntas como:

- ¿Por qué elegimos esta solución?
- ¿Qué ventajas tiene?
- ¿Qué sacrificios implica?

Eso crea criterio de ingeniería y evita depender de la opinión de una sola persona.

### f) Aceptar propuestas desde cualquier nivel

Una buena idea no debería valer menos porque la proponga un integrante nuevo. Si alguien llega con una mejora para un módulo, se analiza técnicamente. Esa cultura hace que las personas se sientan parte del proyecto y no simples ejecutores.

---
# Mi recomendación más importante

Si tuviera que darte un solo consejo para los próximos años, sería este:

**No construyas un equipo que dependa de un líder; construye un equipo que forme nuevos líderes.**

Si dentro de cuatro años cada área tiene una persona capaz de tomar decisiones, enseñar a los nuevos integrantes y mantener vivo el conocimiento del equipo, habrás logrado algo mucho más valioso que un solo robot exitoso. Habrás creado una organización capaz de seguir creciendo, competir y evolucionar incluso cuando los fundadores ya no estén. Esa, en mi opinión, es la diferencia entre un proyecto universitario que dura un semestre y uno que puede convertirse en una referencia dentro de la universidad.

# Referencias
