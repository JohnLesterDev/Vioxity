#include <core/ecs.h>
#include <core/logging.h>
#include <string.h>

void ECS_WorldInit(World* world)
{
    world->entity_count = 0;

    memset(world->entity_signatures, 0, sizeof(world->entity_signatures));

    memset(world->transforms, 0, sizeof(world->transforms));
    memset(world->inputs, 0, sizeof(world->inputs));
    memset(world->renders, 0, sizeof(world->renders));
}

int ECS_WorldCreateEntity(World* world)
{
    if (world->entity_count >= MAX_ENTITIES) {
        LOG_ERROR("Too many entities in world!");
        return -1;
    }

    int entity_id = world->entity_count++;
    world->entity_signatures[entity_id] = COMPONENT_NONE;

    return entity_id;
}

void ECS_WorldDestroyEntity(World* world, int entity)
{
    if (entity < 0 || entity >= MAX_ENTITIES)
        return;

    world->entity_signatures[entity] = COMPONENT_NONE;
}
