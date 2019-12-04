#include "SnakeBody.hpp"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_pixels.h>

extern SDL_Texture* g_sprites;

enum SnakeBody::TYPE : uint8_t
{
    TAIL_SOUTH, TAIL_EAST, TAIL_NORTH, TAIL_WEST,
    BODY_NW, BODY_SW, BODY_SE, BODY_NE,
    BODY_NS, BODY_EW
};

static
SnakeBody::TYPE tailType(vec2d pos, vec2d parentPos)
{
    if (pos.x < parentPos.x)      return SnakeBody::TAIL_EAST;
    else if (pos.x > parentPos.x) return SnakeBody::TAIL_WEST;
    else if (pos.y < parentPos.y) return SnakeBody::TAIL_NORTH;
    else if (pos.y > parentPos.y) return SnakeBody::TAIL_SOUTH;
    abort();
    __builtin_unreachable();
}

static
SnakeBody::TYPE bodyType(vec2d childPos, vec2d pos, vec2d parentPos)
{
    const vec2d mtp = pos - parentPos;
    const vec2d mtc = pos - childPos;

    if (mtp.x == 0)
    {
        if (mtc.x < 0)
            return ((mtp.y < 0) ? SnakeBody::BODY_SW : SnakeBody::BODY_NW);
        else if (mtc.x == 0)
            return SnakeBody::BODY_NS;
        /*else if (mtc.x > 0)*/
        return mtp.y < 0 ? SnakeBody::BODY_SE : SnakeBody::BODY_NE;
    }
    /*else if (mtp.y == 0)*/

    if (mtc.y < 0)
        return mtp.x < 0 ? SnakeBody::BODY_SW : SnakeBody::BODY_SE;
    else if (mtc.y == 0)
        return SnakeBody::BODY_EW;
    /*else if (mtc.y > 0)*/
        return mtp.x < 0 ? SnakeBody::BODY_NW : SnakeBody::BODY_NE;
}

SnakeBody::SnakeBody(vec2d newPos, vec2d parentPos)
    : m_pos{ newPos }
    , m_type{ tailType(newPos, parentPos) }
{}

void SnakeBody::advance(vec2d newPos, vec2d parentPos)
{
    if (m_tail)
    {
        m_tail->advance(m_pos, newPos);
        m_type = bodyType(m_pos, newPos, parentPos);
    }
    else
        m_type = tailType(newPos, parentPos);

    m_pos = newPos;
}
void SnakeBody::grow(vec2d newPos, vec2d parentPos) {
    if (!m_tail)
        m_tail = std::make_unique<SnakeBody>(m_pos, newPos);
    else
        m_tail->grow(m_pos, newPos);

    m_type = bodyType(m_pos, newPos, parentPos);
    m_pos = newPos;
}
void SnakeBody::draw(SDL_Renderer& renderer)
{
    if (m_tail)
        m_tail->draw(renderer);

    SDL_Rect rc{ m_pos.x * 16, m_pos.y * 16, 16, 16 };
    static SDL_Rect body_sprites[] =
    {
        {  0,  16, 16, 16 },
        { 16,  16, 16, 16 },
        { 32,  16, 16, 16 },
        { 48,  16, 16, 16 },

        {  0,  32, 16, 16 },
        { 16,  32, 16, 16 },
        { 32,  32, 16, 16 },
        { 48,  32, 16, 16 },

        {  0,  48, 16, 16 },
        { 16,  48, 16, 16 },
    };
    SDL_RenderCopy(&renderer, g_sprites, &body_sprites[m_type], &rc);
}