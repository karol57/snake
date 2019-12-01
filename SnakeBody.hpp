#pragma once
#include <cstdint>
#include <memory>
class SDL_Renderer;

class SnakeBody
{
public:
    enum TYPE : uint8_t;
    SnakeBody(int x, int y, int px, int py);
    void advance(int x, int y, int px, int py);
    void grow(int x, int y, int px, int py);
    void draw(SDL_Renderer&);

    const SnakeBody * tail() const noexcept { return m_tail.get(); }
    int x() const noexcept { return m_x; }
    int y() const noexcept { return m_y; }
private:
    int m_x, m_y;
    std::unique_ptr<SnakeBody> m_tail;
    TYPE m_type;
};