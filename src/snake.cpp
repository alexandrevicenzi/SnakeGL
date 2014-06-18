#include "snake.h"


//
// Snake implementation
//
void Snake::move()
{

}

void Snake::set_direction(Direction p)
{

}

void Snake::draw()
{
    glColor3f(0.0, 0.0, 1.0);
    //glutSolidSphere(1.0f, 100.0f, 100.0f);
    glPushMatrix();
        glTranslatef(0.5f, DIFF, 0.0f);
        glutSolidCube(0.5f);
    glPopMatrix();

    glColor3f(0.0, 1.0, 0.4);
    glPushMatrix();
        glTranslatef(1.0f, DIFF, 0.0f);
        glutSolidCube(0.5f);
    glPopMatrix();
}

Point Snake::head()
{

}

void Snake::grow()
{

}