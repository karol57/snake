#pragma once

#include <SDL2/SDL_rect.h>
#include "helpers/SdlSurface.hpp"
#include "helpers/SdlRenderer.hpp"

class Terrain
{
public:
    Terrain(SDL_Renderer&, int width, int height);
    void regenerate(SDL_Renderer&) noexcept;

    void draw(SDL_Renderer&);
private:
    SdlSurfacePtr m_sprites;
    SdlTexturePtr m_spritesTex;
    SdlTexturePtr m_terrainTex;
    int m_width, m_height;
};