#include "Game.hpp"
#include "c_raii.hpp"
#include <ctime>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std::string_literals;

int main(int argc, char* args[]) {
    srand(time(nullptr));

    if (const int ec = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER); ec < 0)
        throw std::runtime_error("SDL_Init (error " + std::to_string(ec) + "): " + SDL_GetError());
    C_RAII(SDL_Quit);

    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
        throw std::runtime_error("IMG_Init: "s + IMG_GetError());
    C_RAII(IMG_Quit);

    return Game{}.run();
}