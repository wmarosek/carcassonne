#include "tile.h"

#include <stdlib.h>
#include <stdio.h>

tile* g_tile_list[TILE_LIST_LEN];

char element_to_char(element e) {
    switch (e) {
    case CASTLE: return 'c';
    case ROAD: return 'r';
    case FIELD: return 'f';
    default: return '\0';
    }
}

char modifier_to_char(modifier m) {
    switch (m) {
    case SHIELD: return '*';
    case TEMPLE: return 't';
    default: return '_';
    }
}

char* tile_to_str(const tile* t, char* buff) {
    if (t && buff) {
        buff[0] = element_to_char(t->up);
        buff[1] = element_to_char(t->right);
        buff[2] = element_to_char(t->down);
        buff[3] = element_to_char(t->left);
        buff[4] = modifier_to_char(t->mod);
    } else if (buff) {
        buff[0] = '\t';
        for (int i = 1; i < 5; ++i) {
            buff[i] = '\0';                     // null all other cells
        }
    }
    return buff;
}

void print_tile(const tile* t) {
    char buff[5];
    printf("%.*s", 5, tile_to_str(t, buff));
}

void print_tile_list(const tile* t, size_t len) {
    for (int i = 0; i < len; ++i) {
        print_tile(&t[i]);
        printf("\n");
    }
}

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
