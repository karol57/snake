#pragma once

#include <memory>
#include <SDL2/SDL_surface.h>

struct SdlSurfaceDestructor { void operator()(SDL_Surface* w) { SDL_FreeSurface(w);} };
using SdlSurfacePtr = std::unique_ptr<SDL_Surface, SdlSurfaceDestructor>;

/* !!! FIXME for 2.1: why does this ask for depth? Format provides that. */
SdlSurfacePtr SdlCreateRGBSurfaceWithFormat(Uint32 flags, int width, int height, int depth, Uint32 format);