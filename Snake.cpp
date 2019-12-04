#include "Snake.hpp"

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

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

void wrap(int& v, int min, int max)
{
    if (v < min)
        v = max;
    else if (v >= max)
        v = min;
}

Snake::Snake()
    : m_pos{ 40, 30 }
    , m_stepProgress{ 0.0 }
    , m_dir{ DIR_NORTH }
    , m_nextDir{ DIR_START }
    , m_growTimer{ growTime }
{}

void Snake::update(double dt)
{
    if (m_nextDir == DIR_LOCKED || m_nextDir == DIR_START)
        return;

    m_growTimer -= dt;
    m_stepProgress += dt * velocity;
    if (m_stepProgress < 1.0)
        return;

    m_dir = m_nextDir;

    const int steps = static_cast<int>(m_stepProgress);
    m_stepProgress -= steps;

    vec2d newPos = m_pos;
    switch (m_dir)
    {
        case DIR_WEST:  newPos.x -= steps; break;
        case DIR_EAST:  newPos.x += steps; break;
        case DIR_NORTH: newPos.y -= steps; break;
        case DIR_SOUTH: newPos.y += steps; break;
        default: __builtin_unreachable();
    }

    wrap(newPos.x, 0, 64);
    wrap(newPos.y, 0, 48);

    for (const SnakeBody* bodyPart = m_tail.get(); bodyPart != nullptr; bodyPart = bodyPart->tail())
    {
        if (bodyPart->pos() == newPos)
        {
            m_nextDir = DIR_LOCKED;
            return;
        }
    }

    if (m_growTimer <= 0.0)
    {
        m_growTimer += growTime;
        if (!m_tail)
            m_tail = std::make_unique<SnakeBody>(m_pos, newPos);
        else
            m_tail->grow(m_pos, newPos);
    }
    else if (m_tail)
        m_tail->advance(m_pos, newPos);

    m_pos = newPos;
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
    SDL_Rect rc{ m_pos.x * 16, m_pos.y * 16, 16, 16 };
    SDL_RenderCopy(&renderer, g_sprites, &head_sprites[m_dir], &rc);
}

void Snake::onKeyDown(SDL_Keycode key)
{
    if (m_nextDir == DIR_LOCKED)
        return;

    switch (key)
    {
        case SDLK_RIGHT: if (m_dir != DIR_WEST)  m_nextDir = DIR_EAST;  break;
        case SDLK_UP:    if (m_dir != DIR_SOUTH) m_nextDir = DIR_NORTH; break;
        case SDLK_LEFT:  if (m_dir != DIR_EAST)  m_nextDir = DIR_WEST;  break;
        case SDLK_DOWN:  if (m_dir != DIR_NORTH) m_nextDir = DIR_SOUTH; break;
    }
}

void Snake::reset()
{
    this->~Snake();
    new (this) Snake();
}