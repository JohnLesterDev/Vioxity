#ifndef MANAGER_H
#define MANAGER_H

typedef enum {
    COMPONENT_NONE = 0,
    COMPONENT_TRANSFORM = 1 << 0,
    COMPONENT_INPUT = 1 << 1,
    COMPONENT_RENDER = 1 << 2
} ComponentType;

#endif