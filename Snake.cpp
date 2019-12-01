#include "Snake.hpp"

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include <iostream>

enum Snake::DIR : uint8_t
{
    DIR_WEST,
    DIR_NORTH,
    DIR_EAST,
    DIR_SOUTH,
    DIR_LOCKED,
    DIR_START
};

constexpr static double velocity = 15; // [cells/s]
constexpr static double growTime = .5; // [s/part]
extern SDL_Texture* g_sprites;

Snake::Snake()
    : m_x{ 40 }, m_y{ 30 }
    , m_stepProgress{ 0.0 }
    , m_dir{ DIR_START }
    , m_head{ DIR_NORTH }
    , m_growTimer{ growTime }
{}

void Snake::update(double dt)
{
    if (m_dir == DIR_LOCKED || m_dir == DIR_START)
        return;

    m_growTimer -= dt;
    m_stepProgress += dt * velocity;
    if (m_stepProgress < 1.0)
        return;

    const int steps = static_cast<int>(m_stepProgress);
    m_stepProgress -= steps;

    int new_x = m_x;
    int new_y = m_y;
    switch (m_dir)
    {
        case DIR_WEST:  new_x -= steps; break;
        case DIR_EAST:  new_x += steps; break;
        case DIR_NORTH: new_y -= steps; break;
        case DIR_SOUTH: new_y += steps; break;
        default: __builtin_unreachable();
    }

    if (new_x < 0) new_x += 64;
    else if (new_x >= 64) new_x -= 64;

    if (new_y < 0) new_y += 48;
    else if (new_y >= 48) new_y -= 48;
    
    for (const SnakeBody* bodyPart = m_tail.get(); bodyPart != nullptr; bodyPart = bodyPart->tail())
    {
        if (bodyPart->x() == new_x && bodyPart->y() == new_y)
        {
            m_dir = DIR_LOCKED;
            return;
        }
    }

    if (m_growTimer <= 0.0)
    {
        m_growTimer += growTime;
        if (!m_tail)
            m_tail = std::make_unique<SnakeBody>(m_x, m_y, new_x, new_y);
        else
            m_tail->grow(m_x, m_y, new_x, new_y);
    }
    else if (m_tail)
        m_tail->advance(m_x, m_y, new_x, new_y);

    m_x = new_x;
    m_y = new_y;
}

void Snake::draw(SDL_Renderer& renderer)
{
    if (m_tail)
        m_tail->draw(renderer);

    static SDL_Rect head_sprites[] =
    {
        { 48,  0, 16, 16 },
        {  0,  0, 16, 16 },
        { 16,  0, 16, 16 },
        { 32,  0, 16, 16 },
    };
    SDL_Rect rc{ m_x * 16, m_y * 16, 16, 16 };
    SDL_RenderCopy(&renderer, g_sprites, &head_sprites[m_head], &rc);
}

void Snake::onKeyDown(SDL_Keycode key)
{
    if (m_dir == DIR_LOCKED)
        return;

    switch (key)
    {
        case SDLK_RIGHT: if (m_dir != DIR_WEST)  m_head = m_dir = DIR_EAST;  break;
        case SDLK_UP:    if (m_dir != DIR_SOUTH) m_head = m_dir = DIR_NORTH; break;
        case SDLK_LEFT:  if (m_dir != DIR_EAST)  m_head = m_dir = DIR_WEST;  break;
        case SDLK_DOWN:  if (m_dir != DIR_NORTH) m_head = m_dir = DIR_SOUTH; break;
    }
}

void Snake::reset()
{
    this->~Snake();
    new (this) Snake();
}