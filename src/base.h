#if defined(__APPLE__) || defined(MACOSX)
    #include <OpenGL/gl.h>
    #include <OpenGL/glx.h>
    #include <GLUT/glut.h>
#elif defined(_WIN32) || defined(WIN32)
    #include <windows.h>
    #include <GL/gl.h>
    #include <GL/glut.h>
    #include <GL/glext.h>
#else
    #include <GL/gl.h>
    #include <GL/glx.h>
    #include <GL/glut.h>
#endif

#include "glut_shapes.h"

#include <deque>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>

#include <SOIL/SOIL.h>

using namespace std;

// https://github.com/AdrienHerubel/imgui/blob/master/lib/glew/glew.c
#if defined(_WIN32)
    #define glewGetProcAddress(name) wglGetProcAddress((LPCSTR)name)
#elif defined(__APPLE__)
    #define glewGetProcAddress(name) NSGLGetProcAddress(name)
#elif defined(__sgi) || defined(__sun)
    #define glewGetProcAddress(name) dlGetProcAddress(name)
#else /* __linux */
    #define glewGetProcAddress(name) (*glXGetProcAddressARB)(name)
#endif

// Objects can navigate from -5.0f to 5.0f.
#define BOARD_SIZE      5.25f
// Y axis difference. Ground to Objects.
#define GROUND_DIFF     0.25f

#define GROUND_TEXTURE  0
#define FOOD_TEXTURE    1
#define BARRIER_TEXTURE 2
#define SNAKE_TEXTURE   3
#define MENU_TEXTURE    4
#define BRICK_TEXTURE   5

#define TEXTURE_COUNT   6

/* Key mappings. */
#define KEY_CAMERA      32  // space
#define KEY_PAUSE       112 // p
#define KEY_QUIT        27  // esc
#define KEY_SELECT      13  // enter
#define KEY_START       115 // s
#define KEY_STOP        113 // q
#define KEY_RESET       114 // r
#define KEY_UP          GLUT_KEY_UP
#define KEY_DOWN        GLUT_KEY_DOWN
#define KEY_RIGHT       GLUT_KEY_RIGHT
#define KEY_LEFT        GLUT_KEY_LEFT

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

enum Level
{
    VIRGIN       = 1,
    JEDI         = 2,
    ASIAN        = 3,
    CHUCK_NORRIS = 4,
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
        glut2SolidCube(size);
    glPopMatrix();

    disable_2D_texture();
}

inline void draw_sphere(float size, Point p, int res_id)
{
    enable_2D_texture();

    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, textures[res_id]);
        glTranslatef(p.x, p.y, p.z);

        glut2SolidSphere(size, 100.0f, 100.0f);
    glPopMatrix();

    disable_2D_texture();
}

inline void load_resources()
{
    glGenTextures(TEXTURE_COUNT, textures);

    glBindTexture(GL_TEXTURE_2D, textures[GROUND_TEXTURE]);
    load_image("./resources/grass.png");

    glBindTexture(GL_TEXTURE_2D, textures[FOOD_TEXTURE]);
    load_image("./resources/apple.png");

    glBindTexture(GL_TEXTURE_2D, textures[BARRIER_TEXTURE]);
    load_image("./resources/box.png");

    glBindTexture(GL_TEXTURE_2D, textures[SNAKE_TEXTURE]);
    load_image("./resources/snake.png");

    glBindTexture(GL_TEXTURE_2D, textures[MENU_TEXTURE]);
    load_image("./resources/menu.png");

    glBindTexture(GL_TEXTURE_2D, textures[BRICK_TEXTURE]);
    load_image("./resources/brick.png");
}

inline void unload_resources()
{
    glDeleteTextures(TEXTURE_COUNT, textures);
}

inline void draw_text(string s, Point p, float r, float g, float b)
{
    glDisable(GL_LIGHTING);

    int len, i;
    glColor3f(r, g, b);
    glRasterPos3f(p.x, p.y,p.z);
    len = (int) s.length();

    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
    }

    glEnable(GL_LIGHTING);
}

/*
    http://www.dbfinteractive.com/forum/index.php?topic=5998.0
*/
static void setVSync(bool sync)
{
#ifdef _WIN32
    typedef BOOL (APIENTRY *PFNWGLSWAPINTERVALPROC)( int );
    PFNWGLSWAPINTERVALPROC wglSwapIntervalEXT = 0;

    const char *extensions = (char*)glGetString( GL_EXTENSIONS );

    if( strstr( extensions, "WGL_EXT_swap_control" ) == 0 )
    {
        return;
    }
    else
    {
        wglSwapIntervalEXT = (PFNWGLSWAPINTERVALPROC) wglGetProcAddress( "wglSwapIntervalEXT" );

        if(wglSwapIntervalEXT)
        {
            wglSwapIntervalEXT(sync);
        }
    }
#else
    glewGetProcAddress((const GLubyte*)"glXSwapIntervalEXT");
    PFNGLXSWAPINTERVALEXTPROC glXSwapIntervalEXT = 0;

    GLboolean r = GL_FALSE;
    r = ((glXSwapIntervalEXT = (PFNGLXSWAPINTERVALEXTPROC)glewGetProcAddress((const GLubyte*)"glXSwapIntervalEXT")) == NULL) || r;

    Display *dpy = glXGetCurrentDisplay();
    GLXDrawable drawable = glXGetCurrentDrawable();

    // TODO: not working.
    if (r && glXSwapIntervalEXT)
    {
        glXSwapIntervalEXT(dpy, drawable, (int)sync);
    }
#endif
}