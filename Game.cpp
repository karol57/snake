#include "Game.hpp"
#include "DeltaMeasurer.hpp"
#include <SDL2/SDL.h>
#include "helpers/SdlImage.hpp"

SDL_Texture* g_sprites;


Game::Game()
    : m_running{ false }
    , m_window{ SdlCreateWindow("Snake",
                                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                1024, 768,
                                SDL_WINDOW_SHOWN) }
    , m_renderer{ SdlCreateRenderer(m_window.get(), -1, SDL_RENDERER_ACCELERATED) }
    , m_sprites{ SdlCreateTextureFromSurface(m_renderer.get(), ImgLoad("Snake.png").get()) }
    , m_terrain{ 64, 48 }
    , m_terrainTex{ SdlCreateTextureFromSurface(m_renderer.get(), m_terrain.generate().get()) }
{
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
    SDL_RenderClear(m_renderer.get());
    SDL_RenderCopy(m_renderer.get(), m_terrainTex.get(), nullptr, nullptr);
    m_snake.draw(*m_renderer);
    SDL_RenderPresent(m_renderer.get());
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
                        m_terrainTex = SdlCreateTextureFromSurface(m_renderer.get(), m_terrain.generate().get());
                        m_snake.reset();
                    }
                }
                break;
        };
    }
}