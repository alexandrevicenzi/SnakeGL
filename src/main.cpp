#ifndef BASE_H
    #define BASE_H
    #include "base.h"
#endif

#include "game.cpp"


int width  = 640,
    height = 640;

bool is_game_over = false,
     is_running   = false;

Game* game = NULL;

void keyboard(unsigned char key, int x, int y)
{
    game->on_key_pressed((int)key);
    glutPostRedisplay();
}

void keyboardSpecial(int key, int x, int y)
{
    game->on_key_pressed((int)key);
    glutPostRedisplay();
}

void init()
{
    // Init GL before call this. Otherwise don't work.
    setVSync(true);

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

    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
#ifdef USE_BUFFERS
    glEnable(GL_LIGHTING);
#else
    glDisable(GL_LIGHTING);
#endif
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    load_resources();

    game = new Game();
}

void display()
{
    /*glViewport(width / 4, height / 4, 200, 200);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();*/

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    game->display();

#ifdef USE_BUFFERS
    glutSwapBuffers();
#else
    glFlush();
#endif
}

void resize(int w, int h)
{
    /*glViewport(0.0f, 0.0f, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();*/
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

#ifdef USE_BUFFERS
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
#else
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
#endif

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

    return 0;
}