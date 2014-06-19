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

bool is_game_over = false,
     is_running   = false;

Scenario* scenario = NULL;

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case KEY_ESCAPE:
            exit(0);
        break;
        case KEY_SPACE:
            scenario->change_camera_pos();
            glutPostRedisplay();
        break;
        case 'R':
        case 'r':
            //delete scenario;
            //scenario = new Scenario();
            scenario->reset();
            is_game_over = false;
            is_running = true;
        break;
    }
}

void keyboardSpecial(int key, int x, int y)
{
    if (!is_running || is_game_over) return;

    switch (key)
    {
        case GLUT_KEY_LEFT:
            scenario->snake.set_direction(LEFT);
            glutPostRedisplay();
        break;
        case GLUT_KEY_UP:
            scenario->snake.set_direction(UP);
            glutPostRedisplay();
        break;
        case GLUT_KEY_RIGHT:
            scenario->snake.set_direction(RIGHT);
            glutPostRedisplay();
        break;
        case GLUT_KEY_DOWN:
            scenario->snake.set_direction(DOWN);
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

    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
#ifdef USE_BUFFERS
    glEnable(GL_LIGHTING);
#else
    glDisable(GL_LIGHTING);
#endif
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    scenario = new Scenario();
}

void display()
{
    /*glViewport(width / 4, height / 4, 200, 200);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();*/

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (is_running)
    {
        scenario->set_camera();
        scenario->draw_objects();
    }

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
}

void game_over()
{
    is_game_over = true;
    cout << "┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
    cout << "███▀▀▀██┼███▀▀▀███┼███▀█▄█▀███┼██▀▀▀\n";
    cout << "██┼┼┼┼██┼██┼┼┼┼┼██┼██┼┼┼█┼┼┼██┼██┼┼┼\n";
    cout << "██┼┼┼▄▄▄┼██▄▄▄▄▄██┼██┼┼┼▀┼┼┼██┼██▀▀▀\n";
    cout << "██┼┼┼┼██┼██┼┼┼┼┼██┼██┼┼┼┼┼┼┼██┼██┼┼┼\n";
    cout << "███▄▄▄██┼██┼┼┼┼┼██┼██┼┼┼┼┼┼┼██┼██▄▄▄\n";
    cout << "┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
    cout << "███▀▀▀███┼▀███┼┼██▀┼██▀▀▀┼██▀▀▀▀██▄┼\n";
    cout << "██┼┼┼┼┼██┼┼┼██┼┼██┼┼██┼┼┼┼██┼┼┼┼┼██┼\n";
    cout << "██┼┼┼┼┼██┼┼┼██┼┼██┼┼██▀▀▀┼██▄▄▄▄▄▀▀┼\n";
    cout << "██┼┼┼┼┼██┼┼┼██┼┼█▀┼┼██┼┼┼┼██┼┼┼┼┼██┼\n";
    cout << "███▄▄▄███┼┼┼─▀█▀┼┼─┼██▄▄▄┼██┼┼┼┼┼██▄\n";
    cout << "┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
    cout << "┼┼┼┼┼┼┼┼██┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼██┼┼┼┼┼┼┼┼┼\n";
    cout << "┼┼┼┼┼┼████▄┼┼┼▄▄▄▄▄▄▄┼┼┼▄████┼┼┼┼┼┼┼\n";
    cout << "┼┼┼┼┼┼┼┼┼▀▀█▄█████████▄█▀▀┼┼┼┼┼┼┼┼┼┼\n";
    cout << "┼┼┼┼┼┼┼┼┼┼┼█████████████┼┼┼┼┼┼┼┼┼┼┼┼\n";
    cout << "┼┼┼┼┼┼┼┼┼┼┼██▀▀▀███▀▀▀██┼┼┼┼┼┼┼┼┼┼┼┼\n";
    cout << "┼┼┼┼┼┼┼┼┼┼┼██┼┼┼███┼┼┼██┼┼┼┼┼┼┼┼┼┼┼┼\n";
    cout << "┼┼┼┼┼┼┼┼┼┼┼█████▀▄▀█████┼┼┼┼┼┼┼┼┼┼┼┼\n";
    cout << "┼┼┼┼┼┼┼┼┼┼┼┼███████████┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
    cout << "┼┼┼┼┼┼┼┼▄▄▄██┼┼█▀█▀█┼┼██▄▄▄┼┼┼┼┼┼┼┼┼\n";
    cout << "┼┼┼┼┼┼┼┼▀▀██┼┼┼┼┼┼┼┼┼┼┼██▀▀┼┼┼┼┼┼┼┼┼\n";
    cout << "┼┼┼┼┼┼┼┼┼┼▀▀┼┼┼┼┼┼┼┼┼┼┼▀▀┼┼┼┼┼┼┼┼┼┼┼\n";
    cout << "┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼\n";
}

void on_timer_func()
{
    if (is_running && !is_game_over)
    {
        ObjectType o = scenario->has_collision(scenario->snake.head());

        switch (o)
        {
            case NONE:
                scenario->snake.move();
            break;
            case FOOD:
                scenario->change_food_pos();
                scenario->snake.grow();
                scenario->snake.move();
            break;
            case BARRIER:
            case BOARD:
            case SNAKE:
                game_over();
            break;
            default:
            break;
        }
    }
}

#ifndef _WIN32
    void on_timer(int sig)
    {
        on_timer_func();
        ualarm(500000, 0);
    }
#else
    void __stdcall on_timer(HWND hwnd, UINT message, UINT idTimer, DWORD dwTime)
    {
        on_timer_func();
    }
#endif

int main(int argc, char** argv)
{
#ifdef _WIN32
    SetTimer(0, 1, 500, (TIMERPROC) on_timer);
#else
    signal(SIGALRM, on_timer);
    ualarm(500000, 0);
#endif
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
#ifdef _WIN32
    KillTimer(0, 1);
#endif
    return 0;
}