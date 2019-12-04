#pragma once
#include <cstdint>
#include <memory>
#include "vec2d.hpp"
class SDL_Renderer;

class SnakeBody
{
public:
    enum TYPE : uint8_t;
    SnakeBody(vec2d newPos, vec2d parentPos);
    void advance(vec2d newPos, vec2d parentPos);
    void grow(vec2d newPos, vec2d parentPos);
    void draw(SDL_Renderer&);

    const SnakeBody * tail() const noexcept { return m_tail.get(); }
    const vec2d& pos() const noexcept { return m_pos; }
private:
    vec2d m_pos;
    std::unique_ptr<SnakeBody> m_tail;
    TYPE m_type;
};