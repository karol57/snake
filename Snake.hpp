#pragma once

#include "SnakeBody.hpp"
#include "SDL2/SDL_keycode.h"
class SDL_Surface;

class Snake
{
    enum DIR : uint8_t;
public:
    Snake();

    void update(double dt);
    void draw(SDL_Surface&);
    void onKeyDown(SDL_Keycode key);

    void reset();
private:
    int m_x, m_y;
    double m_stepProgress;
    DIR m_dir;
    DIR m_head;
    double m_growTimer;
    std::unique_ptr<SnakeBody> m_tail;
};