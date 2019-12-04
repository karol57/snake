#include "SnakeBody.hpp"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_pixels.h>

extern SnakeTiles* g_snakeTiles;

SnakeBody::Type SnakeBody::tailType(vec2d pos, vec2d parentPos) noexcept
{
    if (pos.x < parentPos.x)      return TAIL_EAST;
    else if (pos.x > parentPos.x) return TAIL_WEST;
    else if (pos.y < parentPos.y) return TAIL_NORTH;
    else if (pos.y > parentPos.y) return TAIL_SOUTH;
    __builtin_unreachable();
}

SnakeBody::Type SnakeBody::bodyType(vec2d childPos, vec2d pos, vec2d parentPos) noexcept
{
    const vec2d mtp = pos - parentPos;
    const vec2d mtc = pos - childPos;

    if (mtp.x == 0)
    {
        if (mtc.x < 0)
            return ((mtp.y < 0) ? BODY_SW : BODY_NW);
        else if (mtc.x == 0)
            return BODY_NS;
        /*else if (mtc.x > 0)*/
        return mtp.y < 0 ? BODY_SE : BODY_NE;
    }
    /*else if (mtp.y == 0)*/

    if (mtc.y < 0)
        return mtp.x < 0 ? BODY_SW : BODY_SE;
    else if (mtc.y == 0)
        return BODY_EW;
    /*else if (mtc.y > 0)*/
        return mtp.x < 0 ? BODY_NW : BODY_NE;
}

SnakeTiles::Tile SnakeBody::typeToTile(Type type) noexcept
{
    switch (type)
    {
        case TAIL_SOUTH: return SnakeTiles::TAIL_SOUTH;
        case TAIL_EAST:  return SnakeTiles::TAIL_EAST;
        case TAIL_NORTH: return SnakeTiles::TAIL_NORTH;
        case TAIL_WEST:  return SnakeTiles::TAIL_WEST;
        case BODY_NW:    return SnakeTiles::BODY_NW;
        case BODY_SW:    return SnakeTiles::BODY_SW;
        case BODY_SE:    return SnakeTiles::BODY_SE;
        case BODY_NE:    return SnakeTiles::BODY_NE;
        case BODY_NS:    return SnakeTiles::BODY_NS;
        case BODY_EW:    return SnakeTiles::BODY_EW;
    };
    __builtin_unreachable();
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

    g_snakeTiles->drawTile(renderer, m_pos * 16, typeToTile(m_type));
}