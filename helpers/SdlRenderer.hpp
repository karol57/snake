#include <memory>
#include <SDL2/SDL_render.h>

struct SdlRendererDestructor { void operator()(SDL_Renderer* r) { SDL_DestroyRenderer(r); } };
using SdlRendererPtr = std::unique_ptr<SDL_Renderer, SdlRendererDestructor>;

struct SdlTextureDestructor { void operator()(SDL_Texture* t) { SDL_DestroyTexture(t); } };
using SdlTexturePtr = std::unique_ptr<SDL_Texture, SdlTextureDestructor>;

/**
 *  \brief Create a 2D rendering context for a window.
 *
 *  \param window The window where rendering is displayed.
 *  \param index    The index of the rendering driver to initialize, or -1 to
 *                  initialize the first one supporting the requested flags.
 *  \param flags    ::SDL_RendererFlags.
 *
 *  \return A valid rendering context or NULL if there was an error.
 *
 *  \sa SDL_CreateSoftwareRenderer()
 *  \sa SDL_GetRendererInfo()
 *  \sa SDL_DestroyRenderer()
 */
SdlRendererPtr SdlCreateRenderer(SDL_Window * window, int index, Uint32 flags);

/**
 *  \brief Create a texture from an existing surface.
 *
 *  \param renderer The renderer.
 *  \param surface The surface containing pixel data used to fill the texture.
 *
 *  \return The created texture is returned, or NULL on error.
 *
 *  \note The surface is not modified or freed by this function.
 *
 *  \sa SDL_QueryTexture()
 *  \sa SDL_DestroyTexture()
 */
SdlTexturePtr SdlCreateTextureFromSurface(SDL_Renderer * renderer, SDL_Surface * surface);