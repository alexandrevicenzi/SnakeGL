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

        if (is_game_over)
        {
            Point p;
            p.x = -1.25f;
            p.y = 0.5f;
            p.z = 0.0f;
            draw_text("GAME OVER", p, 1.0f, 0.0f, 0.0f);
        }
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
            if (scenario->snake.size() % 6 == 0)
            {
                scenario->add_barrier();
            }
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
            if (!is_running) return;
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
            if (!is_running) return;
            scenario->snake.set_direction(LEFT);
        break;
        case KEY_UP:
            if (!is_running) return;
            scenario->snake.set_direction(UP);
        break;
        case KEY_RIGHT:
            if (!is_running) return;
            scenario->snake.set_direction(RIGHT);
        break;
        case KEY_DOWN:
            if (!is_running) return;
            scenario->snake.set_direction(DOWN);
        break;
    }
}