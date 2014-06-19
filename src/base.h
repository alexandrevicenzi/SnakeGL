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

#include "glut2.h"

#include <deque>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <SOIL/SOIL.h>

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

inline int random_range(int min, int max)
{
    return (rand() % (max + min)) + min;
}

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

inline void load_image(const char* filename)
{
    int width, height;
    unsigned char* image = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

    SOIL_free_image_data(image);
}

inline void draw_cube(float size, Point p, const char* filename)
{
    glPushMatrix();
        load_image(filename);
        glTranslatef(p.x, p.y, p.z);
        glutSolidCube2(size);
    glPopMatrix();
}

inline void draw_sphere(float size, Point p, const char* filename)
{
    glPushMatrix();
        load_image(filename);
        glTranslatef(p.x, p.y, p.z);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glutSolidSphere(size, 100.0f, 100.0f);
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
        //glutSolidCube(0.5f);
        //draw_cube(0.5f, p, res_id);
    glPopMatrix();
}