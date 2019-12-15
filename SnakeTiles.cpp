#include "SnakeTiles.hpp"
#include "helpers/SdlImage.hpp"
#include <SDL2/SDL_rect.h>

SnakeTiles::SnakeTiles(SDL_Renderer& renderer, const char * atlasPath)
    : m_tiles{ SdlCreateTextureFromSurface(&renderer, ImgLoad(atlasPath).get()) }
{}

void SnakeTiles::drawTile(SDL_Renderer& renderer, vec2d pos, Tile tile) const noexcept
{
    static const SDL_Rect tilePositions[] =
    {
        {  0,   0, 16, 16 }, { 16,  0, 16, 16 }, { 32,  0, 16, 16 }, { 48,  0, 16, 16 },
        {  0,  16, 16, 16 }, { 16, 16, 16, 16 }, { 32, 16, 16, 16 }, { 48, 16, 16, 16 },
        {  0,  32, 16, 16 }, { 16, 32, 16, 16 }, { 32, 32, 16, 16 }, { 48, 32, 16, 16 },
        {  0,  48, 16, 16 }, { 16, 48, 16, 16 }
    };

    SDL_Rect rc{ pos.x, pos.y, 16, 16 };
    SDL_RenderCopy(&renderer, m_tiles.get(), &tilePositions[tile], &rc);
}