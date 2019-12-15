#pragma once

#include "Terrain.hpp"
#include "SnakeTiles.hpp"
#include "SnakeBody.hpp"
#include "SDL2/SDL_keycode.h"

class SDL_Renderer;

class Snake
{
    enum Dir : uint8_t
    {
        DIR_NORTH,
        DIR_EAST,
        DIR_SOUTH,
        DIR_WEST,
        DIR_LOCKED,
        DIR_START
    };
    static SnakeTiles::Tile dirToTile(Dir) noexcept;
public:
    Snake(Terrain& terrain);

    void update(double dt);
    void draw(SDL_Renderer&);
    void onKeyDown(SDL_Keycode key);

    void reset();
private:
    vec2d m_pos;
    double m_stepProgress;
    Dir m_dir;
    Dir m_nextDir;
    std::unique_ptr<SnakeBody> m_tail;
    Terrain& m_terrain;
};
