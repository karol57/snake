#pragma once
#include "helpers/SdlRenderer.hpp"
#include "vec2d.hpp"

class SnakeTiles
{
public:
    enum Tile
    {
        HEAD_NORTH, HEAD_EAST, HEAD_SOUTH, HEAD_WEST,
        TAIL_SOUTH, TAIL_EAST, TAIL_NORTH, TAIL_WEST,
        BODY_NW, BODY_SW, BODY_SE, BODY_NE, BODY_NS, BODY_EW
    };

    SnakeTiles(SDL_Renderer&, const char * atlasPath);
    void drawTile(SDL_Renderer& renderer, vec2d pos, Tile) const noexcept;
private:
    SdlTexturePtr m_tiles;
};