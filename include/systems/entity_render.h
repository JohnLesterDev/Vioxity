#ifndef SYSTEMS_ENTITY_RENDER_H
#define SYSTEMS_ENTITY_RENDER_H

#include <SDL2/SDL.h>
#include <core/ecs.h>

void System_EntityRender(World* world, SDL_Renderer* renderer);

#endif