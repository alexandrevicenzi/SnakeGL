#include "snake.h"


//
// Snake implementation
//
Snake::Snake()
{
    set_direction(rand() % 4);
    points.push_front(random_point());
    grow();
}

void Snake::move()
{
    points.pop_back();
    grow();
}

void Snake::set_direction(int d)
{
    if ((d == DOWN && direction == UP) ||
        (direction == DOWN && d == UP) ||
        (d == LEFT && direction == RIGHT) ||
        (direction == LEFT && d == RIGHT))
    {
        return;
    }

    direction = d;

#ifdef DEBUG
    cout << "Direction = " << direction << "\n";
#endif
}

void Snake::draw()
{
    Point h = points[0];

    glColor3f(1.0, 1.0, 0.6);
    glPushMatrix();
        glTranslatef(h.x, h.y, h.z);
        glutSolidCube(0.5f);
        //glutSolidSphere(0.5f, 100.0f, 100.0f);
    glPopMatrix();

    glColor3f(1.0, 0.7, 0.6);

    for (size_t i = 1; i < points.size(); ++i)
    {
        Point p = points.at(i);

        glPushMatrix();
            glTranslatef(p.x, p.y, p.z);
            glutSolidCube(0.5f);
        glPopMatrix();
    }
}

Point Snake::head()
{
    return points[0];
}

void Snake::grow()
{
    Point p;
    p.x = points[0].x;
    p.y = points[0].y;
    p.z = points[0].z;

    switch (direction)
    {
        case DOWN:
            p.z += 0.5f;
        break;
        case UP:
            p.z -= 0.5f;
        break;
        case LEFT:
            p.x -= 0.5f;
        break;
        case RIGHT:
            p.x += 0.5f;
        break;
    }

    points.push_front(p);
}