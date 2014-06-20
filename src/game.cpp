#include "game.h"


Game::Game()
{
    is_game_over = false;
    is_running = false;
    paused = false;
    scenario = new Scenario();
}

Game::~Game()
{
    delete scenario;
}

void Game::display()
{
    if (is_running)
    {
        scenario->set_camera();
        scenario->draw_objects();
    }
}

void Game::pause()
{
    paused = true;
}

void Game::start()
{
    is_game_over = false;
    paused = false;
    is_running = true;
}

void Game::stop()
{
    is_running = false;
}

void Game::reset()
{
    scenario->reset();
    is_game_over = false;
    paused = false;
    is_running = true;
}

void Game::run()
{
    if (paused || is_game_over || !is_running) return;

    ObjectType o = scenario->has_collision(scenario->snake.head());

    switch (o)
    {
        case NONE:
            scenario->snake.move();
        break;
        case FOOD:
            scenario->change_food_pos();
            scenario->snake.grow();
            scenario->snake.move();
        break;
        case BARRIER:
        case BOARD:
        case SNAKE:
            is_game_over = true;
        break;
        default:
        break;
    }
}

void Game::on_key_pressed(int key)
{
    switch (key)
    {
        case KEY_CAMERA:
            scenario->change_camera_pos();
        break;
        case KEY_PAUSE:
            pause();
        break;
        case KEY_QUIT:
            exit(0);
        break;
        case KEY_SELECT:
        break;
        case KEY_START:
            start();
        break;
        case KEY_RESET:
            reset();
        break;
        case KEY_LEFT:
            scenario->snake.set_direction(LEFT);
        break;
        case KEY_UP:
            scenario->snake.set_direction(UP);
        break;
        case KEY_RIGHT:
            scenario->snake.set_direction(RIGHT);
        break;
        case KEY_DOWN:
            scenario->snake.set_direction(DOWN);
        break;
    }
}