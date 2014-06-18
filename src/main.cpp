#ifndef BASE_H
    #define BASE_H
    #include "base.h"
#endif

#include "scenario.cpp"

#ifndef _WIN32
    #include <unistd.h>
    #include <signal.h>
#endif

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
    }
}

void keyboardSpecial(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_LEFT:
            scenario.snake.set_direction(LEFT);
            glutPostRedisplay();
        break;
        case GLUT_KEY_UP:
            scenario.snake.set_direction(UP);
            glutPostRedisplay();
        break;
        case GLUT_KEY_RIGHT:
            scenario.snake.set_direction(RIGHT);
            glutPostRedisplay();
        break;
        case GLUT_KEY_DOWN:
            scenario.snake.set_direction(DOWN);
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

#ifndef _WIN32
    void on_timer(int sig)
#else
    void __stdcall on_timer(HWND hwnd, UINT message, UINT idTimer, DWORD dwTime)
#endif
{
    ObjectType o = scenario.has_collision(scenario.snake.head());

    switch (o)
    {
        case NONE:
            scenario.snake.move();
        break;
        case FOOD:
            scenario.change_food_pos();
            scenario.snake.grow();
            scenario.snake.move();
        break;
        case BARRIER:
        break;
        case BOARD:
        break;
        default:
        break;
    }

#ifndef _WIN32
    alarm(1);
#endif
}

void set_timer()
{
#ifndef _WIN32
    /*struct sigaction sact;

    sigemptyset( &sact.sa_mask );
    sact.sa_flags = 0;
    sact.sa_handler = on_timer;
    sigaction( SIGALRM, &sact, NULL );
    */

    signal(SIGALRM, on_timer);
    alarm(1);
#else
    SetTimer(0, 1, 1000, (TIMERPROC) on_timer);
#endif
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
    glutSpecialFunc(keyboardSpecial);
    init();
    glutMainLoop();
#ifdef _WIN32
    KillTimer(0, 1);
#endif
    return 0;
}