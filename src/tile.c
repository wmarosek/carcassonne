#include "tile.h"

tile g_tile_list[TILE_LIST_LEN];

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
