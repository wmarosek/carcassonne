#include "tile.h"

tile* rotate_tile(tile* t) {
    if (t) {
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
    return t;
}
