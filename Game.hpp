#pragma once

#include "Snake.hpp"

#include "helpers/SdlWindow.hpp"
#include "helpers/SdlRenderer.hpp"
#include "Terrain.hpp"
#include "SnakeTiles.hpp"

class Game
{
public:
    Game();
    int run();
protected:
    void render();
    void update(double dt);
    void pollSdl();
private:
    bool m_running;
    SdlWindowPtr m_window;
    SdlRendererPtr m_renderer;
    SnakeTiles m_snakeTiles;
    Snake m_snake;
    Terrain m_terrain;
};
