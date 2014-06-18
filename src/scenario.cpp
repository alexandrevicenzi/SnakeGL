#include "scenario.h"


//
// Scenario implementation
//

Scenario::Scenario()
{
    xUp = 0.0f;
    yUp = 1.0f;
    zUp = 0.0f;
    camera_mode = 0;
    change_food_pos();
    add_barrier();
}

void Scenario::add_barrier()
{
    Point p;
    p.x = (rand() % 20 / 2.0f) - 5.0f;
    p.y = DIFF;
    p.z = (rand() % 20 / 2.0f) - 5.0f;

    barriers.push_back(p);
}

void Scenario::change_food_pos()
{
    food.x = (rand() % 20 / 2.0f) - 5.0f;
    food.y = DIFF;
    food.z = (rand() % 20 / 2.0f) - 5.0f;
}
void Scenario::draw_axis()
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

void Scenario::draw_board()
{
    glBegin(GL_POLYGON);
        glColor3f(0.0f, 1.0f, 0.0f);
        glNormal3f(0.0, 1.0, 0.0);

        glVertex3f(-BOARD_SIZE, 0.0f,  BOARD_SIZE);
        glVertex3f( BOARD_SIZE, 0.0f,  BOARD_SIZE);
        glVertex3f( BOARD_SIZE, 0.0f, -BOARD_SIZE);
        glVertex3f(-BOARD_SIZE, 0.0f, -BOARD_SIZE);
    glEnd();
}

void Scenario::draw_food()
{
    glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
        glTranslatef(food.x, food.y, food.z);
        //glutSolidSphere(0.5f, 100.0f, 100.0f);
        glutSolidCube(0.5f);
    glPopMatrix();
}

void Scenario::draw_barrier()
{
    for (size_t i = 0; i < barriers.size(); ++i)
    {
        Point p = barriers.at(i);

        glColor3f(0.6, 0.4, 0.4);
        glPushMatrix();
            glTranslatef(p.x, p.y, p.z);
            glutSolidCube(0.5f);
        glPopMatrix();
    }
}

void Scenario::draw_objects()
{
#ifdef DEBUG
    draw_axis();
#endif
    draw_board();
    draw_food();
    draw_barrier();

    snake.draw();
}

bool Scenario::has_collision(Point p)
{
    if (p.x > 5.0f || p.x < -5.0f || p.z > 5.0f || p.z < -5.0f)
    {
        return true;
    }

    return false;
}

void Scenario::change_camera_pos()
{
    camera_mode += 1;

    if (camera_mode > 3)
    {
        camera_mode = 0;
    }
}

void Scenario::set_camera()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective(60, 1, 0.1, 100);
    //gluLookAt(xEye, yEye, zEye, xCenter, yCenter, zCenter, xUp, yUp, zUp);

    if (camera_mode == 0)
    {
        gluPerspective(45, 1, 0.1f, 50);
        gluLookAt(0.0f, 10.0f, 15.0f, 0.0f, 0.0f, 0.0f, xUp, yUp, zUp);
    }
    else if (camera_mode == 1)
    {
        gluPerspective(45, 1, 0.1f, 50);
        gluLookAt(0.0f, 1.0f, 20.0f, 0.0f, 0.0f, 0.0f, xUp, yUp, zUp);
    }
    else if (camera_mode == 2)
    {
        gluPerspective(45, 1, 0.1f, 50);
        gluLookAt(0.0f, -10.0f, 15.0f, 0.0f, 0.0f, 0.0f, xUp, yUp, zUp);
    }
    else if (camera_mode == 3)
    {
        gluPerspective(20, 1, 1, 100);
        gluLookAt(0.0f, 45.0f, 1.0f, 0.0f, 0.0f, 0.0f, xUp, yUp, zUp);
    }

    glMatrixMode(GL_MODELVIEW);
}