#if defined(__APPLE__) || defined(MACOSX)
    #include <OpenGL/gl.h>
    #include <GLUT/glut.h>
#elif defined(WIN32)
    #include <windows.h>
    #include <GL/gl.h>
    #include <GL/glut.h>
#else
    #include <GL/gl.h>
    #include <GL/glut.h>
#endif

using namespace std;
#include <iostream>

int width  = 400,//320,
    height = 400;//240;

#if defined(DEBUG)
    #define DEBUG_MODE 1
#else
    #define DEBUG_MODE 0
#endif

#define KEY_ESCAPE 27
#define KEY_SPACE  32

int camera_mode = 0;

double xEye, yEye, zEye;
double xCenter, yCenter, zCenter;
double xUp = 0.0f, yUp = 1.0f, zUp = 0.0f;

float corRed[4] = { 1.0f, 0.0f, 0.0f, 1.0f };

void keyboard(unsigned char key, int mousePositionX, int mousePositionY)
{
    switch (key)
    {
        case KEY_ESCAPE:
            exit(0);
        break;
        case KEY_SPACE:
            camera_mode += 1;
            if (camera_mode > 1)
            {
                camera_mode = 0;
            }
            glutPostRedisplay();
        break;
    }
}

void set_camera()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective(60, 1, 0.1, 100);
    gluPerspective(45, 1, 0.1f, 50);
    //gluLookAt(xEye, yEye, zEye, xCenter, yCenter, zCenter, xUp, yUp, zUp);

    if (camera_mode == 0)
    {
        gluLookAt(0.0f, 1.0f, 20.0f, 0.0f, 0.0f, 0.0f, xUp, yUp, zUp);
    }
    else if (camera_mode == 1)
    {
        gluLookAt(0.0f, 10.0f, 15.0f, 0.0f, 0.0f, 0.0f, xUp, yUp, zUp);
    }

    glMatrixMode(GL_MODELVIEW);
}

void draw_axis()
{
    glLineWidth(1.0f);
    glNormal3f(0.0, 1.0, 0.0);
    // eixo X - Red
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(100.0f, 0.0f, 0.0f);
    glEnd();
    // eixo Y - Green
    glColor3f(0.0f, 0.8f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);
    glEnd();
    // eixo Z - Blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);
    glEnd();
}

void draw_board()
{
    glBegin(GL_POLYGON);
        glColor3f(0.0f, 1.0f, 0.0f);
        glNormal3f(0.0, 1.0, 0.0);

        glVertex3f(-5.0f, 0.0f, 5.0f);
        glVertex3f(5.0f, 0.0f,  5.0f);
        glVertex3f(5.0f, 0.0f,  -5.0f);
        glVertex3f(-5.0f, 0.0f, -5.0f);
    glEnd();
}

void draw_snake()
{
    glColor3f(0.0, 0.0, 1.0);
    //glutSolidSphere(1.0f, 100.0f, 100.0f);
    glPushMatrix();
        glTranslatef(1.0f, 0.5f, 0.0f);
        glutSolidCube(0.5f);
    glPopMatrix();

    glColor3f(0.0, 1.0, 0.4);
    glPushMatrix();
        glTranslatef(2.0f, 0.5f, 0.0f);
        glutSolidCube(0.5f);
    glPopMatrix();
}

void draw_ball()
{
    glColor3f(1.0, 0.0, 0.0);
    //glutSolidSphere(1.0f, 100.0f, 100.0f);
    glutSolidCube(1.0f);
}

void draw_cube(float xS, float yS, float zS)
{
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, corRed);
    glEnable(GL_LIGHTING);

    glPushMatrix();
        glScalef(xS,yS,zS);
        glutSolidCube(1.0f);
    glPopMatrix();

    glDisable(GL_LIGHTING);
}

void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    xEye = 20.0f;
    yEye = 20.0f;
    zEye = 20.0f;
    xCenter = 0.0f;
    yCenter = 0.0f;
    zCenter = 0.0f;

    float posLight[4] = { 5.0f, 5.0f, 10.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, posLight);
    glEnable(GL_LIGHT0);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void display()
{
    /*glViewport(0.0, 0.0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();*/

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    set_camera();

    if (DEBUG_MODE)
    {
        draw_axis();
    }

    draw_board();
    //draw_ball();
    draw_snake();


    //glFlush();
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    //glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("SnakeGL");
    glutDisplayFunc(display);
    glutIdleFunc(display);
    //glutReshapeFunc(resize);
    glutKeyboardFunc(keyboard);
    init();
    glutMainLoop();
    return 0;
}