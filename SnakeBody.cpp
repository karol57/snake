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
SnakeBody::TYPE tailType(int x, int y, int px, int py)
{
    if (x < px)      return SnakeBody::TAIL_EAST;
    else if (x > px) return SnakeBody::TAIL_WEST;
    else if (y < py) return SnakeBody::TAIL_NORTH;
    else if (y > py) return SnakeBody::TAIL_SOUTH;
    __builtin_unreachable();
}

static
SnakeBody::TYPE bodyType(int cx, int cy, int x, int y, int px, int py)
{
    const int mtp_x = x - px;
    const int mtp_y = y - py;

    if (mtp_x == 0)
    {
        const int mtc_x = x - cx;
        if (mtc_x < 0)
            return ((mtp_y < 0) ? SnakeBody::BODY_SW : SnakeBody::BODY_NW);
        else if (mtc_x == 0)
            return SnakeBody::BODY_NS;
        /*else if (mtc_x > 0)*/
        return mtp_y < 0 ? SnakeBody::BODY_SE : SnakeBody::BODY_NE;
    }
    /*else if (mtp_y == 0)*/
    const int mtc_y = y - cy;
    if (mtc_y < 0)
        return mtp_x < 0 ? SnakeBody::BODY_SW : SnakeBody::BODY_SE;
    else if (mtc_y == 0)
        return SnakeBody::BODY_EW;
    /*else if (mtc_y > 0)*/
        return mtp_x < 0 ? SnakeBody::BODY_NW : SnakeBody::BODY_NE;
}

SnakeBody::SnakeBody(int x, int y, int px, int py)
    : m_x{ x }, m_y{ y }
    , m_type{ tailType(x, y, px, py) }
{}

void SnakeBody::advance(int x, int y, int px, int py)
{
    if (m_tail)
    {
        m_tail->advance(m_x, m_y, x, y);
        m_type = bodyType(m_x, m_y, x, y, px, py);
    }
    else
        m_type = tailType(x, y, px, py);
    
    m_x = x;
    m_y = y;
}
void SnakeBody::grow(int x, int y, int px, int py) {
    if (!m_tail)
        m_tail = std::make_unique<SnakeBody>(m_x, m_y, x, y);
    else
        m_tail->grow(m_x, m_y, x, y);
    
    m_type = bodyType(m_x, m_y, x, y, px, py);

    m_x = x;
    m_y = y;
}
void SnakeBody::draw(SDL_Renderer& renderer)
{
    if (m_tail)
        m_tail->draw(renderer);
        
    SDL_Rect rc{ m_x * 16, m_y * 16, 16, 16 };
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