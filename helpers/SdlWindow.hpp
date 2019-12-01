#include <memory>
#include "SDL2/SDL_video.h"

struct SdlWindowDestructor { void operator()(SDL_Window* w) { SDL_DestroyWindow(w);} };
using SdlWindowPtr = std::unique_ptr<SDL_Window, SdlWindowDestructor>;

/**
 *  \brief Create a window with the specified position, dimensions, and flags.
 *
 *  \param title The title of the window, in UTF-8 encoding.
 *  \param x     The x position of the window, ::SDL_WINDOWPOS_CENTERED, or
 *               ::SDL_WINDOWPOS_UNDEFINED.
 *  \param y     The y position of the window, ::SDL_WINDOWPOS_CENTERED, or
 *               ::SDL_WINDOWPOS_UNDEFINED.
 *  \param w     The width of the window, in screen coordinates.
 *  \param h     The height of the window, in screen coordinates.
 *  \param flags The flags for the window, a mask of any of the following:
 *               ::SDL_WINDOW_FULLSCREEN,    ::SDL_WINDOW_OPENGL,
 *               ::SDL_WINDOW_HIDDEN,        ::SDL_WINDOW_BORDERLESS,
 *               ::SDL_WINDOW_RESIZABLE,     ::SDL_WINDOW_MAXIMIZED,
 *               ::SDL_WINDOW_MINIMIZED,     ::SDL_WINDOW_INPUT_GRABBED,
 *               ::SDL_WINDOW_ALLOW_HIGHDPI, ::SDL_WINDOW_VULKAN.
 *
 *  \return The created window, or NULL if window creation failed.
 *
 *  If the window is created with the SDL_WINDOW_ALLOW_HIGHDPI flag, its size
 *  in pixels may differ from its size in screen coordinates on platforms with
 *  high-DPI support (e.g. iOS and Mac OS X). Use SDL_GetWindowSize() to query
 *  the client area's size in screen coordinates, and SDL_GL_GetDrawableSize(),
 *  SDL_Vulkan_GetDrawableSize(), or SDL_GetRendererOutputSize() to query the
 *  drawable size in pixels.
 *
 *  If the window is created with any of the SDL_WINDOW_OPENGL or
 *  SDL_WINDOW_VULKAN flags, then the corresponding LoadLibrary function
 *  (SDL_GL_LoadLibrary or SDL_Vulkan_LoadLibrary) is called and the
 *  corresponding UnloadLibrary function is called by SDL_DestroyWindow().
 *
 *  If SDL_WINDOW_VULKAN is specified and there isn't a working Vulkan driver,
 *  SDL_CreateWindow() will fail because SDL_Vulkan_LoadLibrary() will fail.
 *
 *  \note On non-Apple devices, SDL requires you to either not link to the
 *        Vulkan loader or link to a dynamic library version. This limitation
 *        may be removed in a future version of SDL.
 *
 *  \sa SDL_DestroyWindow()
 *  \sa SDL_GL_LoadLibrary()
 *  \sa SDL_Vulkan_LoadLibrary()
 */
SdlWindowPtr SdlCreateWindow(const char *title, int x, int y, int w, int h, Uint32 flags);

/**
 *  \brief Get the SDL surface associated with the window.
 *
 *  \return The window's framebuffer surface, or NULL on error.
 *
 *  A new surface will be created with the optimal format for the window,
 *  if necessary. This surface will be freed when the window is destroyed.
 *
 *  \note You may not combine this with 3D or the rendering API on this window.
 *
 *  \sa SDL_UpdateWindowSurface()
 *  \sa SDL_UpdateWindowSurfaceRects()
 */
SDL_Surface& SdlGetWindowSurface(SDL_Window& window);