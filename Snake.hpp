#pragma once

#include "SnakeBody.hpp"
#include "SDL2/SDL_keycode.h"
class SDL_Renderer;

class Snake
{
    enum DIR : uint8_t;
public:
    Snake();

    void update(double dt);
    void draw(SDL_Renderer&);
    void onKeyDown(SDL_Keycode key);

    void reset();
private:
    vec2d m_pos;
    double m_stepProgress;
    DIR m_dir;
    DIR m_nextDir;
    double m_growTimer;
    std::unique_ptr<SnakeBody> m_tail;
};