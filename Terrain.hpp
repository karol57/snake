#pragma once

#include <SDL2/SDL_rect.h>
#include "helpers/SdlSurface.hpp"

class Terrain
{
public:
    Terrain(int width, int height);

    void generate() noexcept;
    SDL_Surface& surface() const { return *m_surface; }
protected:
    void drawTile(int x, int y, const SDL_Rect& sprite);
private:
    SdlSurfacePtr m_sprites;
    SdlSurfacePtr m_surface;

    int m_width, m_height;
};