#ifndef BASE_H
    #define BASE_H
    #include "base.h"
#endif


class Snake
{
private:
    deque<Point> points;
    int direction;
public:
    Snake();
    void  move();
    void  set_direction(int d);
    bool  has_collision(Point p);
    void  draw();
    void  grow(bool back = false);
    Point head();
    Point tail();
    void  reset();
    int   size();
};