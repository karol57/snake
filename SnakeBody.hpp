#pragma once
#include <cstdint>
#include <memory>
#include "vec2d.hpp"
#include "SnakeTiles.hpp"
class SDL_Renderer;

class SnakeBody
{
public:
    enum Type : uint8_t
    {
        TAIL_SOUTH, TAIL_EAST, TAIL_NORTH, TAIL_WEST,
        BODY_NW, BODY_SW, BODY_SE, BODY_NE,
        BODY_NS, BODY_EW
    };
    static Type tailType(vec2d pos, vec2d parentPos) noexcept;
    static Type bodyType(vec2d childPos, vec2d pos, vec2d parentPos) noexcept;
    static SnakeTiles::Tile typeToTile(Type) noexcept;

    SnakeBody(vec2d newPos, vec2d parentPos);
    void advance(vec2d newPos, vec2d parentPos);
    void grow(vec2d newPos, vec2d parentPos);
    void draw(SDL_Renderer&);

    const SnakeBody * tail() const noexcept { return m_tail.get(); }
    const vec2d& pos() const noexcept { return m_pos; }
private:
    vec2d m_pos;
    std::unique_ptr<SnakeBody> m_tail;
    Type m_type;
};