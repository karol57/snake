#pragma once

#include "Snake.hpp"

#include "helpers/SdlWindow.hpp"
#include "helpers/SdlRenderer.hpp"
#include "Terrain.hpp"

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
    SdlTexturePtr m_sprites;
    Terrain m_terrain;
    SdlTexturePtr m_terrainTex;
    Snake m_snake;
};