ifeq ($(OS),Windows_NT)
	GLFLAGS =  -lSOIL -lglut32win -lopengl32 -lglu32
	EXT = .exe
else
	GLFLAGS = -lGL -lGLU -lglut -lSOIL
	EXT = 
endif

CFLAGS = -Wall
CVERSION = -std=c++98

all: clean snake

debug: clean snakedebug

snakedebug:
	$(info Compiling degug mode...)
	g++ -g -o snake$(EXT) main.cpp $< $(CVERSION) $(CFLAGS) $(GLFLAGS) -DDEBUG -DUSE_BUFFERS

snake:
	$(info Compiling...)
	g++ -o snake$(EXT) main.cpp $< $(CVERSION) $(CFLAGS) $(GLFLAGS) -DUSE_BUFFERS

nobuffer:
	$(info Compiling...)
	g++ -o snake$(EXT) main.cpp $< $(CVERSION) $(CFLAGS) $(GLFLAGS)

clean:
	$(info Removing objects...)
	rm -f snake$(EXT)
	rm -f snake-gcw