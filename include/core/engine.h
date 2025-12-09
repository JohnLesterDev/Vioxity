#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>

typedef struct
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
} EngineSource;

int Engine_InitDefault(void);
int Engine_InitGL(void);

int Engine_InitOpenAL(void);

int Engine_Init(
    EngineSource* engine_source,
    int screen_index,
    uint32_t window_flags,
    uint32_t renderer_flags);

int Engine_QuitRequest(void);
void Engine_Quit(void);

EngineSource* Engine_Get_Source(void);
SDL_Window* Engine_Get_Window(void);
SDL_Renderer* Engine_Get_Renderer(void);

void Engine_ClearScreen(int r, int g, int b, int a);
void Engine_Present(void);

#endif