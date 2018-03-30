#ifndef TILE_H
#define TILE_H

#include <stdbool.h>
#include <stddef.h>

// define type representing single tile
typedef enum { CASTLE, ROAD, FIELD } element;
typedef enum { NONE, SHIELD, TEMPLE } modifier;
typedef struct {
    element up;
    element right;
    element down;
    element left;
    modifier mod;
} tile;

#define TILE_LIST_LEN 30
extern tile g_tile_list[TILE_LIST_LEN];     // list of aviable tiles

tile parse_tile();                          // parse single tile
bool parse_tile_list();                     // populate g_tile_list

char element_to_char(element);
char modifier_to_char(modifier);
char* tile_to_str(tile*, char*);
void print_tile(tile*);
void print_tile_list(tile*, size_t);

bool write_tile_list();

// gameplay
int rate_tile(tile*);                   // return a tile rating
tile choose_best_tile();                // choose best tile from the list based on rating

// rotate counterclockwise tile supplied by pointer,
// return pointer for checking validity or chaining function calls
// if pointer is null only return it
tile* rotate_tile(tile*);

#endif
