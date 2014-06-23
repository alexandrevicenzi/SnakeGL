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
    Camera camera;
    void draw_axis();
    void draw_food();
    void draw_barrier();
    void draw_background();
public:
    int camera_mode;
    float m;
    float a;
    Snake snake;
    Scenario();
    void add_barrier();
    void change_food_pos();
    void draw_board();
    void draw_objects();
    void change_camera_pos();
    void set_camera();
    void reset();
    ObjectType has_collision(Point p);
};