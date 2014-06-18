#ifndef BASE_H
    #define BASE_H
    #include "base.h"
#endif


class Snake
{
private:
    vector<Point> points;
    Direction direction;
public:
    void move();
    void set_direction();
    void draw();
};