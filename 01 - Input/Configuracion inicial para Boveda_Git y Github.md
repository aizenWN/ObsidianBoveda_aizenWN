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
8. Ver


---
# Referencias
