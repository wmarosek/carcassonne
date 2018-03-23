#ifndef TILE_H
#define TILE_H

typedef enum { CASTLE, ROAD, FIELD } element;

typedef struct {
    element up;
    element right;
    element down;
    element left;
    enum { SHIELD, TEMPLE } modifier;
} tile;

// rotate counterclockwise tile supplied by pointer,
// return pointer for checking validity or chaining function calls
// if pointer is null only return it
tile* rotate_tile(tile* t);

#endif
