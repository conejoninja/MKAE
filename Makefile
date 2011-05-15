# Genera los ejemplos
PROGNAME=MKAE
PROGNAME1=MKAE
PROGNAME3=GUI
PROGNAME5=VideoPlayer
PROGNAME8=SpriteCollision
PROGNAME9=LogicRenderRates
PROGNAME10=NetChat
PROGNAME11=NetChat2

# Compilador,opciones y ruta de las fuentes
CC=g++
CCFLAGS=-O3 -s -pthread
PATHSRC=src/
PATHOUT=bin/
CRM32Pro=/usr/CRM32Pro/CRM32Pro.so -I/usr/CRM32Pro
X11=-L/usr/X11/lib -lX11 -lXext

# Construccion de ejemplos
all: $(PROGNAME)
$(PROGNAME): 
	@echo
	@echo Generando $(PROGNAME1)...
	$(CC) $(CCFLAGS) src/main.cpp src/includes.cpp src/dataTypes.cpp src/Pathfinding.cpp src/GameView.cpp src/MKAELIB.cpp src/Scroll.cpp src/Shape.cpp src/Object.cpp src/Character.cpp src/Game.cpp src/Controller.cpp src/Menu.cpp -o $(PATHOUT)$(PROGNAME1) $(CRM32Pro) $(X11)

	@echo
	@echo ^__^ END OF COMPILATION  ^__^
	
clean:
	@echo clean ...
	@rm -fr bin/MKAE
	
run:
	@echo Running ...
	bin/MKAE
	
	
	
complete: 
	@echo clean ...
	@rm -fr bin/MKAE

	@echo
	@echo Generando $(PROGNAME1)...
	$(CC) $(CCFLAGS) src/main.cpp src/includes.cpp src/dataTypes.cpp src/Pathfinding.cpp src/GameView.cpp src/MKAELIB.cpp src/Scroll.cpp src/Shape.cpp src/Object.cpp src/Character.cpp src/Game.cpp src/Controller.cpp src/Menu.cpp -o $(PATHOUT)$(PROGNAME1) $(CRM32Pro) $(X11)

	@echo
	@echo ^__^ END OF COMPILATION  ^__^
	
	@echo Running ...
	bin/MKAE