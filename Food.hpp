#include <SDL2/SDL_Rect.h>
#include "vec2d.hpp"

class Food
{
public:
    constexpr Food(vec2d pos, SDL_Rect texRc) noexcept
        : m_pos{pos}, m_texRc{texRc} {}

    void draw(SDL_Renderer& renderer, SDL_Texture& atlas) const;
    constexpr bool isColliding(vec2d pos) const noexcept { return m_pos == pos; }
private:
    vec2d m_pos;
    SDL_Rect m_texRc;
};