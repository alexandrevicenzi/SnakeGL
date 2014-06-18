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
    void move();
    void set_direction(Direction d);
    void draw();
    void grow();
    Point head();
};