#ifndef BASE_H
    #define BASE_H
    #include "base.h"
#endif

#include "scenario.cpp"
#include <ctime>
#include <cstdio>

class Game
{
private:
    bool      is_game_over;
    bool      is_running;
    bool      paused;
    bool      ate;
    bool      key_pressed;
    int       m, m2;
    int       frameCount;
    int       currentTime;
    int       previousTime;
    int       score;
    float     fps;
    Scenario* scenario;
    bool      wait();
    bool      wait2();
    void      calculateFPS();
public:
    Game();
    ~Game();
    void display();
    void pause();
    void start();
    void stop();
    void reset();
    void run();
    void on_key_pressed(int key);
};