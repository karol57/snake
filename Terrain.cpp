#include "Terrain.hpp"

#include <string>
#include <stdexcept>
#include <SDL2/SDL_surface.h>
#include "helpers/SdlImage.hpp"
using namespace std::string_literals;

constexpr auto TILE_SIZE = 16;

static
void drawTile(int x, int y, const SDL_Rect& sprite, SDL_Surface* sprites, SDL_Surface* surface)
{
    SDL_Rect rc; rc.x = x * 16; rc.y = y * 16;
    SDL_BlitSurface(sprites, &sprite, surface, &rc);
}

Terrain::Terrain(SDL_Renderer& renderer, int width, int height)
    : m_width{ width }, m_height{ height }
    , m_sprites{ ImgLoad("grass_tileset_16x16.png") }
    , m_spritesTex{ SdlCreateTextureFromSurface(&renderer, m_sprites.get()) }
{
    regenerate(renderer);
}

void Terrain::regenerate(SDL_Renderer& renderer) noexcept
{
    SdlSurfacePtr result{ SdlCreateRGBSurfaceWithFormat(m_sprites->flags, TILE_SIZE * m_width, TILE_SIZE * m_height, 0, m_sprites->format->format) };

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
            if (v < 0.9)
                drawTile(x, y, sprites[GRASS_NORMAL_1], m_sprites.get(), result.get());
            else if (v < 0.98)
                drawTile(x, y, sprites[GRASS_NORMAL_2], m_sprites.get(), result.get());
            else
                drawTile(x, y, sprites[GRASS_NORMAL_3], m_sprites.get(), result.get());
        }
    }

    m_terrainTex = SdlCreateTextureFromSurface(&renderer, result.get());
}

void Terrain::draw(SDL_Renderer& renderer)
{
    SDL_RenderCopy(&renderer, m_terrainTex.get(), nullptr, nullptr);
}