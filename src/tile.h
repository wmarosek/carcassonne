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

// rotate clockwise tile supplied by pointer,
// return pointer for checking validity or chaining commands
// if pointer is null only return it
tile* rotate_tile(tile* t);

#endif
