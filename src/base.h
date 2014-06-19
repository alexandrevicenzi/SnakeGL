#if defined(__APPLE__) || defined(MACOSX)
    #include <OpenGL/gl.h>
    #include <GLUT/glut.h>
#elif defined(_WIN32) || defined(WIN32)
    #include <windows.h>
    #include <GL/gl.h>
    #include <GL/glut.h>
    #include <GL/glext.h>
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

#define GROUND_TEXTURE  0
#define FOOD_TEXTURE    1
#define BARRIER_TEXTURE 2
#define SNAKE_TEXTURE   3

#define TEXTURE_COUNT 4


GLuint textures[TEXTURE_COUNT];

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

inline void enable_2D_texture()
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

    GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat high_shininess[] = { 0.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
 
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, high_shininess);

    glEnable(GL_TEXTURE_2D);
}

inline void disable_2D_texture()
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

    GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat high_shininess[] = { 100.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
 
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, high_shininess);

    glDisable(GL_TEXTURE_2D);
}

inline void draw_cube(float size, Point p, int res_id)
{
    enable_2D_texture();

    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, textures[res_id]);
        glTranslatef(p.x, p.y, p.z);
        glutSolidCube2(size);
    glPopMatrix();

    disable_2D_texture();
}

inline void draw_sphere(float size, Point p, int res_id)
{
    enable_2D_texture();

    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, textures[res_id]);
        glTranslatef(p.x, p.y, p.z);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        glutSolidSphere(size, 100.0f, 100.0f);
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
    glPopMatrix();

    disable_2D_texture();
}

void load_texture(/*int res_id, */const char* filename, int index)
{
    int width, height;
    unsigned char* image;

    //glActiveTexture(res_id);
    glBindTexture(GL_TEXTURE_2D, textures[index]);

    image = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);
}

void load_resources()
{
    glGenTextures(TEXTURE_COUNT, textures);

    load_texture(/*GL_TEXTURE0, */"./resources/grass.png", GROUND_TEXTURE);
    load_texture(/*GL_TEXTURE1, */"./resources/apple.png", FOOD_TEXTURE);
    load_texture(/*GL_TEXTURE2, */"./resources/box.png",   BARRIER_TEXTURE);
    load_texture(/*GL_TEXTURE3, */"./resources/snake.png", SNAKE_TEXTURE);
}

void unload_resources()
{
    glDeleteTextures(TEXTURE_COUNT, textures);
}