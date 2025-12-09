#include <components/render.h>
#include <components/transform.h>
#include <core/ecs.h>
#include <systems/entity_render.h>

void System_EntityRender(World* world, SDL_Renderer* renderer)
{
    int required_components_mask = COMPONENT_TRANSFORM | COMPONENT_RENDER;

    for (int i = 0; i < world->entity_count; i++) {
        if ((world->entity_signatures[i] & required_components_mask) != required_components_mask) {
            continue;
        }

        TransformComponent* transform = &world->transforms[i];
        RenderComponent* render = &world->renders[i];

        SDL_SetRenderDrawColor(renderer, render->r, render->g, render->b, render->a);

        SDL_FRect f_rect = {
            transform->x,
            transform->y,
            render->data.shape.width,
            render->data.shape.height
        };

        if (render->data.shape.filled) {
            SDL_RenderFillRectF(renderer, &f_rect);
        } else {
            SDL_RenderDrawRectF(renderer, &f_rect);
        }
    }
}
