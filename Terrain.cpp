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

Terrain::Terrain(SDL_Renderer& renderer, size2d size)
    : m_size{ size }
    , m_sprites{ ImgLoad("grass_tileset_16x16.png") }
    , m_food{ SdlCreateTextureFromSurface(&renderer, ImgLoad("Food.png").get()) }
    , m_randomEngine{ std::random_device()() }
    , m_foodTimer{ 0 }
{
    regenerate(renderer);
}

void Terrain::regenerate(SDL_Renderer& renderer) noexcept
{
    const auto sizeInTiles = m_size * TILE_SIZE;
    SdlSurfacePtr result{ SdlCreateRGBSurfaceWithFormat(m_sprites->flags, sizeInTiles.width, sizeInTiles.height, 0,
        m_sprites->format->format) };

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

    for (int y = 0; y < m_size.height; ++y)
    {
        for (int x = 0; x < m_size.width; ++x)
        {
            const double v = std::uniform_real_distribution{0.0, 1.0}(m_randomEngine);
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

#include <iostream>
void Terrain::update(double dt)
{
    m_foodTimer -= dt;
    if (m_foodTimer <= 0)
    {
        if (m_foods.size() >= m_size.area())
            return;

        m_foodTimer += std::uniform_real_distribution{0.5, 4.0}(m_randomEngine);

        std::map<vec2d, SDL_Rect>::iterator it;
        std::uniform_int_distribution x_dist{ 0, m_size.width - 1 };
        std::uniform_int_distribution y_dist{ 0, m_size.height - 1 };
        int x, y;
        int i = 0;
        do
        {
            x = x_dist(m_randomEngine); x_dist.reset();
            y = y_dist(m_randomEngine); y_dist.reset();
            it = m_foods.find({ x, y });
            ++i;
        } while (it != m_foods.end());

        const int icon = std::uniform_int_distribution{ 0, 63 }(m_randomEngine);
        const vec2d iconPos{ icon % 8, icon / 8 };
        const vec2d iconTilePos = iconPos * TILE_SIZE;
        m_foods.insert(std::make_pair<vec2d, SDL_Rect>(vec2d{ iconPos }, { iconTilePos.x, iconTilePos.y, 16, 16 }));
    }
}

void Terrain::draw(SDL_Renderer& renderer)
{
    SDL_RenderCopy(&renderer, m_terrainTex.get(), nullptr, nullptr);
    for (const auto& [pos, srcRc] : m_foods)
    {
        SDL_Rect dstRc{ pos.x * 16, pos.y * 16, 16, 16 };
        SDL_RenderCopy(&renderer, m_food.get(), &srcRc, &dstRc);
    }
}