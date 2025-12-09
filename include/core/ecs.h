#ifndef ECS_H
#define ECS_H

#include <components/input.h>
#include <components/manager.h>
#include <components/render.h>
#include <components/transform.h>

#define MAX_ENTITIES 5000

typedef struct {
    int entity_signatures[MAX_ENTITIES];

    TransformComponent transforms[MAX_ENTITIES];
    InputComponent inputs[MAX_ENTITIES];
    RenderComponent renders[MAX_ENTITIES];

    int entity_count;

} World;

void ECS_WorldInit(World* world);
int ECS_WorldCreateEntity(World* world);
void ECS_WorldDestroyEntity(World* world, int entity);

#endif