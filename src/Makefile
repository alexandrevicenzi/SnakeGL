ifeq ($(OS),Windows_NT)
	GLFLAGS = -lglut32win -lopengl32 -lglu32
	EXT = .exe
else
	GLFLAGS = -lGL -lGLU -lglut
	EXT = 
endif

CFLAGS = -Wall
CVERSION = -std=c++98

all: clean snake

debug: clean snakedebug

doc:
	$(info Gerando documentacao...)
	doxygen doxygen.config

snakedebug:
	$(info Compilando modo degug...)
	g++ -g -o snake$(EXT) main.cpp $< $(CVERSION) $(CFLAGS) $(GLFLAGS)

snake:
	$(info Compilando...)
	g++ -o snake$(EXT) main.cpp $< $(CVERSION) $(CFLAGS) $(GLFLAGS) -DDEBUG

clean:
	$(info Removendo objetos...)
	rm -f snake$(EXT)
	rm -f -r html/
