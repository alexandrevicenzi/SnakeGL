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

snakedebug:
	$(info Compiling degug mode...)
	g++ -g -o snake$(EXT) main.cpp $< $(CVERSION) $(CFLAGS) $(GLFLAGS)

snake:
	$(info Compiling...)
	g++ -o snake$(EXT) main.cpp $< $(CVERSION) $(CFLAGS) $(GLFLAGS) -DDEBUG

clean:
	$(info Removing objects...)
	rm -f snake$(EXT)
