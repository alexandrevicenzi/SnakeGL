#ifndef BASE_H
    #define BASE_H
    #include "base.h"
#endif

#include "snake.cpp"

class Scenario
{
private:
    Point food;
    vector<Point> barriers;
    int camera_mode;

    double xEye, yEye, zEye;
    double xCenter, yCenter, zCenter;
    double xUp, yUp, zUp;

    void add_barrier();
    void change_food_pos();
    void draw_axis();
    void draw_food();
    void draw_barrier();
public:
    Snake snake;
    Scenario();
    void draw_board();
    void draw_objects();
    bool has_collision(Point p);
    void change_camera_pos();
    void set_camera();
};