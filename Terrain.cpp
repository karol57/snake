#include "Terrain.hpp"

#include <string>
#include <stdexcept>
#include <SDL2/SDL_surface.h>
#include "helpers/SdlImage.hpp"
using namespace std::string_literals;

constexpr auto TILE_SIZE = 16;

Terrain::Terrain(int width, int height)
    : m_width{ width }, m_height{ height }
    , m_sprites{ ImgLoad("grass_tileset_16x16.png") }
    , m_surface{ SdlCreateRGBSurfaceWithFormat(m_sprites->flags, TILE_SIZE * width, TILE_SIZE * height, 0, m_sprites->format->format) }
{}

void Terrain::generate() noexcept
{
    enum TYPE
    {
        GRASS_BRIGHT_HOLE_TOP_LEFT, GRASS_TOP, GRASS_HOLE_TOP_RIGHT,
        GRASS_BRIGHT_HOLE_LEFT,                GRASS_HOLE_RIGHT,
        GRASS_BRIGHT_HOLE_BOT_LEFT, GRASS_BOT, GRASS_HOLE_BOT_RIGHT,

        GRASS_NORMAL_1,
        GRASS_NORMAL_2,
        GRASS_NORMAL_3,
    };
    const static SDL_Rect sprites[] = {
                             {  16,  0, 16, 16 }, {  32,  0, 16, 16 }, {  48,  0, 16, 16 },
                             {  16, 16, 16, 16 },                      {  48, 16, 16, 16 },
                             {  16, 32, 16, 16 }, {  32, 32, 16, 16 }, {  48, 32, 16, 16 },
        {   0, 48, 16, 16 },
        {   0, 64, 16, 16 },
        {   0, 80, 16, 16 },
    };

    for (int y = 0; y < m_height; ++y)
    {
        for (int x = 0; x < m_width; ++x)
        {
            const double v = rand() / (double)RAND_MAX;
            if (v < 0.8)
                drawTile(x, y, sprites[GRASS_NORMAL_1]);
            else if (v < 0.9)
                drawTile(x, y, sprites[GRASS_NORMAL_2]);
            else
                drawTile(x, y, sprites[GRASS_NORMAL_3]);
        }
    }
}

void Terrain::drawTile(int x, int y, const SDL_Rect& sprite)
{
    SDL_Rect rc; rc.x = x * 16; rc.y = y * 16;
    SDL_BlitSurface(m_sprites.get(), &sprite, m_surface.get(), &rc);
}