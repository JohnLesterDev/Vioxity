#include <components/render.h>
#include <components/transform.h>
#include <core/logging.h>
#include <math.h>
#include <scenes/prototype.h>
#include <systems/entity_render.h>

static int main_player;
static int line_entity;

void Scene_PrototypeInit(World* world)
{
    main_player = ECS_WorldCreateEntity(world);
    line_entity = ECS_WorldCreateEntity(world);

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

    world->transforms[line_entity] = (TransformComponent) { .x = 0, .y = 0 };
    world->renders[line_entity] = (RenderComponent) {
        .type = RENDER_LINE,
        .r = 255,
        .g = 0,
        .b = 0,
        .a = 255,
        .data.line = { .end_x = 0, .end_y = 0 }
    };

    world->entity_signatures[main_player] = COMPONENT_TRANSFORM | COMPONENT_RENDER;
    world->entity_signatures[line_entity] = COMPONENT_TRANSFORM | COMPONENT_RENDER;

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

    float chase_speed = 4.5f;
    float target_x = (float)mouse_x - (player_render->data.shape.width / 2.0f);
    float target_y = (float)mouse_y - (player_render->data.shape.height / 2.0f);

    player_transform->x += (target_x - player_transform->x) * chase_speed * delta_time;
    player_transform->y += (target_y - player_transform->y) * chase_speed * delta_time;

    TransformComponent* p_trans = &world->transforms[main_player];
    RenderComponent* p_render = &world->renders[main_player];

    float start_x = p_trans->x + (p_render->data.shape.width / 2.0f);
    float start_y = p_trans->y + (p_render->data.shape.height / 2.0f);

    float dx = (float)mouse_x - start_x;
    float dy = (float)mouse_y - start_y;
    float dist = sqrtf(dx * dx + dy * dy);

    if (dist > 5.0f) {
        world->entity_signatures[line_entity] |= COMPONENT_RENDER;

        world->transforms[line_entity].x = start_x;
        world->transforms[line_entity].y = start_y;

        world->renders[line_entity].data.line.end_x = (float)mouse_x;
        world->renders[line_entity].data.line.end_y = (float)mouse_y;
    } else {
        world->entity_signatures[line_entity] &= ~COMPONENT_RENDER;
    }
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