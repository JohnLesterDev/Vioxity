#ifndef COMPONENT_RENDER_H
#define COMPONENT_RENDER_H

#include <SDL2/SDL.h>
#include <stdint.h>

typedef enum {
    RENDER_NONE,
    RENDER_CIRCLE,
    RENDER_RECT,
    RENDER_LINE,
    RENDER_TEXTURE
} RenderType;

typedef struct {
    RenderType type;

    uint8_t r, g, b, a;
    int layer;

    union {
        struct {
            float radius;
            float width;
            float height;
            int filled;
        } shape;
        struct {
            float end_x;
            float end_y;
        } line;
        struct {
            SDL_Texture* texture;
            float width;
            float height;
            int x, y;
        } sprite;
    } data;

} RenderComponent;

#endif