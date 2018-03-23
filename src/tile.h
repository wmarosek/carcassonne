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

void rotate_tile(tile* t) {
    element
        u = t->up,
        r = t->right,
        d = t->down,
        l = t->left;
    t->up = r;
    t->right = d;
    t->down = l;
    t->left = u;
}

#endif
