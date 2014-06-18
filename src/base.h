#if defined(__APPLE__) || defined(MACOSX)
    #include <OpenGL/gl.h>
    #include <GLUT/glut.h>
#elif defined(_WIN32) || defined(WIN32)
    #include <windows.h>
    #include <GL/gl.h>
    #include <GL/glut.h>
#else
    #include <GL/gl.h>
    #include <GL/glut.h>
#endif

#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

// Objects can navigate from -5.0f to 5.0f.
#define BOARD_SIZE 5.25f
// Y axis difference. Ground to Objects.
#define DIFF       0.25f

enum Direction
{
    DOWN  = 1,
    UP    = 2,
    LEFT  = 3,
    RIGHT = 4,
};

enum ObjectType
{
    NONE    = 0,
    SNAKE   = 1,
    FOOD    = 2,
    BARRIER = 3,
    BOARD   = 4,
};

struct Point
{
    float x, y, z;
};