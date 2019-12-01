#pragma once

#include <SDL2/SDL_rect.h>
#include "helpers/SdlSurface.hpp"

class Terrain
{
public:
    Terrain(int width, int height);
    SdlSurfacePtr generate() noexcept;
private:
    SdlSurfacePtr m_sprites;
    int m_width, m_height;
};