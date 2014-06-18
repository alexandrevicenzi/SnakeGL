#include "snake.h"


//
// Snake implementation
//
Snake::Snake()
{
    reset();
}

void Snake::reset()
{
    points.clear();
    int d = (rand() % 4) + 1;
    set_direction(d);
    points.push_front(random_point());
    grow();
}

void Snake::move()
{
#ifdef DEBUG
    cout << "walk\n";
#endif
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
    cout << "direction = " << direction << "\n";
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

Point Snake::tail()
{
    return points[points.size() - 1];
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

bool Snake::has_collision(Point p)
{
    // Skip head. It's the same point.
    for (size_t i = 1; i < points.size(); ++i)
    {
        Point b = points.at(i);

        if (p.x == b.x && p.z == b.z)
        {
            return BARRIER;
        }
    }

    return false;
}