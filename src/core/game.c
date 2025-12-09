#include <core/engine.h>
#include <core/game.h>
#include <core/logging.h>
#include <stdio.h>

static GameFlags_u8 game_flags = { 0 };
static SDL_Event event;

int Game_Init(void)
{
    if (Engine_InitGL() < 0) {
        LOG_FATAL("Engine initialization failed...\n");
        return -1;
    }

    game_flags.is_running = 1;

    SDL_ShowCursor(SDL_DISABLE);

    return 0;
}

void Game_Test(void)
{
    LOG_INFO("Game test initialized...\n");

    int num_render_drivers = SDL_GetNumRenderDrivers();
    LOG_INFO("Total available render drivers: %d\n\n", num_render_drivers);
}

void Game_Run(void)
{
    while (game_flags.is_running && !Engine_QuitRequest()) {
        Engine_ClearScreen(0, 0, 0, 255);

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                game_flags.is_running = 0;
                break;
            default:
                break;
            }
        }

        Engine_Present();
    }
}

void Game_Quit(void)
{
    Engine_Quit();
}
