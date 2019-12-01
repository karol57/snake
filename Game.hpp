#pragma once

#include "Snake.hpp"

#include "helpers/SdlSurface.hpp"
#include "helpers/SdlWindow.hpp"
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
    SDL_Surface& m_surface;
    SdlSurfacePtr m_sprites;
    Terrain m_terrain;
    Snake m_snake;
};