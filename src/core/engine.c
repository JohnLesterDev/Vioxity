#include <AL/al.h>
#include <AL/alc.h>
#include <config.h>
#include <core/engine.h>
#include <core/game.h>
#include <core/logging.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static EngineSource g_engine_source = { NULL, NULL, NULL };
static void* g_openal_lib_handler = NULL;

static volatile sig_atomic_t g_shutdown_requested = 0;
void Engine_SignalHandler(int signal)
{
    if (signal == SIGINT || signal == SIGTERM) {
        g_shutdown_requested = 1;
    }
}

int Engine_InitDefault(void)
{
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "");

    return Engine_Init(
        &g_engine_source,
        0,
        CONFIG_WINDOW_FLAGS,
        CONFIG_RENDERER_FLAGS);
}

int Engine_InitGL(void)
{
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");

    return Engine_Init(
        &g_engine_source,
        0,
        CONFIG_GL_WINDOW_FLAGS,
        CONFIG_RENDERER_FLAGS);
}

int Engine_InitOpenAL(void)
{
    g_openal_lib_handler = SDL_LoadObject(CONFIG_OPENAL_LIBNAME);

    if (!g_openal_lib_handler || g_openal_lib_handler == NULL) {
        LOG_ERROR("Failed to load OpenAL library: %s\n", SDL_GetError());
    } else {
        LOG_INFO("Loaded OpenAL library: %s\n", CONFIG_OPENAL_LIBNAME);
    }

    return 1;
}

int Engine_Init(
    EngineSource* engine_source,
    int screen_index,
    uint32_t window_flags,
    uint32_t renderer_flags)
{
    signal(SIGINT, Engine_SignalHandler);
    signal(SIGTERM, Engine_SignalHandler);

    if (SDL_Init(CONFIG_SDL_FLAGS) < 0) {
        LOG_FATAL("SDL initialization failed: %s\n", SDL_GetError());
        return -1;
    }

    Engine_InitOpenAL();

    engine_source->window = SDL_CreateWindow("",
        SDL_WINDOWPOS_CENTERED_DISPLAY(screen_index),
        SDL_WINDOWPOS_CENTERED_DISPLAY(screen_index),
        0,
        0,
        window_flags);

    if (!engine_source->window) {
        LOG_FATAL("Window creation failed: %s\n", SDL_GetError());
        return -1;
    }

    engine_source->renderer = SDL_CreateRenderer(
        engine_source->window,
        -1,
        renderer_flags);

    if (!engine_source->renderer) {
        LOG_FATAL("Renderer creation failed: %s\n", SDL_GetError());
        return -1;
    }

    SDL_RendererInfo info;
    SDL_GetRendererInfo(engine_source->renderer, &info);
    LOG_INFO("Renderer: %s\n", info.name);

    if (info.flags & SDL_RENDERER_TARGETTEXTURE) {
        LOG_INFO("Renderer supports target texture!\n");
    }

    return 1;
}

int Engine_QuitRequest(void)
{
    return g_shutdown_requested;
}

void Engine_Quit(void)
{
    if (g_engine_source.renderer) {
        SDL_DestroyRenderer(g_engine_source.renderer);
    }
    if (g_engine_source.window) {
        SDL_DestroyWindow(g_engine_source.window);
    }

    g_engine_source.renderer = NULL;
    g_engine_source.window = NULL;
    g_engine_source.texture = NULL;

    SDL_Quit();

    LOG_INFO("Engine quit.\n");
}

EngineSource* Engine_Get_Source(void)
{
    return &g_engine_source;
}

SDL_Window* Engine_Get_Window(void)
{
    return g_engine_source.window;
}

SDL_Renderer* Engine_Get_Renderer(void)
{
    return g_engine_source.renderer;
}

void Engine_ClearScreen(int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(g_engine_source.renderer, r, g, b, a);
    Engine_Present();
}

void Engine_Present(void)
{
    SDL_RenderPresent(g_engine_source.renderer);
}
