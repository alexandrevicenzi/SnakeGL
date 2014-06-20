#ifndef BASE_H
    #define BASE_H
    #include "base.h"
#endif

#include "scenario.cpp"

class Game
{
private:
    bool      is_game_over;
    bool      is_running;
    bool      paused;
    GLuint    textures[TEXTURE_COUNT];
    Scenario* scenario;
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