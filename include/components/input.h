#ifndef COMPONENTS_INPUT_H
#define COMPONENTS_INPUT_H

#include <stdint.h>

typedef struct {
    float mouse_x;
    float mouse_y;

    uint32_t keys;
} InputComponent;

#endif