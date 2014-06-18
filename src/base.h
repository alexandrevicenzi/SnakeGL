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

#include <deque>
#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

// Objects can navigate from -5.0f to 5.0f.
#define BOARD_SIZE  5.25f
// Y axis difference. Ground to Objects.
#define GROUND_DIFF 0.25f

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

inline float random_pos()
{
    return (rand() % 20 / 2.0f) - 5.0f;
}

inline Point random_point()
{
    Point p;
    p.x = random_pos();
    p.y = GROUND_DIFF;
    p.z = random_pos();

#ifdef DEBUG
    cout << "x = " << p.x << " ";
    cout << "y = " << p.y << " ";
    cout << "z = " << p.z << "\n";
#endif

    return p;
}