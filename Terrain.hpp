#pragma once

#include <random>
#include <map>
#include <SDL2/SDL_rect.h>
#include "helpers/SdlSurface.hpp"
#include "helpers/SdlRenderer.hpp"
#include "vec2d.hpp"

class Terrain
{
public:
    Terrain(SDL_Renderer&, int width, int height);
    void regenerate(SDL_Renderer&) noexcept;

    void update(double dt);
    void draw(SDL_Renderer&);
private:
    SdlSurfacePtr m_sprites;
    SdlTexturePtr m_food;
    SdlTexturePtr m_terrainTex;
    int m_width, m_height;
    std::mt19937_64 m_randomEngine;
    double m_foodTimer;
    std::map<vec2d, SDL_Rect> m_foods;
};