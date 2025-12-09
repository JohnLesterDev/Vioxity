#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

typedef struct {
    uint8_t is_running : 1;
    uint8_t : 7;
} GameFlags_u8;

int Game_Init(void);
void Game_Test(void);
void Game_Run(void);
void Game_Quit(void);

#endif