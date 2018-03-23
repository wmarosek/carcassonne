#include "tile.h"

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
