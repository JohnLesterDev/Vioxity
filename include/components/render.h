#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include <stdint.h>

typedef enum {
    RENDER_NONE,
    RENDER_CIRCLE,
    RENDER_RECT,
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
        } shape;
        struct {
            SDL_Texture* texture;
            float width;
            float height;
            int x, y;
        } sprite;
    } data;

} RenderComponent;

#endif