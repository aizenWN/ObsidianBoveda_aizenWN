---
aliases:
  - prolog
  - Prolog
tags:
  - Programacion
  - Completo
Creado: 2026-10-06
Relacionado:
  - Lenguaje de Programacion
---
# Introducción
En está nota abordaremos el lenguaje de programacion interpretado llamado **SWI-PROLOG**.

**SWI-PROLOG** es un lenguaje lógico orientado a un sistema experto, está está nota se expondrá su sintaxis para su utilizacion.

---
# Desarrollo
**Prolog** no se centra en decirle al programa "como hacer algo", sino en declarar hechos y reglas para que el motor pueda deducir cosas.

Veamos la sintaxis que se necesita dominar:

## 1. Hechos
La estructura general es: `predicado(argumento).`

Por ejemplo: `estudiante(juan).`
Se interpreta como *Juan es un estudiante*

>**Importante:** el punto "."
>Cada hecho o regla termina con: **.**

## 2.Predicados
El nombre `gato, perro, estudiante, etc` es el preducado.

Si tenemos:
- gato(tom).
- predicado(argumento).

Un predicado puede tener varios argumentos:
- padre(juan, pedro).

En el caso anterior tenemos 2 argumentos, esto podemos interpretarlo como **Juan es padre de Pedro**.

## 3. Consultas
Si tenemos:
- gato(tom).
- perro(firulais).

Podemos preguntar con la sintaxis `?-`

Por ejemplo:
- ?- gato(tom).

Nos daria como resultado `True`, ya que ese hecho si existe.

Si preguntamos
- ?- gato(firulais).

Nos devolveria `False`.

## 4. Variables
Una variable comienza con **`MAYUSCULAS` o con `_`**.

Por ejemplo:
- gato(tom).
- gato(michi).
- gato(luna).

Podemos preguntar algo como:
- ?- gato(X).

Y nos responde:
- X = tom ;
- X = michi ;
- X = luna.

Esta variable significaria algo como:
	"Encuentra cualquier cosa que sea un gato."

>Regla importante:
>x -> atomo
>X -> Variable

Por ejemplo utilizando los predicados anteriores.
- tom
- michi
- luna

Son átomos/argumento, mientras que:
- X
- Persona
- Animal
Son variables.

## 5. Reglas
Permiten expresar relaciones más complejas.

Por ejemplo:
- padre(juan, pedro).
- padre(juan, maria).

- abuelo(X, Y) :-
	- padre(X, Z),
	- padre(Z, Y).

La estructura `conslusion :- condiciones.
Se lee como: `conclusion`es cierta si `condiciones` son ciertas.

El símbolo `:-` se puede leer como "si".

## 6. AND
Las condiciones separadas por comas significan **AND**.
- abuelos(X, Y) :-
	- padre(X, Z),
	- padre(Z, Y).

Es: `padre(X, Z) AND padre(Z, Y)
Ambas deben cumplirse.

## 7. OR
Para expresar alternativas podemos utilizar `;`.
- animal(X) :-
	- gato(X);
	- perro(X).

Esto significa: `X es animal si X es gato o X es perro`.

## 8. Negacion.
Existe: `\+`

Por ejemplo:
- ave(X) :-
	- animal(X),
	- `\+` perro(X).


## 9. Comparaciones
Prolog tiene operadores para comparar valores.
- X = 5.
Pero `=` no significa exactamente "igual matemáticamente".

También tenemos:
- X `=:=` Y
- X `=\=` Y
- X `<` Y
- X `>` Y
- X `=<` Y
- X `>=` Y

Por ejemplo:
- mayor(X, Y) :-
	- X > Y.

Consultamos:
- ?- mayor(10, 5).

Resultado: `true`

### 9.1. Unificacion
Tenemos:
- persona(X) = persona(juan).

Resultado:
- X = juan.

Pero:
- persona(X) = animal(juan).
falla porque:
- persona != animal.

---
# Referencias
