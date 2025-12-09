#include <components/render.h>
#include <components/transform.h>
#include <core/logging.h>
#include <math.h>
#include <scenes/prototype.h>
#include <systems/entity_render.h>

static int main_player;

void Scene_PrototypeInit(World* world)
{
    main_player = ECS_WorldCreateEntity(world);

    world->transforms[main_player] = (TransformComponent) {
        .x = 100.0f,
        .y = 100.0f,
        .rotation = 0.0f,
        .scale = 1.0f
    };

    world->renders[main_player] = (RenderComponent) {
        .type = RENDER_RECT,
        .r = 255,
        .g = 0,
        .b = 0,
        .a = 255,
        .data.shape = {
            .width = 32.0f,
            .height = 32.0f,
            .filled = 1 }
    };

    world->entity_signatures[main_player] = COMPONENT_TRANSFORM | COMPONENT_RENDER;

    LOG_INFO("Prototype scene initialized!");
}

void Scene_PrototypeUpdate(World* world, float delta_time)
{
    RenderComponent* player_render = &world->renders[main_player];
    TransformComponent* player_transform = &world->transforms[main_player];

    float time = SDL_GetTicks() / 1000.0f;
    player_render->r = (Uint8)((sin(time) + 1) * 127);
    player_render->g = (Uint8)((cos(time) + 2) * 127);
    player_render->b = (Uint8)((sin(time * 2) + 1) * 127);

    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    float chase_speed = 3.5f;
    float target_x = (float)mouse_x - (player_render->data.shape.width / 2.0f);
    float target_y = (float)mouse_y - (player_render->data.shape.height / 2.0f);

    player_transform->x += (target_x - player_transform->x) * chase_speed * delta_time;
    player_transform->y += (target_y - player_transform->y) * chase_speed * delta_time;
}

void Scene_PrototypeRender(World* world, SDL_Renderer* renderer)
{
    System_EntityRender(world, renderer);
}

void Scene_PrototypeCleanup(World* world)
{
    ECS_WorldInit(world);
    LOG_INFO("Prototype scene cleaned up!");
}