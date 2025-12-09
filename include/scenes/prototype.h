#ifndef SCENES_PROTOTYPE_H
#define SCENES_PROTOTYPE_H

#include <SDL2/SDL.h>
#include <core/ecs.h>

void Scene_PrototypeInit(World* world);
void Scene_PrototypeUpdate(World* world, float delta_time);
void Scene_PrototypeRender(World* world, SDL_Renderer* renderer);
void Scene_PrototypeCleanup(World* world);

#endif