#ifndef TILE_H
#define TILE_H

#include <stdbool.h>

typedef enum { CASTLE, ROAD, FIELD } element;

typedef struct {
    element up;
    element right;
    element down;
    element left;
    bool shield;
    bool temple;
} tile;

void rotate_tile(tile* t);

#endif
