#include "SdlImage.hpp"
#include "SdlRenderer.hpp"
#include "SdlSurface.hpp"
#include "SdlWindow.hpp"
#include <stdexcept>
#include <SDL2/SDL_image.h>

using namespace std::string_literals;

SdlRendererPtr SdlCreateRenderer(SDL_Window * window, int index, Uint32 flags)
{
    SdlRendererPtr result{ SDL_CreateRenderer(window, index, flags) };
    if (!result)
        throw std::runtime_error("SDL_CreateRenderer: "s + SDL_GetError());
    return result;
}

SdlTexturePtr SdlCreateTextureFromSurface(SDL_Renderer * renderer, SDL_Surface * surface)
{
    SdlTexturePtr result{ SDL_CreateTextureFromSurface(renderer, surface) };
    if (!result)
        throw std::runtime_error("SDL_CreateTextureFromSurface: "s + SDL_GetError());
    return result;
}

SdlSurfacePtr SdlCreateRGBSurfaceWithFormat(Uint32 flags, int width, int height, int depth, Uint32 format)
{
    SdlSurfacePtr result{ SDL_CreateRGBSurfaceWithFormat(flags, width, height, depth, format) };
    if (!result)
        throw std::runtime_error("SDL_DuplicateSurface: "s + SDL_GetError());
    return result;
}

SdlWindowPtr SdlCreateWindow(const char *title, int x, int y, int w, int h, Uint32 flags)
{
    SdlWindowPtr result{ SDL_CreateWindow(title, x, y, w, h, flags) };
    if (!result)
        throw std::runtime_error("SDL_CreateWindow: "s + SDL_GetError());
    return result;
}

SDL_Surface& SdlGetWindowSurface(SDL_Window& window)
{
    SDL_Surface * const result = SDL_GetWindowSurface(&window);
    if (!result)
        throw std::runtime_error("SDL_GetWindowSurface: "s + SDL_GetError());
    return *result;
}

SdlSurfacePtr ImgLoad(const char *file)
{
    SdlSurfacePtr result{ IMG_Load(file) };
    if (!result)
        throw std::runtime_error("IMG_Load: "s + IMG_GetError());
    return result;
}