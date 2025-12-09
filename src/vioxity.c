#define SDL_MAIN_HANDLED

#include <config.h>
#include <core/game.h>
#include <core/logging.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    Log_Init(CONFIG_LOG_FILE_PATH, LOG_INFO);
    LOG_INFO("Starting Vioxity...\n");

    if (Game_Init() < 0) {
        fprintf(stderr, "Something went wrong...\n");
        return EXIT_FAILURE;
    }

    Game_Test();
    Game_Run();
    Game_Quit();

    Log_Destroy();

    return EXIT_SUCCESS;
}