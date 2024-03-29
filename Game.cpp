#include "Game.hpp"
#include "DeltaMeasurer.hpp"
#include <SDL2/SDL.h>
#include "helpers/SdlImage.hpp"

SnakeTiles* g_snakeTiles;

constexpr size2d MAP_SIZE{ 64, 24 };


Game::Game()
    : m_running{ false }
    , m_window{ SdlCreateWindow("Snake",
                                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                MAP_SIZE.width * 16, MAP_SIZE.height * 16,
                                SDL_WINDOW_SHOWN) }
    , m_renderer{ SdlCreateRenderer(m_window.get(), -1, SDL_RENDERER_ACCELERATED) }
    , m_snakeTiles{ *m_renderer, "Snake.png" }
    , m_terrain{ *m_renderer, MAP_SIZE }
    , m_snake{ m_terrain }
{
    g_snakeTiles = &m_snakeTiles;
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
    m_terrain.draw(*m_renderer);
    m_snake.draw(*m_renderer);
    SDL_RenderPresent(m_renderer.get());
}

void Game::update(double dt)
{
    m_terrain.update(dt);
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
                        m_terrain.regenerate(*m_renderer);
                        m_snake.reset();
                    }
                }
                break;
        };
    }
}
