---
aliases:
  - Configutracion Boveda git_github
tags:
  - Obsidian
  - Boveda
  - TallerRobotico
  - Completado
Creado: 2026-09-02
Relacionado:
  - Git
  - Github
  - Repositorio
  - "[[Equipo de Robótica]]"
---
# Introducción
Esta nota es una guia de configuración para conectar nuestra boveda de [[Obsidian]] hacia nuestros repositorio en [[Github]].

---
# Desarrollo
1. Lo primero que necesitamos es crear nuestra propia cuenta de **GitHub** en el siguiente enlace: https://github.com

2. Una vez que cada integrante tenga su cuenta personal, deben de avisarle a "Alex" para que este los agregue como colaboradores al repositorio privado de la boveda en **GitHub**.

3. Instalar [[Git]] en nuestra computadora.
### Usuarios Windows


### Usuarios [[Linux]]
1. ``sudo apt install git``.
2. ``sudo apt install gh``(Instalar GitHub CLI).
3. ``gh auth login`` (Iniciar sesion en GitHub):
		Elegir
		
		1. GitHub.com
		2. HTTPS
		3. Login with a web browser

4. Configurar su identidad Git (Añadir su cuenta personal):
		1. git config --global user.name "NombreIntegrante"
		2. git config --global user.email "correointegrante@ejemplo.com"
	
5. Clonar la boveda en una carpeta local:
		1. cd mi_usuario/TallerRobotico
		2. git clone https://github.com/aizenWN/ObsidianBoveda_aizenWN.git ObsidianEquipo.
6. Abrir esa carpeta en Obsidian como Boveda.
7. Activar complementos comunitarios / confiar en en los complementos y el autor de la Boveda.
8. Verificar que este activo el plugin **Git / Obsidian Git** posiblemente en último lugar de la barra lateral izquierda.

## Configuracion recomendada para plugin Git
Finalmente, revisar que las siguientes configuraciones del plugin de GIt en Obsidian sean las siguientes:
```
Pull on startup              ON
Auto commit-and-sync         10 min
Push on commit-and-sync      ON
Pull on commit-and-sync      ON
Only staged files            OFF
Squash commits               OFF
Merge strategy               Merge
Conflict strategy            Git default
Show status bar              ON
Show branch status           ON
Error notifications          ON
```

---
**Mensajes Automaticos / Auto commits**:

``Auto backup: {{date}} | User: {{hostname}} | NumFiles: {{numFiles}}``

**Mensajes Manuales / Manual commits**:

``Manual backup: {{date}} | User: {{hostname}} | NumFiles: {{numFiles}}``

---
Para acceder a ellas, ir al simbolo de la tuerquita al lado derecho del nombre de la Boveda:
![[Pasted image 20260902150051.png]]
Despues bajar hasta el final de nuestro navegador izquierdo y seleccionar **Git**:
![[Pasted image 20260902150420.png]]
Ahi ya pueden buscar las configuraciones anteriormente mencionadas.

# IMPORTANTE / README
Si se siguieron correctamente los pasos, cada vez que abres **Obsidian** se deberian descargar automaticamente los archivos actualizados de la Boveda, pero también es importante verificar que esto está funcionando correctamente.
![[Pasted image 20260902150736.png]]
El plugin de **Git** es el último de la barra lateral izquierda, al presionarlo, se abre una nueva pestaña a la derecha como esta:
![[Pasted image 20260902150823.png]]
Si nos fijamos bien, uno de sus iconos en la parte superior es una flecha apuntando hacia abajo, este es nuestro **pull**, nos actualiza todos los cambios que hay en el repositorio, aunque en teoria ya se configuro para hacerlo de manera automatica, hay que corroborarlo con ese icono al inicio.

Tambien es **IMPORTANTE** que de momento no se actualiza de manera automatica, cada cambio que haces, se guarda en tu dispositivo personal, así que se tiene que seguir los siguientes pasos para **Subir tus actualizaciones al repositorio**:

Si seguimos observando la imagen anterior, vemos que en color Rosado / Rojo dice Changes, estos son los cambios que hay dentro de la boveda, el archivo de abajo (Configu...), a su lado derecho aparece una "M", esto significa el estado en el que se encuentra ese cambio dentro del repositorio, varios indicaciones:

- M = Modified (Modificada)
- U = Untracked (No a sido registrada por Git)
- +2 = Dos cambios pendientes
- D = Deleted

El flujo correcto para guardar tus archivos es el siguiente:

1. Simbolo de "+" dentro de un circulo, este actualiza los cambios que hay en la boveda.
2. SImbolo de "palomita" (commit), este añade todas las actualizaciones al pa


---
# Referencias
