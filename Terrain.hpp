#pragma once

#include <random>
#include <vector>
#include <SDL2/SDL_rect.h>
#include "helpers/SdlSurface.hpp"
#include "helpers/SdlRenderer.hpp"
#include "vec2d.hpp"
#include "size2d.hpp"
#include "Food.hpp"

class Terrain
{
public:
    Terrain(SDL_Renderer&, size2d size);
    void regenerate(SDL_Renderer&) noexcept;

    void update(double dt);
    void draw(SDL_Renderer&);

    bool eatFoodOn(vec2d pos);

    const size2d& size() const noexcept { return m_size; }
private:
    SdlSurfacePtr m_sprites;
    SdlTexturePtr m_food;
    SdlTexturePtr m_terrainTex;
    size2d m_size;
    std::mt19937_64 m_randomEngine;
    double m_foodTimer;
    std::vector<Food> m_foods;
};
