#include "Game.hpp"
#include "DeltaMeasurer.hpp"
#include <SDL2/SDL.h>
#include "helpers/SdlImage.hpp"

SDL_Surface* g_sprites;

Game::Game()
    : m_running{ false }
    , m_window{ SdlCreateWindow("Snake",
                                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                1024, 768,
                                SDL_WINDOW_SHOWN) }
    , m_surface{ SdlGetWindowSurface(*m_window) }
    , m_sprites{ ImgLoad("Snake.png") }
    , m_terrain{ 64, 48 }

{
    SDL_SetSurfaceBlendMode(m_sprites.get(), SDL_BLENDMODE_BLEND);

    m_terrain.generate();
    g_sprites = m_sprites.get();
}

int Game::run()
{
    m_running = true;
    
    DeltaMeasurer dm;
    do {
        printf("%7.2f FPS (%5.2f ms)\r", dm.fps(), 1000*dm.delta());
        render();
        update(dm.delta());
        pollSdl();
        dm.tick();
    } while (m_running);

    return EXIT_SUCCESS;
}

void Game::render()
{
    SDL_Rect rc{ 0, 0, 1024, 768 };
    SDL_BlitSurface(&m_terrain.surface(), &rc, &m_surface, &rc);
    m_snake.draw(m_surface);
    SDL_UpdateWindowSurface(m_window.get());
}

void Game::update(double dt)
{
    m_snake.update(dt);
}

void Game::pollSdl()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                m_running = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.repeat == 0u)
                {
                    m_snake.onKeyDown(event.key.keysym.sym);
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        m_running = false;
                    else if (event.key.keysym.sym == SDLK_r)
                    {
                        m_terrain.generate();
                        m_snake.reset();
                    }
                }
                break;
        };
    }
}