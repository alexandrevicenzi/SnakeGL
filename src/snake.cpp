#include "snake.h"


//
// Snake implementation
//
Snake::Snake()
{
    direction = rand() % 4;
    points.push_front(random_point());
    grow();
}

void Snake::move()
{
    points.pop_back();
    grow();
}

void Snake::set_direction(Direction d)
{
    direction = d;

#ifdef DEBUG
    cout << "Direction = " << direction << "\n";
#endif
}

void Snake::draw()
{
    Point h = points[0];

    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
        glTranslatef(h.x, h.y, h.z);
        glutSolidCube(0.5f);
        //glutSolidSphere(0.5f, 100.0f, 100.0f);
    glPopMatrix();

    glColor3f(0.0, 1.0, 0.4);

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
    p.x = points[0].x + 0.5f;
    p.y = points[0].y;
    p.z = points[0].z;

    switch (direction)
    {
        case DOWN:

        break;
        case UP:

        break;
        case LEFT:

        break;
        case RIGHT:

        break;
    }

    points.push_front(p);
}