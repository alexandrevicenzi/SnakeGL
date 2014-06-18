#ifndef BASE_H
    #define BASE_H
    #include "base.h"
#endif

#include "scenario.cpp"


#include <unistd.h>
#include <signal.h>

// Key mappings.
#define KEY_ESCAPE 27
#define KEY_SPACE  32


int width  = 400,//320,
    height = 400;//240;

Scenario scenario;

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case KEY_ESCAPE:
            exit(0);
        break;
        case KEY_SPACE:
            scenario.change_camera_pos();
            glutPostRedisplay();
        break;
        case GLUT_KEY_LEFT:
            glutPostRedisplay();
        break;
        case GLUT_KEY_UP:
            glutPostRedisplay();
        break;
        case GLUT_KEY_RIGHT:
            glutPostRedisplay();
        break;
        case GLUT_KEY_DOWN:
            glutPostRedisplay();
        break;
    }
}

void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    float pos_light[4] = { 5.0f, 5.0f, 10.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, pos_light);
    glEnable(GL_LIGHT0);

#ifdef DEBUG
    glDisable(GL_CULL_FACE);
#else
    glEnable(GL_CULL_FACE);
#endif

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void display()
{
    /*glViewport(width / 4, height / 4, 200, 200);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();*/

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scenario.set_camera();
    scenario.draw_objects();

    //glFlush();
    glutSwapBuffers();
}

void resize(int w, int h)
{
    /*glViewport(0.0f, 0.0f, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();*/
}

void on_timer(int sig)
{
    scenario.snake.move();
    alarm(1);
}

void set_timer()
{
    /*struct sigaction sact;

    sigemptyset( &sact.sa_mask );
    sact.sa_flags = 0;
    sact.sa_handler = on_timer;
    sigaction( SIGALRM, &sact, NULL );
    */

    signal(SIGALRM, on_timer);
    alarm(1);
}

int main(int argc, char** argv)
{
    set_timer();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    //glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("SnakeGL");
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyboard);
    //glutSpecialFunc(keyboard);
    init();
    glutMainLoop();
    return 0;
}