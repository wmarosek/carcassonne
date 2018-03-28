#ifndef TILE_H
#define TILE_H

#include <stdbool.h>

// define type representing single tile
typedef enum { CASTLE, ROAD, FIELD } element;
typedef struct {
    element up;
    element right;
    element down;
    element left;
    enum { SHIELD, TEMPLE } modifier;
} tile;

#define TILE_LIST_LEN 30
extern tile g_tile_list[TILE_LIST_LEN]; // list of aviable tiles

tile parse_tile();                      // parse single tile
bool parse_tile_list();                 // populate g_tile_list

int rate_tile(tile*);                   // return a tile rating
tile choose_best_tile();                // choose best tile from the list based on rating

bool write_tile_list();

// rotate counterclockwise tile supplied by pointer,
// return pointer for checking validity or chaining function calls
// if pointer is null only return it
tile* rotate_tile(tile*);

#endif
